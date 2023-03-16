#include <iostream>
#include <vector>
#include <memory>

using namespace std;

enum RB
{
    Red = true,
    Black = false
};

struct RBnode
{
    int data;
    RB type;
    shared_ptr<struct RBnode> parent;
    shared_ptr<struct RBnode> left;
    shared_ptr<struct RBnode> right;
};

class RBtree
{
private:
    shared_ptr<struct RBnode> root;
    shared_ptr<struct RBnode> TNULL;
    shared_ptr<struct RBnode> Create_New_Node(shared_ptr<struct RBnode> node, shared_ptr<struct RBnode> parent);

    void leftRotate(shared_ptr<struct RBnode> x);
    void rightRotate(shared_ptr<struct RBnode> x);

    void Fix_Insert_Tree(shared_ptr<struct RBnode> k);

    void Delete_Node_Rec(shared_ptr<struct RBnode> node, int data);
    void Fix_Delete_Tree(shared_ptr<struct RBnode> x);
    void Red_Black_Transplant(shared_ptr<struct RBnode> u, shared_ptr<struct RBnode> v);

    void DisplaytreeRec(shared_ptr<struct RBnode> root, int height, vector<bool> DispLine);
    void In_Order_Rec(shared_ptr<struct RBnode> node);

public:
    RBtree();
    RBtree(vector<int> ListData);

    shared_ptr<struct RBnode> minimum(shared_ptr<struct RBnode> node);

    void Insert_Node(int data);

    shared_ptr<struct RBnode> get_Root();

    void Delete_Node(int data);

    void Displaytree(shared_ptr<struct RBnode> root);
    void In_Order();

    ~RBtree() = default;
};

shared_ptr<struct RBnode> RBtree::Create_New_Node(shared_ptr<struct RBnode> node, shared_ptr<struct RBnode> parent)
{
    shared_ptr<struct RBnode> temp = make_shared<struct RBnode>();
    node->data = 0;
    node->parent = parent;
    node->left = NULL;
    node->right = NULL;
    node->type = Black;
    return node;
}

void RBtree::In_Order_Rec(shared_ptr<struct RBnode> node)
{
    if (node != TNULL)
    {
        In_Order_Rec(node->left);
        cout << node->data << " ";
        In_Order_Rec(node->right);
    }
}

// For balancing the tree after deletion
void RBtree::Fix_Delete_Tree(shared_ptr<struct RBnode> x)
{
    shared_ptr<struct RBnode> s;
    while (x != this->root && x->type == 0)
    {
        if (x == x->parent->left)
        {
            s = x->parent->right;
            if (s->type)
            {
                s->type = Black;
                x->parent->type = Red;
                leftRotate(x->parent);
                s = x->parent->right;
            }

            if (s->left->type == 0 && s->right->type == 0)
            {
                s->type = Red;
                x = x->parent;
            }
            else
            {
                if (s->right->type == 0)
                {
                    s->left->type = Black;
                    s->type = Red;
                    rightRotate(s);
                    s = x->parent->right;
                }

                s->type = x->parent->type;
                x->parent->type = Black;
                s->right->type = Black;
                leftRotate(x->parent);
                x = this->root;
            }
        }
        else
        {
            s = x->parent->left;
            if (s->type)
            {
                s->type = Black;
                x->parent->type = Red;
                rightRotate(x->parent);
                s = x->parent->left;
            }

            if (s->right->type == 0 && s->right->type == 0)
            {
                s->type = Red;
                x = x->parent;
            }
            else
            {
                if (s->left->type == 0)
                {
                    s->right->type = Black;
                    s->type = Red;
                    leftRotate(s);
                    s = x->parent->left;
                }

                s->type = x->parent->type;
                x->parent->type = Black;
                s->left->type = Black;
                rightRotate(x->parent);
                x = this->root;
            }
        }
    }
    x->type = Black;
}

void RBtree::Red_Black_Transplant(shared_ptr<struct RBnode> u, shared_ptr<struct RBnode> v)
{
    if (u->parent == NULL)
    {
        this->root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void RBtree::Delete_Node_Rec(shared_ptr<struct RBnode> node, int data)
{
    shared_ptr<struct RBnode> z = TNULL;
    shared_ptr<struct RBnode> x, y;
    while (node != TNULL)
    {
        if (node->data == data)
        {
            z = node;
        }

        if (node->data <= data)
        {
            node = node->right;
        }
        else
        {
            node = node->left;
        }
    }

    if (z == TNULL)
    {
        cout << "Key not found in the tree" << endl;
        return;
    }

    y = z;
    int y_original_color = y->type;
    if (z->left == TNULL)
    {
        x = z->right;
        Red_Black_Transplant(z, z->right);
    }
    else if (z->right == TNULL)
    {
        x = z->left;
        Red_Black_Transplant(z, z->left);
    }
    else
    {
        y = minimum(z->right);
        y_original_color = y->type;
        x = y->right;
        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            Red_Black_Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        Red_Black_Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->type = z->type;
    }

    if (y_original_color == 0)
    {
        Fix_Delete_Tree(x);
    }
}

// For balancing the tree after insertion
void RBtree::Fix_Insert_Tree(shared_ptr<struct RBnode> k)
{
    shared_ptr<struct RBnode> u;
    while (k->parent->type)
    {
        if (k->parent == k->parent->parent->right)
        {
            u = k->parent->parent->left;
            if (u->type)
            {
                u->type = Black;
                k->parent->type = Black;
                k->parent->parent->type = Red;
                k = k->parent->parent;
            }
            else
            {
                if (k == k->parent->left)
                {
                    k = k->parent;
                    rightRotate(k);
                }
                k->parent->type = Black;
                k->parent->parent->type = Red;
                leftRotate(k->parent->parent);
            }
        }
        else
        {
            u = k->parent->parent->right;

            if (u->type)
            {
                u->type = Black;
                k->parent->type = Black;
                k->parent->parent->type = Red;
                k = k->parent->parent;
            }
            else
            {
                if (k == k->parent->right)
                {
                    k = k->parent;
                    leftRotate(k);
                }
                k->parent->type = Black;
                k->parent->parent->type = Red;
                rightRotate(k->parent->parent);
            }
        }
        if (k == this->root)
        {
            break;
        }
    }
    this->root->type = Black;
}

RBtree::RBtree()
{
    TNULL = make_shared<struct RBnode>();
    TNULL->type = Black;
    TNULL->left = NULL;
    TNULL->right = NULL;
    this->root = TNULL;
}

RBtree::RBtree(vector<int> ListData)
{
    TNULL = make_shared<struct RBnode>();
    TNULL->type = Black;
    TNULL->left = NULL;
    TNULL->right = NULL;
    this->root = TNULL;

    for (size_t i = 0; i < ListData.size(); i++)
    {
        Insert_Node(ListData[i]);
    }
}

void RBtree::In_Order()
{
    In_Order_Rec(this->root);
}

shared_ptr<struct RBnode> RBtree::minimum(shared_ptr<struct RBnode> node)
{
    while (node->left != TNULL)
    {
        node = node->left;
    }
    return node;
}

void RBtree::leftRotate(shared_ptr<struct RBnode> root)
{
    shared_ptr<struct RBnode> rootR = root->right;
    root->right = rootR->left;
    if (rootR->left != TNULL)
    {
        rootR->left->parent = root;
    }
    rootR->parent = root->parent;
    if (root->parent == NULL)
    {
        this->root = rootR;
    }
    else if (root == root->parent->left)
    {
        root->parent->left = rootR;
    }
    else
    {
        root->parent->right = rootR;
    }
    rootR->left = root;
    root->parent = rootR;
}

void RBtree::rightRotate(shared_ptr<struct RBnode> root)
{
    shared_ptr<struct RBnode> rootL = root->left;
    root->left = rootL->right;
    if (rootL->right != TNULL)
    {
        rootL->right->parent = root;
    }
    rootL->parent = root->parent;
    if (root->parent == NULL)
    {
        this->root = rootL;
    }
    else if (root == root->parent->right)
    {
        root->parent->right = rootL;
    }
    else
    {
        root->parent->left = rootL;
    }
    rootL->right = root;
    root->parent = rootL;
}

// Inserting a node
void RBtree::Insert_Node(int data)
{
    shared_ptr<struct RBnode> node = make_shared<struct RBnode>();
    node->parent = NULL;
    node->data = data;
    node->left = TNULL;
    node->right = TNULL;
    node->type = Red;

    shared_ptr<struct RBnode> y = NULL;
    shared_ptr<struct RBnode> x = this->root;

    while (x != TNULL)
    {
        y = x;
        if (node->data < x->data)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    node->parent = y;
    if (y == NULL)
    {
        this->root = node;
    }
    else if (node->data < y->data)
    {
        y->left = node;
    }
    else
    {
        y->right = node;
    }

    if (node->parent == NULL)
    {
        node->type = Black;
        return;
    }

    if (node->parent->parent == NULL)
    {
        return;
    }

    Fix_Insert_Tree(node);
}

shared_ptr<struct RBnode> RBtree::get_Root()
{
    return this->root;
}

void RBtree::Delete_Node(int data)
{
    Delete_Node_Rec(this->root, data);
}

// --------------------------------------------------------
void RBtree::Displaytree(shared_ptr<struct RBnode> root)
{
    if (root == TNULL)
    {
        cout << "Empty Tree" << endl;
        return;
    }

    if (root->type)
    {
        cout << "0> RED: " << root->data << endl;
    }
    else
    {
        cout << "0> BLK: " << root->data << endl;
    }

    vector<bool> Disp;
    Disp.push_back(false);
    if (root->right != TNULL)
    {
        Disp.push_back(true);
        DisplaytreeRec(root->right, 0, Disp);
        Disp.pop_back();
    }
    if (root->left != TNULL)
    {
        Disp.push_back(false);
        DisplaytreeRec(root->left, 0, Disp);
        Disp.pop_back();
    }
    return;
}

void RBtree::DisplaytreeRec(shared_ptr<struct RBnode> root, int height, vector<bool> DispLine)
{

    for (size_t i = 0; i < (height + 1); i++)
    {
        if (DispLine[i] == true)
        {
            cout << "|";
        }
        else
        {
            cout << " ";
        }
    }

    if (DispLine[DispLine.size() - 1] == true)
    {
        cout << "R";
    }
    else
    {
        cout << "L";
    }

    if (root->type)
    {
        cout << "0> RED :" << root->data << endl;
    }
    else
    {
        cout << "0> BLK :" << root->data << endl;
    }
    if (root->right != TNULL)
    {
        DispLine.push_back(true);
        DisplaytreeRec(root->right, height + 1, DispLine);
        DispLine.pop_back();
    }
    if (root->left != TNULL)
    {
        DispLine.push_back(false);
        DisplaytreeRec(root->left, height + 1, DispLine);
        DispLine.pop_back();
    }
    return;
}

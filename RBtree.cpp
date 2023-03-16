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

    void leftRotate(shared_ptr<struct RBnode> rootX);
    void rightRotate(shared_ptr<struct RBnode> rootX);

    void Fix_Insert_Tree(shared_ptr<struct RBnode> rootK);

    void Delete_Node_Rec(shared_ptr<struct RBnode> node, int data);
    void Fix_Delete_Tree(shared_ptr<struct RBnode> rootX);
    void Red_Black_Transplant(shared_ptr<struct RBnode> rootU, shared_ptr<struct RBnode> rootV);

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
void RBtree::Fix_Delete_Tree(shared_ptr<struct RBnode> rootX)
{
    shared_ptr<struct RBnode> rootS;
    while (rootX != this->root && rootX->type == 0)
    {
        if (rootX == rootX->parent->left)
        {
            rootS = rootX->parent->right;
            if (rootS->type)
            {
                rootS->type = Black;
                rootX->parent->type = Red;
                leftRotate(rootX->parent);
                rootS = rootX->parent->right;
            }

            if (rootS->left->type == 0 && rootS->right->type == 0)
            {
                rootS->type = Red;
                rootX = rootX->parent;
            }
            else
            {
                if (rootS->right->type == 0)
                {
                    rootS->left->type = Black;
                    rootS->type = Red;
                    rightRotate(rootS);
                    rootS = rootX->parent->right;
                }

                rootS->type = rootX->parent->type;
                rootX->parent->type = Black;
                rootS->right->type = Black;
                leftRotate(rootX->parent);
                rootX = this->root;
            }
        }
        else
        {
            rootS = rootX->parent->left;
            if (rootS->type)
            {
                rootS->type = Black;
                rootX->parent->type = Red;
                rightRotate(rootX->parent);
                rootS = rootX->parent->left;
            }

            if (rootS->right->type == 0 && rootS->right->type == 0)
            {
                rootS->type = Red;
                rootX = rootX->parent;
            }
            else
            {
                if (rootS->left->type == 0)
                {
                    rootS->right->type = Black;
                    rootS->type = Red;
                    leftRotate(rootS);
                    rootS = rootX->parent->left;
                }

                rootS->type = rootX->parent->type;
                rootX->parent->type = Black;
                rootS->left->type = Black;
                rightRotate(rootX->parent);
                rootX = this->root;
            }
        }
    }
    rootX->type = Black;
}

void RBtree::Red_Black_Transplant(shared_ptr<struct RBnode> rootU, shared_ptr<struct RBnode> rootV)
{
    if (rootU->parent == NULL)
    {
        this->root = rootV;
    }
    else if (rootU == rootU->parent->left)
    {
        rootU->parent->left = rootV;
    }
    else
    {
        rootU->parent->right = rootV;
    }
    rootV->parent = rootU->parent;
}

void RBtree::Delete_Node_Rec(shared_ptr<struct RBnode> node, int data)
{
    shared_ptr<struct RBnode> rootZ = TNULL;
    shared_ptr<struct RBnode> rootX, rootY;
    while (node != TNULL)
    {
        if (node->data == data)
        {
            rootZ = node;
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

    if (rootZ == TNULL)
    {
        cout << "Key not found in the tree" << endl;
        return;
    }

    rootY = rootZ;
    int y_original_color = rootY->type;
    if (rootZ->left == TNULL)
    {
        rootX = rootZ->right;
        Red_Black_Transplant(rootZ, rootZ->right);
    }
    else if (rootZ->right == TNULL)
    {
        rootX = rootZ->left;
        Red_Black_Transplant(rootZ, rootZ->left);
    }
    else
    {
        rootY = minimum(rootZ->right);
        y_original_color = rootY->type;
        rootX = rootY->right;
        if (rootY->parent == rootZ)
        {
            rootX->parent = rootY;
        }
        else
        {
            Red_Black_Transplant(rootY, rootY->right);
            rootY->right = rootZ->right;
            rootY->right->parent = rootY;
        }

        Red_Black_Transplant(rootZ, rootY);
        rootY->left = rootZ->left;
        rootY->left->parent = rootY;
        rootY->type = rootZ->type;
    }

    if (y_original_color == 0)
    {
        Fix_Delete_Tree(rootX);
    }
}

// For balancing the tree after insertion
void RBtree::Fix_Insert_Tree(shared_ptr<struct RBnode> rootK)
{
    shared_ptr<struct RBnode> rootU;
    while (rootK->parent->type)
    {
        if (rootK->parent == rootK->parent->parent->right)
        {
            rootU = rootK->parent->parent->left;
            if (rootU->type)
            {
                rootU->type = Black;
                rootK->parent->type = Black;
                rootK->parent->parent->type = Red;
                rootK = rootK->parent->parent;
            }
            else
            {
                if (rootK == rootK->parent->left)
                {
                    rootK = rootK->parent;
                    rightRotate(rootK);
                }
                rootK->parent->type = Black;
                rootK->parent->parent->type = Red;
                leftRotate(rootK->parent->parent);
            }
        }
        else
        {
            rootU = rootK->parent->parent->right;

            if (rootU->type)
            {
                rootU->type = Black;
                rootK->parent->type = Black;
                rootK->parent->parent->type = Red;
                rootK = rootK->parent->parent;
            }
            else
            {
                if (rootK == rootK->parent->right)
                {
                    rootK = rootK->parent;
                    leftRotate(rootK);
                }
                rootK->parent->type = Black;
                rootK->parent->parent->type = Red;
                rightRotate(rootK->parent->parent);
            }
        }
        if (rootK == this->root)
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

    shared_ptr<struct RBnode> rootY = NULL;
    shared_ptr<struct RBnode> rootX = this->root;

    while (rootX != TNULL)
    {
        rootY = rootX;
        if (node->data < rootX->data)
        {
            rootX = rootX->left;
        }
        else
        {
            rootX = rootX->right;
        }
    }

    node->parent = rootY;
    if (rootY == NULL)
    {
        this->root = node;
    }
    else if (node->data < rootY->data)
    {
        rootY->left = node;
    }
    else
    {
        rootY->right = node;
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

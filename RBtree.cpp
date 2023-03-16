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
    int comparsions;
    int rotations;

    shared_ptr<struct RBnode> Create_New_Node(shared_ptr<struct RBnode> node, shared_ptr<struct RBnode> parent);

    void leftRotate(shared_ptr<struct RBnode> rootX);
    void rightRotate(shared_ptr<struct RBnode> rootX);

    void Fix_Insert_Tree(shared_ptr<struct RBnode> rootK);

    void Delete_Node_Rec(shared_ptr<struct RBnode> node, int data);
    void Fix_Delete_Tree(shared_ptr<struct RBnode> rootX);
    void Red_Black_Transplant(shared_ptr<struct RBnode> rootU, shared_ptr<struct RBnode> rootV);

    void DisplaytreeRec(shared_ptr<struct RBnode> root, int height, vector<bool> DispLine);
    void In_Order_Rec(shared_ptr<struct RBnode> node);
    int Check_Height_Rec(shared_ptr<struct RBnode> root, int current);

public:
    RBtree();
    RBtree(vector<int> ListData);

    shared_ptr<struct RBnode> minimum(shared_ptr<struct RBnode> node);

    void Insert_Node(int data);

    shared_ptr<struct RBnode> get_Root();
    int get_Rotation();
    int get_Comparsion();

    void Delete_Node(int data);

    void Displaytree(shared_ptr<struct RBnode> root);
    void In_Order();

    int Check_Height(shared_ptr<struct RBnode> root);
    int Node_Amount(shared_ptr<struct RBnode> root);

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
        cout << node->data << ", ";
        In_Order_Rec(node->right);
    }
}

void RBtree::Fix_Delete_Tree(shared_ptr<struct RBnode> rootX)
{
    shared_ptr<struct RBnode> rootS;
    while (rootX != this->root && rootX->type == 0)
    {
        this->comparsions += 1;
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
                this->comparsions += 1;

                rootS->type = rootX->parent->type;
                rootX->parent->type = Black;
                rootS->right->type = Black;
                leftRotate(rootX->parent);
                rootX = this->root;
            }
            this->comparsions += 2;
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
            this->comparsions += 1;

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
                this->comparsions += 1;

                rootS->type = rootX->parent->type;
                rootX->parent->type = Black;
                rootS->left->type = Black;
                rightRotate(rootX->parent);
                rootX = this->root;
            }
            this->comparsions += 1;
        }
        this->comparsions += 1;
    }
    rootX->type = Black;
}

void RBtree::Red_Black_Transplant(shared_ptr<struct RBnode> rootU, shared_ptr<struct RBnode> rootV)
{
    if (rootU->parent == NULL)
    {
        this->root = rootV;
        this->comparsions += 1;
    }
    else if (rootU == rootU->parent->left)
    {
        this->comparsions += 2;
        rootU->parent->left = rootV;
    }
    else
    {
        this->comparsions += 2;
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
        this->comparsions += 3;
    }

    if (rootZ == TNULL)
    {
        cout << "Key not found in the tree" << endl;
        return;
    }
    this->comparsions += 1;

    rootY = rootZ;
    int y_original_color = rootY->type;
    if (rootZ->left == TNULL)
    {
        this->comparsions += 1;
        rootX = rootZ->right;
        Red_Black_Transplant(rootZ, rootZ->right);
    }
    else if (rootZ->right == TNULL)
    {
        this->comparsions += 2;
        rootX = rootZ->left;
        Red_Black_Transplant(rootZ, rootZ->left);
    }
    else
    {
        this->comparsions += 2;

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
        this->comparsions += 1;

        Red_Black_Transplant(rootZ, rootY);
        rootY->left = rootZ->left;
        rootY->left->parent = rootY;
        rootY->type = rootZ->type;
    }

    if (y_original_color == 0)
    {
        this->comparsions += 1;
        Fix_Delete_Tree(rootX);
    }
}

void RBtree::Fix_Insert_Tree(shared_ptr<struct RBnode> rootK)
{
    shared_ptr<struct RBnode> rootU;
    while (rootK->parent->type)
    {
        this->comparsions += 1;
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
                this->comparsions += 1;
                rootK->parent->type = Black;
                rootK->parent->parent->type = Red;
                leftRotate(rootK->parent->parent);
            }
            this->comparsions += 2;
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
                this->comparsions += 1;
                rootK->parent->type = Black;
                rootK->parent->parent->type = Red;
                rightRotate(rootK->parent->parent);
            }
            this->comparsions += 2;
        }
        if (rootK == this->root)
        {
            this->comparsions += 1;
            break;
        }
        this->comparsions += 1;
    }
    this->root->type = Black;
}

RBtree::RBtree()
{
    rotations = 0;
    comparsions = 0;

    TNULL = make_shared<struct RBnode>();
    TNULL->type = Black;
    TNULL->left = NULL;
    TNULL->right = NULL;
    this->root = TNULL;
}

RBtree::RBtree(vector<int> ListData)
{
    rotations = 0;
    comparsions = 0;
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
        this->comparsions += 1;
        node = node->left;
    }
    return node;
}

void RBtree::leftRotate(shared_ptr<struct RBnode> root)
{
    this->rotations++;
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

    rotations++;
}

void RBtree::rightRotate(shared_ptr<struct RBnode> root)
{
    this->rotations++;
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

    rotations++;
}

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
        this->comparsions += 2;
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
        this->comparsions += 1;
    }
    else if (node->data < rootY->data)
    {
        rootY->left = node;
        this->comparsions += 2;
    }
    else
    {
        rootY->right = node;
        this->comparsions += 2;
    }

    if (node->parent == NULL)
    {
        this->comparsions += 1;
        node->type = Black;
        return;
    }
    this->comparsions += 1;
    if (node->parent->parent == NULL)
    {
        this->comparsions += 1;
        return;
    }
    this->comparsions += 1;

    Fix_Insert_Tree(node);
}

shared_ptr<struct RBnode> RBtree::get_Root()
{
    return this->root;
}

int RBtree::get_Rotation()
{
    return this->rotations;
}
int RBtree::get_Comparsion()
{
    return this->comparsions;
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

int RBtree::Check_Height(shared_ptr<struct RBnode> root)
{
    return Check_Height_Rec(root, 1);
}

int RBtree::Check_Height_Rec(shared_ptr<struct RBnode> root, int current)
{
    int maxR = 0;
    int maxL = 0;

    if (root->right != NULL)
    {
        maxR = Check_Height_Rec(root->right, current + 1);
    }

    if (root->left != NULL)
    {
        maxL = Check_Height_Rec(root->left, current + 1);
    }

    if (current > max(maxR, maxL))
    {
        return current;
    }
    return max(maxR, maxL);
}

int RBtree::Node_Amount(shared_ptr<struct RBnode> root)
{
    int count = 0;
    if (root->right != TNULL)
    {
        count += Node_Amount(root->right);
    }

    if (root->left != TNULL)
    {
        count += Node_Amount(root->left);
    }
    return count + 1;
}
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

struct AVLnode
{
    int data;
    int height;
    shared_ptr<struct AVLnode> left;
    shared_ptr<struct AVLnode> right;
};

class AVLtree
{
private:
    shared_ptr<struct AVLnode> root;

    shared_ptr<struct AVLnode> RRRotation(shared_ptr<struct AVLnode> root);
    shared_ptr<struct AVLnode> LLRotation(shared_ptr<struct AVLnode> root);

    void DisplaytreeRec(shared_ptr<struct AVLnode> root, int height, vector<bool> DispLine);
    void in_OrderRec(shared_ptr<struct AVLnode> root);

public:
    shared_ptr<struct AVLnode> Create_New_Node(int data);

    AVLtree(int HeadData);
    AVLtree(vector<int> ListData);

    shared_ptr<struct AVLnode> get_Root();
    void set_Root(shared_ptr<struct AVLnode> root);

    int Check_Balance(shared_ptr<struct AVLnode> root);
    int Check_Height(shared_ptr<struct AVLnode> root);
    shared_ptr<struct AVLnode> MinValue_Node_Search(shared_ptr<struct AVLnode> node);

    shared_ptr<struct AVLnode> Insert_Node(shared_ptr<struct AVLnode> root, int data);
    shared_ptr<struct AVLnode> Delete_Node(shared_ptr<struct AVLnode> root, int data);

    void Displaytree(shared_ptr<struct AVLnode> root);
    void in_Order(shared_ptr<struct AVLnode> root);

    ~AVLtree() = default;
};

shared_ptr<struct AVLnode> AVLtree::Create_New_Node(int data)
{
    shared_ptr<struct AVLnode> temp = make_shared<struct AVLnode>();
    temp->data = data;
    temp->height = 1;
    temp->left = temp->right = NULL;
    return temp;
}

AVLtree::AVLtree(int HeadData)
{
    root = Create_New_Node(HeadData);
}

AVLtree::AVLtree(vector<int> ListData)
{
    for (size_t i = 0; i < ListData.size(); i++)
    {
        root = Insert_Node(root, ListData[i]);
    }
}

shared_ptr<struct AVLnode> AVLtree::Insert_Node(shared_ptr<struct AVLnode> root, int data)
{
    if (root == NULL)
    {
        return (Create_New_Node(data));
    }
    else if (data > root->data)
    {
        root->right = Insert_Node(root->right, data);
    }
    else if (data < root->data)
    {
        root->left = Insert_Node(root->left, data);
    }
    else
    {
        return root;
    }

    // Update balance
    root->height = 1 + max(Check_Height(root->left), Check_Height(root->right));
    int balance = Check_Balance(root);

    if (balance > 1)
    {
        if (data < root->left->data)
        {
            return RRRotation(root);
        }
        else if (data > root->left->data)
        {
            root->left = LLRotation(root->left);
            return RRRotation(root);
        }
    }
    if (balance < -1)
    {
        if (data > root->right->data)
        {
            return LLRotation(root);
        }
        else if (data < root->right->data)
        {
            root->right = RRRotation(root->right);
            return LLRotation(root);
        }
    }
    return root;
}

shared_ptr<struct AVLnode> AVLtree::MinValue_Node_Search(shared_ptr<struct AVLnode> node)
{
    auto current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

shared_ptr<struct AVLnode> AVLtree::Delete_Node(shared_ptr<struct AVLnode> root, int data)
{
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = Delete_Node(root->left, data);
    else if (data > root->data)
        root->right = Delete_Node(root->right, data);
    else
    {
        if ((root->left == NULL) && (root->right == NULL))
        {
            root = NULL;
        }
        else if ((root->left == NULL) || (root->right == NULL))
        {
            root = root->left ? root->left : root->right;
        }
        else
        {
            auto temp = MinValue_Node_Search(root->right); // min?
            root->data = temp->data;
            root->right = Delete_Node(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    // Update balance
    root->height = 1 + max(Check_Height(root->left), Check_Height(root->right));
    int balance = Check_Balance(root);

    if (balance > 1)
    {
        if (Check_Balance(root->left) >= 0)
        {
            return RRRotation(root);
        }
        else
        {
            root->left = LLRotation(root->left);
            return RRRotation(root);
        }
    }
    else if (balance < -1)
    {
        if (Check_Balance(root->right) <= 0)
        {
            return LLRotation(root);
        }
        else if (data < root->right->data)
        {
            root->right = RRRotation(root->right);
            return LLRotation(root);
        }
    }
    return root;
}

shared_ptr<struct AVLnode> AVLtree::RRRotation(shared_ptr<struct AVLnode> root)
{
    auto rootL = root->left;
    auto rootLR = rootL->right;
    rootL->right = root;
    root->left = rootLR;
    root->height = max(Check_Height(root->left), Check_Height(root->right)) + 1;
    rootL->height = max(Check_Height(rootL->left), Check_Height(rootL->right)) + 1;
    return rootL;
}
shared_ptr<struct AVLnode> AVLtree::LLRotation(shared_ptr<struct AVLnode> root)
{
    auto rootR = root->right;
    auto rootRL = rootR->left;
    rootR->left = root;
    root->right = rootRL;
    root->height = max(Check_Height(root->left), Check_Height(root->right)) + 1;
    rootR->height = max(Check_Height(rootR->left), Check_Height(rootR->right)) + 1;
    return rootR;
}

int AVLtree::Check_Height(shared_ptr<struct AVLnode> root)
{
    if (root == NULL)
        return 0;
    return root->height;
}

int AVLtree::Check_Balance(shared_ptr<struct AVLnode> root)
{
    if (root == NULL)
        return 0;
    return Check_Height(root->left) - Check_Height(root->right);
}

void AVLtree::in_Order(shared_ptr<struct AVLnode> root)
{
    cout << "List;" << endl;
    in_OrderRec(root);
    cout << endl;
}

void AVLtree::in_OrderRec(shared_ptr<struct AVLnode> root)
{
    if (root->left != NULL)
    {
        in_OrderRec(root->left);
    }

    cout << root->data << ", ";

    if (root->right != NULL)
    {
        in_OrderRec(root->right);
    }
}

void AVLtree::Displaytree(shared_ptr<struct AVLnode> root)
{
    if (root == NULL)
    {
        cout << "Empty Tree" << endl;
        return;
    }

    cout << "0>" << root->data << endl;
    vector<bool> Disp;
    Disp.push_back(false);
    if (root->right != NULL)
    {
        Disp.push_back(true);
        DisplaytreeRec(root->right, 0, Disp);
        Disp.pop_back();
    }
    if (root->left != NULL)
    {
        Disp.push_back(false);
        DisplaytreeRec(root->left, 0, Disp);
        Disp.pop_back();
    }
    return;
}

void AVLtree::DisplaytreeRec(shared_ptr<struct AVLnode> root, int height, vector<bool> DispLine)
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

    cout << "0>" << root->data << endl;

    if (root->right != NULL)
    {
        DispLine.push_back(true);
        DisplaytreeRec(root->right, height + 1, DispLine);
        DispLine.pop_back();
    }
    if (root->left != NULL)
    {
        DispLine.push_back(false);
        DisplaytreeRec(root->left, height + 1, DispLine);
        DispLine.pop_back();
    }
    return;
}

void AVLtree::set_Root(shared_ptr<struct AVLnode> root)
{
    this->root = root;
}

shared_ptr<struct AVLnode> AVLtree::get_Root()
{
    return root;
}
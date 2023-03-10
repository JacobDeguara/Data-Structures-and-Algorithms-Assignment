#include <iostream>
#include <vector>
#include <memory>

using namespace std;

struct BSnode
{
    int data;
    int height;
    shared_ptr<struct BSnode> left;
    shared_ptr<struct BSnode> right;
};

class BStree
{
private:
    shared_ptr<struct BSnode> root;

    void DisplaytreeRec(shared_ptr<struct BSnode> root, int height, vector<bool> DispLine);
    void in_OrderRec(shared_ptr<struct BSnode> root);

public:
    shared_ptr<struct BSnode> Create_New_Node(int data);

    BStree(int HeadData);
    BStree(vector<int> ListData);

    shared_ptr<struct BSnode> get_Root();
    void set_Root(shared_ptr<struct BSnode> root);

    int Check_Height(shared_ptr<struct BSnode> root);

    shared_ptr<struct BSnode> Delete_Node(shared_ptr<struct BSnode> root);
    shared_ptr<struct BSnode> Insert_New_Node(shared_ptr<struct BSnode> root, int data);

    shared_ptr<struct BSnode> Delete_From_List(shared_ptr<struct BSnode> root, int Remove);

    void Displaytree(shared_ptr<struct BSnode> root);
    void in_Order(shared_ptr<struct BSnode> root);

    ~BStree() = default;
};

shared_ptr<struct BSnode> BStree::Create_New_Node(int data)
{
    shared_ptr<struct BSnode> temp = make_shared<struct BSnode>();
    temp->data = data;
    temp->height = 1;
    temp->left = temp->right = NULL;
    return temp;
}

BStree::BStree(int HeadData)
{
    root = Create_New_Node(HeadData);
}

BStree::BStree(vector<int> ListData)
{
    root = Create_New_Node(ListData[0]);

    for (size_t i = 1; i < ListData.size(); i++)
    {
        root = Insert_New_Node(root, ListData[i]);
    }
}

shared_ptr<struct BSnode> BStree::Insert_New_Node(shared_ptr<struct BSnode> root, int data)
{
    if (root == NULL)
    {
        return (Create_New_Node(data));
    }
    else if (root->data > data)
    {
        root->left = Insert_New_Node(root->left, data);
    }
    else
    {
        root->right = Insert_New_Node(root->right, data);
    }

    root->height = 1 + max(Check_Height(root->left), Check_Height(root->right));

    return root;
}

shared_ptr<struct BSnode> BStree::Delete_Node(shared_ptr<struct BSnode> root)
{
    if (root->right == NULL && root->left == NULL)
        return NULL;

    if (root->right != NULL && root->left != NULL)
    {
        root->data = root->left->data;
        root->left = Delete_Node(root->left);
    }

    if (root->right == NULL)
    {
        root->data = root->left->data;
        root->left = Delete_Node(root->left);
    }
    else if (root->left == NULL)
    {
        root->data = root->right->data;
        root->right = Delete_Node(root->right);
    }

    root->height = 1 + max(Check_Height(root->left), Check_Height(root->right));

    return root;
}

shared_ptr<struct BSnode> BStree::Delete_From_List(shared_ptr<struct BSnode> root, int Remove)
{
    if (root->left != NULL)
        Delete_From_List(root->left, Remove);

    if (root->right != NULL)
        Delete_From_List(root->right, Remove);

    if (root != NULL)
    {
        if (Remove == root->data)
        {
            root = Delete_Node(root);
        }
    }
    return root;
}

int BStree::Check_Height(shared_ptr<struct BSnode> root)
{
    if (root == NULL)
        return 0;
    return root->height;
}

void BStree::Displaytree(shared_ptr<struct BSnode> root)
{
    if (root == NULL)
    {
        cout << "Empty Tree" << endl;
        return;
    }

    cout << "0>" << root->data << endl;
    vector<bool> Disp;

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

void BStree::DisplaytreeRec(shared_ptr<struct BSnode> root, int height, vector<bool> DispLine)
{

    for (size_t i = 0; i < (height); i++)
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

void BStree::in_Order(shared_ptr<struct BSnode> root)
{
    cout << "List;" << endl;
    in_OrderRec(root);
    cout << endl;
}

void BStree::in_OrderRec(shared_ptr<struct BSnode> root)
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

void BStree::set_Root(shared_ptr<struct BSnode> root)
{
    this->root = root;
}

shared_ptr<struct BSnode> BStree::get_Root()
{
    return root;
}

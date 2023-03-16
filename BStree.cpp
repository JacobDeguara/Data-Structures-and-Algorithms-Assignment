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
    int comparsions;

    void DisplaytreeRec(shared_ptr<struct BSnode> root, int height, vector<bool> DispLine);
    void in_OrderRec(shared_ptr<struct BSnode> root);

public:
    shared_ptr<struct BSnode> Create_New_Node(int data);

    BStree(int HeadData);
    BStree(vector<int> ListData);

    shared_ptr<struct BSnode> get_Root();
    int get_Comparsion();
    void set_Root(shared_ptr<struct BSnode> root);

    int Check_Height(shared_ptr<struct BSnode> root);
    shared_ptr<struct BSnode> MinValue_Node_Search(shared_ptr<struct BSnode> node);

    shared_ptr<struct BSnode> Insert_New_Node(shared_ptr<struct BSnode> root, int data);
    shared_ptr<struct BSnode> Delete_Node(shared_ptr<struct BSnode> root, int Remove);

    void Displaytree(shared_ptr<struct BSnode> root);
    void in_Order(shared_ptr<struct BSnode> root);

    int Node_Amount(shared_ptr<struct BSnode> root);

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
    comparsions = 0;
    root = Create_New_Node(HeadData);
}

BStree::BStree(vector<int> ListData)
{
    comparsions = 0;
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
        this->comparsions += 1;
        return (Create_New_Node(data));
    }
    else if (root->data > data)
    {
        this->comparsions += 2;
        root->left = Insert_New_Node(root->left, data);
    }
    else
    {
        this->comparsions += 2;
        root->right = Insert_New_Node(root->right, data);
    }

    root->height = 1 + max(Check_Height(root->left), Check_Height(root->right));

    return root;
}

shared_ptr<struct BSnode> BStree::MinValue_Node_Search(shared_ptr<struct BSnode> node)
{
    auto current = node;
    while (current->left != NULL)
    {
        this->comparsions += 1;
        current = current->left;
    }
    return current;
}

shared_ptr<struct BSnode> BStree::Delete_Node(shared_ptr<struct BSnode> root, int Remove)
{
    if (root == NULL)
    {
        this->comparsions += 1;
        return root;
    }

    if (Remove < root->data)
    {
        this->comparsions += 2;
        root->left = Delete_Node(root->left, Remove);
    }
    else if (Remove > root->data)
    {
        this->comparsions += 3;
        root->right = Delete_Node(root->right, Remove);
    }
    else
    {
        this->comparsions += 3;
        if ((root->left == NULL) && (root->right == NULL))
        {
            this->comparsions += 1;
            root = NULL;
        }
        else if ((root->left == NULL) || (root->right == NULL))
        {
            this->comparsions += 3;
            root = root->left ? root->left : root->right;
        }
        else
        {
            this->comparsions += 2;
            auto temp = MinValue_Node_Search(root->right);
            root->data = temp->data;
            root->right = Delete_Node(root->right, temp->data);
        }
    }

    if (root != NULL)
        root->height = 1 + max(Check_Height(root->left), Check_Height(root->right));
    this->comparsions += 1;
    return root;
}

int BStree::Check_Height(shared_ptr<struct BSnode> root)
{
    if (root == NULL)
        return 0;
    this->comparsions += 1;
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

int BStree::get_Comparsion()
{
    return this->comparsions;
}

int BStree::Node_Amount(shared_ptr<struct BSnode> root)
{
    int count = 0;
    if (root->right != NULL)
    {
        count += Node_Amount(root->right);
    }

    if (root->left != NULL)
    {
        count += Node_Amount(root->left);
    }
    return count + 1;
}
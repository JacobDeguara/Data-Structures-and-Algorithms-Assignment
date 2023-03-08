#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

struct BSnode
{
    int data;
    shared_ptr<struct BSnode> left;
    shared_ptr<struct BSnode> right;
};

class BStree
{
private:
    /* Head node */
    shared_ptr<struct BSnode> root;

    /* Recursive Display with Parameters sone in Displaytree() */
    void Displaytree2(shared_ptr<struct BSnode> root, int height, vector<bool> DispLine);

public:
    /* Returns a newly created a node */
    shared_ptr<struct BSnode> Create_New_Node(int data);

    /* Constructers that create a tree at root in class */
    BStree(int HeadData);
    /* Constructers that create a tree at root in class */
    BStree(vector<int> ListData);

    /* Deletes root node */
    shared_ptr<struct BSnode> Delete_Node(shared_ptr<struct BSnode> root);

    /* Destructer */
    ~BStree() = default;

    /* Insert new node from head tree */
    shared_ptr<struct BSnode> Insert_New_Node(shared_ptr<struct BSnode> root, int data);

    /* Returns the new tree */
    shared_ptr<struct BSnode> Delete_From_List(shared_ptr<struct BSnode> root, int Remove);

    /* Displays the tree */
    void Displaytree(shared_ptr<struct BSnode> root);

    /* Returns the head node*/
    shared_ptr<struct BSnode> get_Root();

    /* Sets the current Head node to whats passed*/
    void set_Root(shared_ptr<struct BSnode> root);
};

shared_ptr<struct BSnode> BStree::Create_New_Node(int data)
{
    shared_ptr<struct BSnode> temp = make_shared<struct BSnode>();
    temp->data = data;
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
        root = Create_New_Node(data);
        return root;
    }

    if (root->data > data)
    {
        root->left = Insert_New_Node(root->left, data);
    }
    else
    {
        root->right = Insert_New_Node(root->right, data);
    }

    return root;
}

shared_ptr<struct BSnode> BStree::Delete_Node(shared_ptr<struct BSnode> root)
{
    if (root->right == NULL && root->left == NULL)
    {
        return NULL;
    }

    if (root->right != NULL && root->left != NULL)
    {
        auto temp = Create_New_Node(root->left->data);
        temp->right = root->right;
        temp->left = Delete_Node(root->left);
        return temp;
    }

    if (root->right == NULL)
    {
        auto temp = Create_New_Node(root->left->data);
        temp->left = Delete_Node(root->left);
        return temp;
    }
    else if (root->left == NULL)
    {
        auto temp = Create_New_Node(root->right->data);
        temp->right = Delete_Node(root->right);
        return temp;
    }
    return NULL;
}

shared_ptr<struct BSnode> BStree::Delete_From_List(shared_ptr<struct BSnode> root, int Remove)
{
    if (root->left != NULL)
    {
        Delete_From_List(root->left, Remove);
    }

    if (root->right != NULL)
    {
        Delete_From_List(root->right, Remove);
    }

    if (root != NULL)
    {
        if (Remove == root->data)
        {
            root = Delete_Node(root);
        }
    }
    return root;
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
        Displaytree2(root->right, 0, Disp);
        Disp.pop_back();
    }
    if (root->left != NULL)
    {
        Disp.push_back(false);
        Displaytree2(root->left, 0, Disp);
        Disp.pop_back();
    }
    return;
}

void BStree::Displaytree2(shared_ptr<struct BSnode> root, int height, vector<bool> DispLine)
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
        Displaytree2(root->right, height + 1, DispLine);
        DispLine.pop_back();
    }
    if (root->left != NULL)
    {
        DispLine.push_back(false);
        Displaytree2(root->left, height + 1, DispLine);
        DispLine.pop_back();
    }
    return;
}

void BStree::set_Root(shared_ptr<struct BSnode> root)
{
    this->root = root;
}

shared_ptr<struct BSnode> BStree::get_Root()
{
    return root;
}

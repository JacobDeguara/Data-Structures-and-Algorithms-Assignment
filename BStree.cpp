#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

struct BSnode
{
    int data;
    struct BSnode *left;
    struct BSnode *right;
};

class BStree
{
private:
    struct BSnode *root;
    void Displaytree2(struct BSnode *root, int n);

public:
    struct BSnode *Create_New_Node(int data);
    BStree(int HeadData);
    BStree(vector<int> ListData);

    void Delete_Tree(struct BSnode *root);
    ~BStree();

    struct BSnode *Insert_New_Node(struct BSnode *root, int data);
    void Displaytree(struct BSnode *root);
};

struct BSnode *BStree::Create_New_Node(int data)
{
    struct BSnode *temp = (struct BSnode *)malloc(sizeof(struct BSnode));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

void BStree::Delete_Tree(struct BSnode *root)
{
    if (root == NULL)
        return;

    if (root->right != NULL)
    {
        Delete_Tree(root->right);
    }

    if (root->left != NULL)
    {
        Delete_Tree(root->left);
    }

    free(root);
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
        // insert New Nodes;
    }
}

struct BSnode *BStree::Insert_New_Node(struct BSnode *root, int data)
{
    if (root == NULL)
    {
        root = Create_New_Node(data);
        return root;
    }

    if (root->data < data)
    {
        root->left = Insert_New_Node(root->left, data);
    }
    else
    {
        root->right = Insert_New_Node(root->right, data);
    }

    return root;
}

BStree::~BStree()
{
    Delete_Tree(root);
}

void BStree::Displaytree(struct BSnode *root)
{
    cout << L"▷" << root->data << endl;

    if (root->right != NULL)
    {
        Displaytree2(root->right, 0);
    }
    if (root->left != NULL)
    {
        Displaytree2(root->left, 0);
    }
    return;
}

void BStree::Displaytree2(struct BSnode *root, int height)
{
    for (size_t i = 0; i < (height); i++)
    {
        cout << " ";
    }

    cout << L"┗▷" << root->data << endl;

    if (root->right != NULL)
    {
        Displaytree2(root->right, height + 1);
    }
    if (root->left != NULL)
    {
        Displaytree2(root->left, height + 1);
    }
    return;
}

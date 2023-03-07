#include <stdlib.h>
#include <iostream>

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
    struct BSnode *BStree::Create_New_Node(int data);

public:
    BStree(int HeadData);

    void Delete_Tree(struct BSnode *root);
    ~BStree();
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

BStree::~BStree()
{
    Delete_Tree(root);
}

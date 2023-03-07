#include <stdlib.h>
#include <iostream>

using namespace std;

struct AVLnode
{
    int data;
    struct AVLnode *left;
    struct AVLnode *right;
};

class AVLtree
{
private:
    struct AVLnode *root;

public:
    struct AVLnode *Create_New_Node(int data);
    AVLtree(int HeadData);

    void Delete_Tree(struct AVLnode *root);
    ~AVLtree();
};

struct AVLnode *AVLtree::Create_New_Node(int data)
{
    struct AVLnode *temp = (struct AVLnode *)malloc(sizeof(struct AVLnode));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

void AVLtree::Delete_Tree(struct AVLnode *root)
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

AVLtree::AVLtree(int HeadData)
{
    root = Create_New_Node(HeadData);
}

AVLtree::~AVLtree()
{
    Delete_Tree(root);
}

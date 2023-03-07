#include <stdlib.h>
#include <iostream>

using namespace std;

enum RB
{
    Red = false,
    Black = true
};

struct RBnode
{
    int data;
    RB Type;
    struct RBnode *left;
    struct RBnode *right;
};

class RBtree
{
private:
    struct RBnode *root;

public:
    struct RBnode *Create_New_Node(int data, RB Type);
    RBtree(int data, RB Type);

    void Delete_Tree(struct RBnode *root);
    ~RBtree();
};

struct RBnode *RBtree::Create_New_Node(int data, RB Type)
{
    struct RBnode *temp = (struct RBnode *)malloc(sizeof(struct RBnode));
    temp->data = data;
    temp->Type = Type;
    temp->left = temp->right = NULL;
    return temp;
}

void RBtree::Delete_Tree(struct RBnode *root)
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

RBtree::RBtree(int data, RB Type)
{
    root = Create_New_Node(data, Type);
}

RBtree::~RBtree()
{
    Delete_Tree(root);
}

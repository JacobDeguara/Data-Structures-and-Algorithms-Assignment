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
    struct AVLnode *Create_New_Node(int data);

public:
    AVLtree(int HeadData);
    ~AVLtree();
};

struct AVLnode *AVLtree::Create_New_Node(int data)
{
    struct AVLnode *temp = (struct AVLnode *)malloc(sizeof(struct AVLnode));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

AVLtree::AVLtree(int HeadData)
{
    root = Create_New_Node(HeadData);
}

AVLtree::~AVLtree()
{
}

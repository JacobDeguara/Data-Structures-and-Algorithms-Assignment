#include <iostream>
#include <vector>
#include <memory>

using namespace std;

struct AVLnode
{
    int data;
    shared_ptr<struct AVLnode> left;
    shared_ptr<struct AVLnode> right;
};

class AVLtree
{
private:
    shared_ptr<struct AVLnode> root;

public:
    shared_ptr<struct AVLnode> Create_New_Node(int data);
    AVLtree(int HeadData);

    shared_ptr<struct AVLnode> LLRotation(shared_ptr<struct AVLnode> root);
    shared_ptr<struct AVLnode> RRRotation(shared_ptr<struct AVLnode> root);
    shared_ptr<struct AVLnode> RLRotation(shared_ptr<struct AVLnode> root);
    shared_ptr<struct AVLnode> LRRotation(shared_ptr<struct AVLnode> root);

    shared_ptr<struct AVLnode> getRoot();
    ~AVLtree() = default;
};

shared_ptr<struct AVLnode> AVLtree::Create_New_Node(int data)
{
    shared_ptr<struct AVLnode> temp = make_shared<struct AVLnode>();
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

AVLtree::AVLtree(int HeadData)
{
    root = Create_New_Node(HeadData);
}

shared_ptr<struct AVLnode> AVLtree::LLRotation(shared_ptr<struct AVLnode> root)
{
    auto rootLeft = root->left;
    root->left = rootLeft->right;
    rootLeft->right = root;
    return rootLeft;
}
shared_ptr<struct AVLnode> AVLtree::RRRotation(shared_ptr<struct AVLnode> root)
{
    auto rootRight = root->right;
    root->right = rootRight->left;
    rootRight->left = root;
    return rootRight;
}
shared_ptr<struct AVLnode> AVLtree::RLRotation(shared_ptr<struct AVLnode> root)
{
    root->right = LLRotation(root->right);
    return RRRotation(root);
}
shared_ptr<struct AVLnode> AVLtree::LRRotation(shared_ptr<struct AVLnode> root)
{
    root->left = RRRotation(root->left);
    return LLRotation(root);
}

shared_ptr<struct AVLnode> AVLtree::getRoot()
{
    return root;
}
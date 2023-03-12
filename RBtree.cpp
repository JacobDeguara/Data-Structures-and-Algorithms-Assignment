#include <iostream>
#include <vector>
#include <memory>

using namespace std;

enum RB
{
    Red = true,
    Black = false
};

struct RBnode
{
    int data;
    RB Type;
    shared_ptr<struct RBnode> parent;
    shared_ptr<struct RBnode> left;
    shared_ptr<struct RBnode> right;
};

class RBtree
{
private:
    shared_ptr<struct RBnode> root;

public:
    shared_ptr<struct RBnode> Create_New_Node(int data, RB Type);
    RBtree(int data);

    shared_ptr<struct RBnode> get_root();
    void set_root(shared_ptr<struct RBnode> root);

    shared_ptr<struct RBnode> Insert_Node(shared_ptr<struct RBnode> root, int data);
    shared_ptr<struct RBnode> Delete_Node(shared_ptr<struct RBnode> root, int data);

    shared_ptr<struct RBnode> RRRotation(shared_ptr<struct RBnode> root);
    shared_ptr<struct RBnode> LLRotation(shared_ptr<struct RBnode> root);

    ~RBtree() = default;
};

shared_ptr<struct RBnode> RBtree::Create_New_Node(int data, RB Type)
{
    shared_ptr<struct RBnode> temp = make_shared<struct RBnode>();
    temp->data = data;
    temp->Type = Type;
    temp->left = temp->right = temp->parent = NULL;
    return temp;
}

shared_ptr<struct RBnode> RBtree::Insert_Node(shared_ptr<struct RBnode> root, int data)
{
    if (root == NULL)
        root = Create_New_Node(data, Black);
    return root;

    auto newNode = Create_New_Node(data, Red);
    shared_ptr<struct RBnode> parent = NULL;
    auto currentNode = root;

    while (currentNode != NULL)
    {
        parent = currentNode;
        if (data < currentNode->data)
            currentNode = currentNode->left;
        else
            currentNode = currentNode->right;
    }

    newNode->parent = parent;
    if (newNode->data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    if (newNode->parent->parent == NULL)
    {
        return root;
    }

    // Fix_Tree_Insert();
    return root;
}

shared_ptr<struct RBnode> RBtree::Delete_Node(shared_ptr<struct RBnode> root, int data)
{
    return NULL;
}

shared_ptr<struct RBnode> RBtree::RRRotation(shared_ptr<struct RBnode> root)
{
    auto rootL = root->left;
    auto rootLR = rootL->right;
    rootL->right = root;
    root->left = rootLR;
    return rootL;
}

shared_ptr<struct RBnode> RBtree::LLRotation(shared_ptr<struct RBnode> root)
{
    auto rootR = root->right;
    auto rootRL = rootR->left;
    rootR->left = root;
    root->right = rootRL;
    return rootR;
}

RBtree::RBtree(int data)
{
    root = Create_New_Node(data, Black);
}

shared_ptr<struct RBnode> RBtree::get_root()
{
    return this->root;
}
void RBtree::set_root(shared_ptr<struct RBnode> root)
{
    this->root = root;
}

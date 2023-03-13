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

    shared_ptr<struct RBnode> RRRotation(shared_ptr<struct RBnode> root);
    shared_ptr<struct RBnode> LLRotation(shared_ptr<struct RBnode> root);

    void Fix_Tree_Insert(shared_ptr<struct RBnode> root);
    void LLViolation(shared_ptr<struct RBnode> root, shared_ptr<struct RBnode> parent, shared_ptr<struct RBnode> grandparent);
    void RRViolation(shared_ptr<struct RBnode> root, shared_ptr<struct RBnode> parent, shared_ptr<struct RBnode> grandparent);
    void RLViolation(shared_ptr<struct RBnode> root, shared_ptr<struct RBnode> parent, shared_ptr<struct RBnode> grandparent);
    void LRViolation(shared_ptr<struct RBnode> root, shared_ptr<struct RBnode> parent, shared_ptr<struct RBnode> grandparent);

public:
    shared_ptr<struct RBnode> Create_New_Node(int data, RB Type);
    RBtree(int data);
    RBtree(vector<int> Listdata);

    shared_ptr<struct RBnode> get_root();
    void set_root(shared_ptr<struct RBnode> root);

    shared_ptr<struct RBnode> Insert_Node(shared_ptr<struct RBnode> root, int data);
    shared_ptr<struct RBnode> Delete_Node(shared_ptr<struct RBnode> root, int data);

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

    Fix_Tree_Insert(newNode);
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

void RBtree::Fix_Tree_Insert(shared_ptr<struct RBnode> root)
{
    shared_ptr<struct RBnode> temp = NULL;
    auto parent = root->parent;
    auto grandParent = root->parent->parent;

    if (parent->Type) // Red = True
    {
        if (parent == grandParent->right) // GrandParent->right == parent
        {
            if (root == parent->right) // Parent->right == root
            {
                temp = grandParent->left;
                if (temp != NULL) // GrandParent->left != NULL
                {
                    if (temp->Type) // GrandParent->Left->Type is Red
                    {
                        if (grandParent->parent != NULL) // is not root
                        {
                            grandParent->Type = Red;
                        }
                        parent->Type = Black;
                        temp->Type = Black;
                    }
                    else // else GrandParent->Left->Type is Black
                    {
                        RRViolation(root, parent, grandParent);
                    }
                }
                else // GrandParent->left == NULL
                {
                    RRViolation(root, parent, grandParent);
                }
            }
            else // parent->left == root
            {
                temp = grandParent->right;
                if (temp != NULL) // GrandParent->right != NULL
                {
                    if (temp->Type) // GrandParent->Right->Type is Red
                    {
                        if (grandParent->parent != NULL) // is not root
                        {
                            grandParent->Type = Red;
                        }
                        parent->Type = Black;
                        temp->Type = Black;
                    }
                    else // else GrandParent->right->Type is Black
                    {
                        RLViolation(root, parent, grandParent);
                    }
                }
                else // GrandParent->right == NULL
                {
                    RLViolation(root, parent, grandParent);
                }
            }
        }
        else if (parent == grandParent->left) // grandParent->left == parent
        {
            if (root == parent->left) // parent->left == root
            {
                temp = grandParent->right;
                if (temp != NULL) // if grandParent->right != NULL
                {
                    if (temp->Type) // if grandParent-> type == Red
                    {
                        if (grandParent->parent != NULL) // is not root
                        {
                            grandParent->Type = Red;
                        }
                        parent->Type = Black;
                        temp->Type = Black;
                    }
                    else // grandParent->type == Black
                    {
                        LLViolation(root, parent, grandParent);
                    }
                }
                else // grandparent->right == NULL
                {
                    LLViolation(root, parent, grandParent);
                }
            }
            else if (root == parent->right) // parent->right == root
            {
                temp = grandParent->right;
                if (temp != NULL) // if grandParent->right != NULL
                {
                    if (temp->Type) // if grandParent-> type == Red
                    {
                        if (grandParent->parent != NULL) // is not root
                        {
                            grandParent->Type = Red;
                        }
                        parent->Type = Black;
                        temp->Type = Black;
                    }
                    else // grandParent->type == Black
                    {
                        LRViolation(root, parent, grandParent);
                    }
                }
                else // grandparent->right == NULL
                {
                    LRViolation(root, parent, grandParent);
                }
            }
        }
    }
}

void RBtree::LLViolation(shared_ptr<struct RBnode> root, shared_ptr<struct RBnode> parent, shared_ptr<struct RBnode> grandParent)
{
    if (grandParent->parent == NULL) // is root
    {
        this->root = RRRotation(grandParent);

        grandParent->parent = parent;
        grandParent->Type = Red;
        parent->parent = NULL;
        parent->Type = Black;
    }
    else // is not root
    {
        auto grandgrandParent = grandParent->parent; // GrandParent's Parent
        if (grandgrandParent->right == grandParent)  // grandgrandParent->right == grandParent
        {
            grandgrandParent->right = RRRotation(grandParent);
        }
        else // else  grandgrandParent->left == grandParent
        {
            grandgrandParent->left = RRRotation(grandParent);
        }

        grandParent->parent = parent;
        grandParent->Type = Red;
        parent->parent = grandgrandParent;
        parent->Type = Black;
    }
}

void RBtree::RRViolation(shared_ptr<struct RBnode> root, shared_ptr<struct RBnode> parent, shared_ptr<struct RBnode> grandParent)
{
    if (grandParent->parent == NULL) // is root
    {
        this->root = LLRotation(grandParent);
        grandParent->parent = parent;
        grandParent->Type = Red;
        parent->parent = NULL;
        parent->Type = Black;
    }
    else
    {
        auto grandgrandParent = grandParent->parent; // GrandParent's Parent
        if (grandgrandParent->right == grandParent)  // grandgrandParent->right == grandParent
        {
            grandgrandParent->right = LLRotation(grandParent);
        }
        else // else  grandgrandParent->left == grandParent
        {
            grandgrandParent->left = LLRotation(grandParent);
        }

        grandParent->parent = parent;
        grandParent->Type = Red;
        parent->parent = grandgrandParent;
        parent->Type = Black;
    }
}
void RBtree::RLViolation(shared_ptr<struct RBnode> root, shared_ptr<struct RBnode> parent, shared_ptr<struct RBnode> grandParent)
{
    if (grandParent->parent == NULL) // is root
    {
        grandParent->right = RRRotation(parent);
        this->root = LLRotation(grandParent);

        grandParent->parent = root;
        grandParent->Type = Red;
        parent->parent = root;
        parent->Type = Red;
        root->parent = NULL;
        root->Type = Black;
    }
    else
    {
        auto grandgrandParent = grandParent->parent; // GrandParent's Parent
        if (grandgrandParent->right == grandParent)  // grandgrandParent->right == grandParent
        {
            grandParent->right = RRRotation(parent);
            grandgrandParent->right = LLRotation(grandParent);
        }
        else // else  grandgrandParent->left == grandParent
        {
            grandParent->right = RRRotation(parent);
            grandgrandParent->left = LLRotation(grandParent);
        }

        grandParent->parent = root;
        grandParent->Type = Red;
        parent->parent = root;
        parent->Type = Red;
        root->parent = grandgrandParent;
        root->Type = Black;
    }
}
void RBtree::LRViolation(shared_ptr<struct RBnode> root, shared_ptr<struct RBnode> parent, shared_ptr<struct RBnode> grandParent)
{
    if (grandParent->parent == NULL) // is root
    {
        grandParent->left = LLRotation(parent);
        this->root = RRRotation(grandParent);

        grandParent->parent = root;
        grandParent->Type = Red;
        parent->parent = root;
        parent->Type = Red;
        root->parent = NULL;
        root->Type = Black;
    }
    else // is not root
    {
        auto grandgrandParent = grandParent->parent; // GrandParent's Parent
        if (grandgrandParent->right == grandParent)  // grandgrandParent->right == grandParent
        {
            grandParent->left = LLRotation(parent);
            grandgrandParent->right = RRRotation(grandParent);
        }
        else // else  grandgrandParent->left == grandParent
        {
            grandParent->left = LLRotation(parent);
            grandgrandParent->left = RRRotation(grandParent);
        }

        grandParent->parent = root;
        grandParent->Type = Red;
        parent->parent = root;
        parent->Type = Red;
        root->parent = grandgrandParent;
        root->Type = Black;
    }
}

RBtree::RBtree(int data)
{
    root = Create_New_Node(data, Black);
}

RBtree::RBtree(vector<int> Listdata)
{
    for (size_t i = 0; i < Listdata.size(); i++)
    {
        root = Insert_Node(get_root(), Listdata[i]);
    }
}

shared_ptr<struct RBnode> RBtree::get_root()
{
    return this->root;
}
void RBtree::set_root(shared_ptr<struct RBnode> root)
{
    this->root = root;
}

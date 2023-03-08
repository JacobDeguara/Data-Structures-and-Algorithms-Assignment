#include <iostream>
#include <vector>
#include <memory>

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

    ~RBtree() = default;
};

shared_ptr<struct RBnode> RBtree::Create_New_Node(int data, RB Type)
{
    shared_ptr<struct RBnode> temp = make_shared<struct RBnode>();
    temp->data = data;
    temp->Type = Type;
    temp->left = temp->right = NULL;
    return temp;
}

RBtree::RBtree(int data)
{
    root = Create_New_Node(data, Black);
}

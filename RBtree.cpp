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
    /* data */
public:
    RBtree(/* args */);
    ~RBtree();
};

RBtree::RBtree(/* args */)
{
}

RBtree::~RBtree()
{
}

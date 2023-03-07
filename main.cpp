#include <iostream>
#include "Log.cpp"
#include "BStree.cpp"
#include "AVLtree.cpp"
#include "RBtree.cpp"

int main()
{
    AVLtree avlTree = AVLtree(12);
    RBtree rbTree = RBtree(12);
    BStree bsTree = BStree(12);
    return 0;
}
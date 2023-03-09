#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>

#include "Log.cpp"
#include "BStree.cpp"
#include "AVLtree.cpp"
#include "RBtree.cpp"

bool compare(int x, int y)
{
    if (x == y)
    {
        return true;
    }
    return false;
}

int main()
{
    std::random_device dev;
    std::mt19937 rngX(dev());
    std::mt19937 rngY(dev());
    std::mt19937 rngZ(dev());
    std::mt19937 rngSize(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist33(-3000, 3000);
    std::uniform_int_distribution<std::mt19937::result_type> dist13(1000, 3000);
    std::uniform_int_distribution<std::mt19937::result_type> dist51(500, 1000);

    vector<int> ListX;
    vector<int> ListY;
    vector<int> ListZ;
    vector<int> Simple;

    for (size_t i = 0; i < dist13(rngSize); i++)
    {
        ListX.push_back(dist33(rngX));
        while (std::adjacent_find(ListX.begin(), ListX.end()) != ListX.end())
        {
            ListX[i] = dist33(rngX);
        }
    }
    for (size_t i = 0; i < dist51(rngSize); i++)
    {
        ListY.push_back(dist33(rngY));
        while (std::adjacent_find(ListY.begin(), ListY.end()) != ListY.end())
        {
            ListY[i] = dist33(rngY);
        }
    }
    for (size_t i = 0; i < dist51(rngSize); i++)
    {
        ListZ.push_back(dist33(rngZ));
        while (std::adjacent_find(ListZ.begin(), ListZ.end()) != ListZ.end())
        {
            ListZ[i] = dist33(rngZ);
        }
    }
    for (size_t i = 0; i < 25; i++)
    {
        Simple.push_back(i);
    }

    shuffle(Simple.begin(), Simple.end(), default_random_engine(dev()));

    auto Xtest = std::adjacent_find(ListX.begin(), ListX.end());
    auto Ytest = std::adjacent_find(ListY.begin(), ListY.end());
    auto Ztest = std::adjacent_find(ListZ.begin(), ListZ.end());

    if (Xtest != ListX.end())
    {
        cerr << "Duplicate elements Found in List X";
        return -1;
    }

    if (Ytest != ListY.end())
    {
        cerr << "Duplicate elements Found in List Y";
        return -1;
    }

    if (Ztest != ListZ.end())
    {
        cerr << "Duplicate elements Found in List Z";
        return -1;
    }

    // RBtree rbTree = RBtree(12);

    BStree bsTree = BStree(Simple);
    bsTree.in_Order(bsTree.get_Root());
    bsTree.Displaytree(bsTree.get_Root());
    /*
    bsTree.set_Root(bsTree.Delete_Node(bsTree.get_Root()));
    bsTree.in_Order(bsTree.get_Root());
    */

    AVLtree avlTree = AVLtree(Simple);
    avlTree.in_Order(avlTree.getRoot());
    avlTree.Displaytree(avlTree.getRoot());
    cout << avlTree.Check_Height(avlTree.getRoot());
    return 0;
}
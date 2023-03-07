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
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(-3000, 3000);

    vector<int> ListX;

    for (size_t i = 0; i < 25; i++)
    {
        ListX.push_back(dist6(rng));
    }

    random_shuffle(ListX.begin(), ListX.end());

    auto Xtest = std::adjacent_find(ListX.begin(), ListX.end());

    if (Xtest != ListX.end())
    {
        cout << "Duplicate elements Found";
        return 0;
    }

    // AVLtree avlTree = AVLtree(12);
    // RBtree rbTree = RBtree(12);

    BStree bsTree = BStree(ListX);

    bsTree.Displaytree(bsTree.get_Root());

    auto NEWROOT = bsTree.Delete_From_List(bsTree.get_Root(), ListX);

    bsTree.Displaytree(bsTree.get_Root());

    return 0;
}
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>

#include "Log.cpp"
#include "BStree.cpp"
#include "AVLtree.cpp"
#include "RBtree.cpp"

void Simple_test();

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

    // RBtree rbTree = RBtree(12);

    Simple_test();

    return 0;
}

void Simple_test()
{
    std::random_device dev;
    vector<int> Simple;
    for (size_t i = 0; i < 25; i++)
    {
        Simple.push_back(i);
    }
    shuffle(Simple.begin(), Simple.end(), default_random_engine(dev()));

    BStree bsTree = BStree(Simple);
    bsTree.in_Order(bsTree.get_Root());
    bsTree.Displaytree(bsTree.get_Root());
    cout << "Height :" << bsTree.Check_Height(bsTree.get_Root()) << endl;

    AVLtree avlTree = AVLtree(Simple);
    avlTree.in_Order(avlTree.get_Root());
    avlTree.Displaytree(avlTree.get_Root());
    cout << "Height :" << avlTree.Check_Height(avlTree.get_Root()) << endl;

    RBtree rbTree = RBtree(Simple);

    shuffle(Simple.begin(), Simple.end(), default_random_engine(dev()));

    Simple.resize(5);

    for (size_t i = 0; i < Simple.size(); i++)
    {
        cout << "Deleting: " << Simple[i] << endl;
        bsTree.set_Root(bsTree.Delete_Node(bsTree.get_Root(), Simple[i]));
        bsTree.in_Order(bsTree.get_Root());
    }

    bsTree.Displaytree(bsTree.get_Root());
    cout << "Height :" << bsTree.Check_Height(bsTree.get_Root()) << endl;

    for (size_t i = 0; i < Simple.size(); i++)
    {
        cout << "Deleting: " << Simple[i] << endl;
        avlTree.set_Root(avlTree.Delete_Node(avlTree.get_Root(), Simple[i]));
        avlTree.in_Order(avlTree.get_Root());
    }

    avlTree.Displaytree(avlTree.get_Root());
    cout << "Height :" << avlTree.Check_Height(avlTree.get_Root()) << endl;
}
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>

#include "Log.cpp"
#include "BStree.cpp"
#include "AVLtree.cpp"
#include "RBtree.cpp"

void Simple_test();

vector<int> intersection(vector<int> v1, vector<int> v2);

bool isDuplicate(vector<int> list);

int main()
{
    // Creating a list of random numbers
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
        while (isDuplicate(ListX))
        {
            ListX[i] = dist33(rngX);
        }
    }

    for (size_t i = 0; i < dist51(rngSize); i++)
    {
        ListY.push_back(dist33(rngY));
        while (isDuplicate(ListY))
        {
            ListY[i] = dist33(rngY);
        }
    }

    for (size_t i = 0; i < dist51(rngSize); i++)
    {
        ListZ.push_back(dist33(rngZ));
        while (isDuplicate(ListZ))
        {
            ListZ[i] = dist33(rngZ);
        }
    }

    // Log size of lists and intersection
    string message;
    Log log = Log("result.txt");

    message = "Set X contains " + to_string(ListX.size()) + " integers";
    log.Write(message);
    cout << message << endl;

    message = "Set Y contains " + to_string(ListY.size()) + " integers";
    log.Write(message);
    cout << message << endl;

    message = "Set Z contains " + to_string(ListZ.size()) + " integers";
    log.Write(message);
    cout << message << endl;

    auto IntersectionXY = intersection(ListX, ListY);
    message = "Sets X and Y have " + to_string(IntersectionXY.size()) + " values in common";
    log.Write(message);
    cout << message << endl;

    auto IntersectionXZ = intersection(ListX, ListZ);
    message = "Sets X and Z have " + to_string(IntersectionXZ.size()) + " values in common";
    log.Write(message);
    cout << message << endl;
    cout << endl;

    // Inserting ListX into each tree
    BStree bsTree = BStree(ListX);
    AVLtree avlTree = AVLtree(ListX);
    RBtree rbTree = RBtree(ListX);

    message = "AVL: " + to_string(avlTree.get_Rotation()) + " tot. rotations req." +
              ", height is " + to_string(avlTree.Check_Height(avlTree.get_Root())) +
              ", #nodes is " + to_string(avlTree.Node_Amount(avlTree.get_Root())) +
              ", #comparisons is " + to_string(avlTree.get_Comparsion()) + ".";
    log.Write(message);
    cout << message << endl;

    message = "RBT: " + to_string(rbTree.get_Rotation()) + " tot. rotations req." +
              ", height is " + to_string(rbTree.Check_Height(rbTree.get_Root())) +
              ", #nodes is " + to_string(rbTree.Node_Amount(rbTree.get_Root())) +
              ", #comparisons is " + to_string(rbTree.get_Comparsion()) + ".";
    log.Write(message);
    cout << message << endl;

    message = "BST: height is " + to_string(bsTree.Check_Height(bsTree.get_Root())) +
              ", #nodes is " + to_string(bsTree.Node_Amount(bsTree.get_Root())) +
              ", #comparisons is " + to_string(bsTree.get_Comparsion()) + ".";
    log.Write(message);
    cout << message << endl;

    int BSTree_Comparsions_Amount = bsTree.get_Comparsion();
    int AVLTree_Comparsions_Amount = avlTree.get_Comparsion();
    int RBTree_Comparsions_Amount = rbTree.get_Comparsion();

    int AVLTree_Rotations_Amount = avlTree.get_Rotation();
    int RBTree_Rotations_Amount = rbTree.get_Rotation();
    cout << endl;

    // Deleteing ListY from each tree

    bsTree.Delete_List(ListY);
    avlTree.Delete_List(ListY);
    rbTree.Delete_List(ListY);

    message = "AVL: " + to_string(avlTree.get_Rotation() - AVLTree_Rotations_Amount) + " tot. rotations req." +
              ", height is " + to_string(avlTree.Check_Height(avlTree.get_Root())) +
              ", #nodes is " + to_string(avlTree.Node_Amount(avlTree.get_Root())) +
              ", #comparisons is " + to_string(avlTree.get_Comparsion() - AVLTree_Comparsions_Amount) + ".";
    log.Write(message);
    cout << message << endl;

    message = "RBT: " + to_string(rbTree.get_Rotation() - RBTree_Rotations_Amount) + " tot. rotations req." +
              ", height is " + to_string(rbTree.Check_Height(rbTree.get_Root())) +
              ", #nodes is " + to_string(rbTree.Node_Amount(rbTree.get_Root())) +
              ", #comparisons is " + to_string(rbTree.get_Comparsion() - RBTree_Comparsions_Amount) + ".";
    log.Write(message);
    cout << message << endl;

    message = "BST: height is " + to_string(bsTree.Check_Height(bsTree.get_Root())) +
              ", #nodes is " + to_string(bsTree.Node_Amount(bsTree.get_Root())) +
              ", #comparisons is " + to_string(bsTree.get_Comparsion() - BSTree_Comparsions_Amount) + ".";
    log.Write(message);
    cout << message << endl;

    BSTree_Comparsions_Amount = bsTree.get_Comparsion();
    AVLTree_Comparsions_Amount = avlTree.get_Comparsion();
    RBTree_Comparsions_Amount = rbTree.get_Comparsion();

    AVLTree_Rotations_Amount = avlTree.get_Rotation();
    RBTree_Rotations_Amount = rbTree.get_Rotation();
    cout << endl;

    // Search for ListZ values in tree
    int BSTree_Found_Value;
    int BSTree_Not_Found_Value;
    int AVLTree_Found_Value;
    int AVLTree_Not_Found_Value;
    int RBTree_Found_Value;
    int RBTree_Not_Found_Value;

    for (size_t i = 0; i < ListZ.size(); i++)
    {
        if (bsTree.Search(bsTree.get_Root(), ListZ[i]))
            BSTree_Found_Value++;
        else
            BSTree_Not_Found_Value++;

        if (avlTree.Search(avlTree.get_Root(), ListZ[i]))
            AVLTree_Found_Value++;
        else
            AVLTree_Not_Found_Value++;

        if (rbTree.Search(rbTree.get_Root(), ListZ[i]))
            RBTree_Found_Value++;
        else
            RBTree_Not_Found_Value++;
    }

    message = "AVL: " +
              to_string(avlTree.get_Comparsion() - AVLTree_Comparsions_Amount) + " total comparisons required, " +
              to_string(AVLTree_Found_Value) + " numbers found, " +
              to_string(AVLTree_Not_Found_Value) + " numbers not found.";
    log.Write(message);
    cout << message << endl;

    message = "RBT: " +
              to_string(rbTree.get_Comparsion() - RBTree_Comparsions_Amount) + " total comparisons required, " +
              to_string(RBTree_Found_Value) + " numbers found, " +
              to_string(RBTree_Not_Found_Value) + " numbers not found.";
    log.Write(message);
    cout << message << endl;

    message = "BST: " +
              to_string(bsTree.get_Comparsion() - BSTree_Comparsions_Amount) + " total comparisons required, " +
              to_string(BSTree_Found_Value) + " numbers found, " +
              to_string(BSTree_Not_Found_Value) + " numbers not found.";
    log.Write(message);
    cout << message << endl;

    // Simple_test();

    return 0;
}

vector<int> intersection(vector<int> v1, vector<int> v2)
{
    vector<int> v3;

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));
    return v3;
}

bool isDuplicate(vector<int> list)
{
    for (size_t i = 0; i < (list.size() - 1); i++)
    {
        if (list[i] == list[(list.size() - 1)])
            return true;
    }
    return false;
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

    cout << "Amount of Nodes:" + to_string(bsTree.Node_Amount(bsTree.get_Root())) << endl;

    AVLtree avlTree = AVLtree(Simple);
    avlTree.in_Order(avlTree.get_Root());

    cout << "Amount of Nodes:" + to_string(avlTree.Node_Amount(avlTree.get_Root())) << endl;

    RBtree rbTree = RBtree(Simple);
    cout << "List;" << endl;
    rbTree.In_Order();
    cout << endl;

    cout << "Amount of Nodes:" + to_string(rbTree.Node_Amount(rbTree.get_Root())) << endl;
}
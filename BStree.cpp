#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

struct BSnode
{
    int data;
    struct BSnode *left;
    struct BSnode *right;
};

class BStree
{
private:
    /* Head node */
    struct BSnode *root;

    /* Recursive Display with Parameters sone in Displaytree() */
    void Displaytree2(struct BSnode *root, int height, vector<bool> DispLine);

public:
    /* Returns a newly created a node */
    struct BSnode *Create_New_Node(int data);

    /* Constructers that create a tree at root in class */
    BStree(int HeadData);
    /* Constructers that create a tree at root in class */
    BStree(vector<int> ListData);

    /* Deletes root node */
    struct BSnode *Delete_Node(struct BSnode *root);
    /* Deletes entire tree from root */
    void Delete_Tree(struct BSnode *root);

    /* Destructer */
    ~BStree();

    /* Insert new node from head tree */
    struct BSnode *Insert_New_Node(struct BSnode *root, int data);

    /* Returns the new tree with one function for comparison and one function for application*/
    struct BSnode *Func_Apply(struct BSnode *root, bool (*comp)(int, int), struct BSnode *(*apply)(struct BSnode *))

        /* Displays the tree */
        void Displaytree(struct BSnode *root);

    /* Returns the head node*/
    struct BSnode *get_Root();

    /* Sets the current Head node to whats passed*/
    void set_Root(struct BSnode *root);
};

struct BSnode *BStree::Create_New_Node(int data)
{
    struct BSnode *temp = (struct BSnode *)malloc(sizeof(struct BSnode));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

void BStree::Delete_Tree(struct BSnode *root)
{
    if (root == NULL)
        return;

    if (root->right != NULL)
    {
        Delete_Tree(root->right);
    }

    if (root->left != NULL)
    {
        Delete_Tree(root->left);
    }

    free(root);
}

BStree::BStree(int HeadData)
{
    root = Create_New_Node(HeadData);
}

BStree::BStree(vector<int> ListData)
{
    root = Create_New_Node(ListData[0]);

    for (size_t i = 1; i < ListData.size(); i++)
    {
        root = Insert_New_Node(root, ListData[i]);
    }
}

struct BSnode *BStree::Insert_New_Node(struct BSnode *root, int data)
{
    if (root == NULL)
    {
        root = Create_New_Node(data);
        return root;
    }

    if (root->data < data)
    {
        root->left = Insert_New_Node(root->left, data);
    }
    else
    {
        root->right = Insert_New_Node(root->right, data);
    }

    return root;
}

struct BSnode *BStree::Delete_Node(struct BSnode *root)
{
    if (root->right == NULL && root->left == NULL)
    {
        free(root);
        return NULL;
    }

    if (root->right != NULL && root->left != NULL)
    {
        auto rootLeft = root->left;
        rootLeft->right = root->right;
        rootLeft->left = Delete_Node(root->left);
        free(root);
        return rootLeft;
    }

    if (root->right == NULL)
    {
        auto rootLeft = root->left;
        free(root);
        return rootLeft;
    }
    else
    {
        auto rootRight = root->right;
        free(root);
        return rootRight;
    }
}

void BStree::Displaytree(struct BSnode *root)
{
    cout << "0>" << root->data << endl;
    vector<bool> Disp;

    if (root->right != NULL)
    {
        Disp.push_back(true);
        Displaytree2(root->right, 0, Disp);
        Disp.pop_back();
    }
    if (root->left != NULL)
    {
        Disp.push_back(false);
        Displaytree2(root->left, 0, Disp);
        Disp.pop_back();
    }
    return;
}

void BStree::Displaytree2(struct BSnode *root, int height, vector<bool> DispLine)
{

    for (size_t i = 0; i < (height); i++)
    {
        if (DispLine[i] == true)
        {
            cout << "|";
        }
        else
        {
            cout << " ";
        }
    }

    cout << "L0>" << root->data << endl;

    if (root->right != NULL)
    {
        DispLine.push_back(true);
        Displaytree2(root->right, height + 1, DispLine);
        DispLine.pop_back();
    }
    if (root->left != NULL)
    {
        DispLine.push_back(false);
        Displaytree2(root->left, height + 1, DispLine);
        DispLine.pop_back();
    }
    return;
}

void BStree::set_Root(struct BSnode *root)
{
    this->root = root;
}

struct BSnode *BStree::get_Root()
{
    return root;
}

BStree::~BStree()
{
    Delete_Tree(root);
}
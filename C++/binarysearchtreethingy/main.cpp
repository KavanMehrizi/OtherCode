#include <iostream>
using namespace std;

struct BSTNode /// BinarySearchTreeNode
{ 
    
    int value;
    BSTNode* left = nullptr;
    BSTNode* right = nullptr;
};

class BST // BinarySearchTree
{ 
private:
    BSTNode* root;
public:
    BST() { root = nullptr; }
    ~BST() { clear(root); }
    // moved function implementations out of the class implementation
    void insert(int value);
    void insert(BSTNode* p, int value);
    void remove(int value);
    void remove(BSTNode* p, int value);
    void remove(BSTNode* p, BSTNode* prev);
    BSTNode* findMin() const;
    /// ------------------------------------------
    BSTNode* findMax() const;
    /// ------------------------------------------
    void preOrderTraversal() const;
    void preOrderTraversal(BSTNode* node) const;
    /// ------------------------------------------
    void inOrderTraversal() const;
    void inOrderTraversal(BSTNode* node) const;
    /// ------------------------------------------
    void postOrderTraversal() const;
    void postOrderTraversal(BSTNode* node) const;
    void clear(BSTNode* T);
};

// this helper function is needed to implement recursion
void BST::insert(int value) 
{
    insert(root, value);
}
// this helper function uses recursion to insert new value
void BST::insert(BSTNode* p, int value) 
{
    // if root doesn't exist, puts p there
    if (p == nullptr) 
    {
        p = new BSTNode;
        p->value = value;
        root = p;
    }
    else 
    {
        // if value is smaller than p, calls insert using left tree
        if (value < p->value) 
        {
            if (p->left == nullptr) 
            {
                BSTNode* t = new BSTNode;
                t->value = value;
                p->left = t;
            }
            else 
            {
                insert(p->left, value);
            }
        }
        else if (value > p->value) 
        {
            // if value is bigger than p, calls insert using right tree
            if (p->right == nullptr) 
            {
                BSTNode* t = new BSTNode;
                t->value = value;
                p->right = t;
            }
            else 
            {
                insert(p->right, value);
            }
        }
    }
}
// this function is used to check to see if value needed to be removed is root
void BST::remove(int value) 
{
    if (root->value == value) 
    {
        // if value to be removed is root, removes it
        remove(root, root);
    }
    else 
    {
        // else redirect root to correct position
        remove(root, value);
    }
}
// this helper function is used to check to see wheither right or left tree needs to be removed
void BST::remove(BSTNode* p, int value) 
{
    // if value is smaller, call remove with left tree
    if (value < p->value) 
    {
        if (p->left->value == value) 
        {
            remove(p->left, p);
        }
        else 
        {
            remove(p->left, value);
        }
    }
    else 
    {
        // if value is bigger, call remove with right tree
        if (p->right->value == value) 
        {
            remove(p->right, p);
        }
        else 
        {
            remove(p->right, value);
        }
    }
}
// this helper function is used to remove children of part of the tree
void BST::remove(BSTNode* p, BSTNode* prev) {
    // if removing node has no children, remove node
    if (p->left == nullptr && p->right == nullptr) 
    {
        if (p == root) 
        {
            root = nullptr;
        }
        else if (p == prev->left) 
        {
            prev->left = nullptr;
        }
        else 
            prev->right = nullptr;
    }
    // else if removing node has 1 child, figures out which offspring is null and removes
    else if (p->left == nullptr && p->right != nullptr) 
    {
        if (p == root) 
        {
            root = p->right;
        }
        else if (p == prev->left) 
        {
            prev->left = p->right;
        }
        else 
        {
            prev->right = p->right;
        }
    }
    else if (p->left != nullptr && p->right == nullptr) 
    {
        if (p == root) 
        {
            root = p->left;
        }
        else if (p == prev->left) 
        {
            prev->left = p->left;
        }
        else 
        {
            prev->right = p->left;
        }
    }
    // else removing node has two children
    else 
    {
        BSTNode* t = new BSTNode();
        BSTNode* pt = new BSTNode();
        pt = p;
        t = p->right;

        while (t->left != nullptr) 
        {
            pt = t;
            t = t->left;
        }

        if (t->right == nullptr) 
        {
            pt->left = nullptr;
        }
        else {
            pt->left = t->right;
        }

        if (p == root) {
            root = t;
        }
        else if (p == prev->left) 
        {
            prev->left = t;
        }
        else {
            prev->right = t;
            t->left = p->left;
            t->right = p->right;
        }
    }
    delete p;
}
/// This function finds node containing smallest value
BSTNode* BST::findMin() const 
{
    BSTNode* cur = root;
    while (cur->left != nullptr) 
    {
        cur = cur->left;
    }
    return(cur);
}
// This function finds node containing largest value
BSTNode* BST::findMax() const 
{
    BSTNode* cur = root;
    while (cur->right != nullptr) 
    {
        cur = cur->right;
    }
    return(cur);
}
// This function displays values in pre-order
void BST::preOrderTraversal() const 
{
    cout << "preOrderTraversal: ";
    preOrderTraversal(root);
    cout << endl;
}
void BST::preOrderTraversal(BSTNode* node) const 
{
    if (node != nullptr) {
        cout << node->value << " ";
        preOrderTraversal(node->left);
        preOrderTraversal(node->right);
    }
}
// This function displays values in in-order
void BST::inOrderTraversal() const 
{
    cout << "inOrderTraversal: ";
    inOrderTraversal(root);
    cout << endl;
}
void BST::inOrderTraversal(BSTNode* node) const 
{
    if (node != nullptr) {
        inOrderTraversal(node->left);
        cout << node->value << " ";
        inOrderTraversal(node->right);
    }
}
// This function displays values in post-order
void BST::postOrderTraversal() const {
    cout << "postOrderTraversal: ";
    postOrderTraversal(root);
    cout << endl;
}
void BST::postOrderTraversal(BSTNode* node) const {
    if (node != nullptr) {
        postOrderTraversal(node->left);
        postOrderTraversal(node->right);
        cout << node->value << " ";
    }
}

// this function clears subtrees and the node
void BST::clear(BSTNode* T)
{
    // t is nothing, nothing to clear
    if (T == NULL)
    {
        return;
    }
    // clears left subtree if not empty
    if (T->left != NULL)
    {
        clear(T->left);
    }
    // clears right subtree if not empty
    if (T->right != NULL)
    {
        clear(T->right);
    }
    // deletes node T
    delete T;
    return;
}

const int SIZE = 15;

int main() 
{
    BST bst;
    int values[SIZE] = {5, 2, 12, -4, 3, 9, 21, -7, 19, 25, -8, -6, -4, 3, 12};
    for (int i = 0; i < SIZE; i++)
        bst.insert(values[i]);

    bst.preOrderTraversal(); /// should be 5 2 -4 -7 -8 -6 3 12 9 21 19 25
    bst.inOrderTraversal(); /// should be -8 -7 -6 -4 2 3 5 9 12 19 21 25
    bst.postOrderTraversal(); /// should be -8 -6 7 -4 3 2 9 19 25 21 12 5

    bst.remove(3); /// Node 3 has 0 children --> delete the node and make it NULL;
    bst.remove(-4); /// Node -4 has 1 children --> Link parent to child --> delete the node and make it NULL;
    bst.remove(12); /// Node 12 has 2 children --> findMin for the right subtree --> swap value -> delete

    bst.preOrderTraversal(); /// should be 5 2 -7 -8 -6 19 9 21 25
    bst.inOrderTraversal(); /// should be -8 -7 -6 2 5 9 19 21 25
    bst.postOrderTraversal(); /// should be -8 -6 7 2 9 25 21 19 5

    return 0;
}
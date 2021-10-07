/*
 * BinarySearchTree.cpp
 * COMP15
 * Fall 2019
 * Edited by: Matt Champlin
 *
 * Implementation of the Binary Search Tree class.
 * Behaves like a standard BST except that it handles multiplicity
 * If you insert a number twice  and then remove it once, then it will
 * still be in the data structure
 */

#include "BinarySearchTree.h"
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#include <time.h>
#include <limits>
#include <chrono>

using namespace std;
using namespace chrono;

// Function:   BinarySearchTree()
// Parameters: None
// Returns:    Nothing
// Does:       Default Constructor for Binary Search Tree Class
BinarySearchTree::BinarySearchTree() {
        root = NULL;
}

// Function:   ~BinarySearchTree()
// Parameters: None
// Returns:    Nothing
// Does:       Default Destructor
BinarySearchTree::~BinarySearchTree() {
        // walk tree in post-order traversal and delete
        post_order_delete(root);
        root = nullptr;  // not really necessary, since the tree is going
                         // away, but might want to guard against someone
                         // using a pointer after deleting
}

// Function:   post_order_delete
// Parameters: Node *node - pointer to a node
// Returns:    nothing
// Does:       deletes a BST
void BinarySearchTree::post_order_delete(Node *node) {
    if (node == NULL) {
        return;
    }
    else {
        post_order_delete(node->left);
        post_order_delete(node->right);
        delete node;
    }
    root = NULL;
    return;
}

// Function:   BinarySeachTree()
// Parameters: BinarySearchTree &source - An initialized BST object
// Returns:    nothing
// Does:       copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source) {
        root = pre_order_copy(source.root);
        set_parents(root);
}

// Function:   set_parents
// Parameters: Node *root - pointer to the root node
// Returns:    nothing
// Does:       sets new trees parent nodes
void BinarySearchTree::set_parents(Node *root)
{
    if (root == NULL) {
        return;
    }
    set_parents(root->left);
    set_parents(root->right);
    if (root->left != NULL) {
        root->left->parent = root;
    }
    if (root->right != NULL) {
        root->right->parent = root;    
    }
    

}

// Function:   Binary Search Tree assignment overload
// Parameters: A initialized BST object
// Returns:    a copied BST object
// Does:       assignment overload
BinarySearchTree &BinarySearchTree::operator=(const BinarySearchTree &source) {

       if (this != &source) {
        post_order_delete(root);
        root = pre_order_copy(source.root);
        set_parents(root);
    }
    return *this;
}

// Function:   pre_order_copy
// Parameters: Node *node
// Returns:    A Node pointer
// Does:       copies a tree and returns the root node
BinarySearchTree::Node *BinarySearchTree::pre_order_copy(Node *node) const {
        if (node == NULL) {
            return NULL;
        }
        Node *tree   = copy_node(node->data, node->count);
        tree->parent = NULL;
        tree->left   = pre_order_copy(node->left);
        tree->right  = pre_order_copy(node->right);
        return tree;
}

// Function:   copy_node
// Parameters: int data  - data from node to copied
//             int count - count from node to be copied
// Returns:    a newly initialized BinarySearchTree node pointer
// Does:       see above
BinarySearchTree::Node *BinarySearchTree::copy_node(int data, int count) const
{
    Node *n   = new Node;
    n->data   = data;
    n->count  = count;
    n->left   = NULL;
    n->right  = NULL;
    n->parent = NULL;
    return n;
}

// Function:   isEmpty
// Parameters: none
// Returns:    True if tree is empty, false if not
// Does:       see above
bool BinarySearchTree::isEmpty()
{
    if (root == NULL) {
        return true;
    }
    return false;
}

// Function:   getRoot
// Parameters: none
// Returns:    A pointer to the root node
// Does:       see above
BinarySearchTree::Node *BinarySearchTree::getRoot() {
    return root;
}

// Function:   getRootVal
// Parameters: None
// Returns:    An int with the value at the root node
// Does:       see above
int BinarySearchTree::getRootVal()
{
    if (root == NULL) {
        return 0;
    }
    return root->data;
}

// Function:   find_min
// Parameters: none
// Returns:    an int with the min value in the tree
// Does:       public function where user can get the min value in BST
int BinarySearchTree::find_min() const {
    if (root == nullptr) {
            return numeric_limits<int>::min(); // INT_MAX
        }


    return find_min(root)->data;
}

// Function:   find_min
// Parameters: Node *node - pointer to the root
// Returns:    the root node pointer
// Does:       
BinarySearchTree::Node *BinarySearchTree::find_min(Node *node) const {
    
    if (node == NULL) {
        return NULL;
    }
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Function:   find_max (public)
// Parameters: none
// Returns:    int with max value held in tree
// Does:       Public function where user can find max of BST
int BinarySearchTree::find_max() const {
    if (root == nullptr) {
        return numeric_limits<int>::max(); // INT_MAX
    }
    return find_max(root)->data;
}

// Function:   find_max (private)
// Parameters: Node *node - a pointer to the root node
// Returns:    The node  with the max value in the tree
// Does:       see above
BinarySearchTree::Node *BinarySearchTree::find_max(Node *node) const {
    if (node == NULL) {
        return NULL;
    }
    while (node->right != NULL) {
        node = node->right;
    }
    return node;
}

// Function:   contains
// Parameters: int value - the value you want to find
// Returns:    True is the value is in the BST False if not
// Does:       see above
bool BinarySearchTree::contains(int value) const {
    return (contains(root, value));
}

// Function:   contains 
// Parameters: Node *node - the root node
//             int value  - the value you want to find
// Returns:    True if the value is in the BST False if not
// Does:       see above
bool BinarySearchTree::contains(Node *node, int value) const {
        if (node == NULL) {
            return false;
        }
        if (value == node->data) {
            return true;
        }
        if (value > node->data) {
            return (contains(node->right, value)); 
        }
        else {
            return (contains(node->left, value));
        } 
        return false;
}
 
// Function:   insert (public)
// Parameters: int value - the value you want to insert
// Returns:    nothing
// Does:       inserts a value into BST
void BinarySearchTree::insert(int value) {
        insert(root, nullptr, value);
}

// Function:   insert (private)
// Parameters: Node *node   - the root node
//             Node *parent - nullpointer
//             int   value  - the value to be inserted
// Returns:    nothign
// Does:       inserts a value into BST
void BinarySearchTree::insert(Node *node, Node *parent, int value) {

    if (node == NULL) {
        root = createNode(value);
        return;
    }
    if (value == node->data){
        node->count++;
        return;
    }
    if (value > node->data) {
        if (node->right == NULL){
            node->right = createNode(value);
            node->right->parent = node;
        }
        else {
            parent = node;
            insert(node->right, parent, value);
        }
    }
    if (value < node->data){
        if (node->left == NULL){
            node->left = createNode(value);
            node->left->parent = node;
        }
        else {
            parent = node;
            insert(node->left, parent, value);
        }     
    }
}

// Function:   remove (public)
// Parameters: int value - the value to be removed
// Returns:    true if value is removed, false if not
// Does:       removes a value
bool BinarySearchTree::remove(int value) {

        return remove(root, value);
}

// Function:   remove (private)
// Parameters: Node *node - root node\
//             int value  - value to be removed
// Returns:    true if value is removed, false if not
// Does:       removes a value
bool BinarySearchTree::remove(Node *node, int value) {
    if (node == NULL) {
        return false;
    }
    Node *found  = NULL;
    if (! find(node, found, value)) {
        cout << "Value Does Not Exist In BST!" << endl;
        return false;
    }
    if (found->data == value) {
        found->count--;
    }
    if (found->count <= 0) {
        if (root->left == NULL and root->right == NULL) {
            delete root;
            root = NULL;
            return true;
        }
        if (found->left == NULL and found->right == NULL) {
            if (found->parent->right == found) {
                found->parent->right = NULL;
            }
            if (found->parent->left == found) {
                found->parent->left = NULL;
            }
            delete found;
            return true;
        } else if (found->left == NULL or found->right == NULL) {
            if (found->left == NULL) {
                rem_help_min(found);
            } else {
                rem_help_max(found);
            }
        } else {
            if (found->parent == NULL) { 
                rem_help_min(found);
            }
            else if (found->parent->left == found) {
                rem_help_min(found);
            }
            else if (found->parent->right == found) {
                rem_help_min(found);
            }
        }   
    }
    return true;
}

// Function:   rem_help-min
// Parameters: Node *found - the node of the found value
// Returns:    nothing
// Does:       finds the min value of the right node of the found node
void BinarySearchTree::rem_help_min(Node *found) 
{
    Node *min = find_min(found->right);
    found->data  = min->data;
    found->count = min->count;
    min->count   = 0;
    remove(min, min->data);
}
    

// Function:   rem_help_max
// Parameters: Node *found - the node of the found value
// Returns:    nothing
// Does:      finds the max value of the left node of the found node
void BinarySearchTree::rem_help_max(Node *found) 
{
    Node * max = find_max(found->left);
    found->data = max->data;
    found->count = max->count;
    max->count = 0;
    remove(max, max->data);
}

// Function:   find (public)
// Parameters: int value - the value to find
// Returns:    true if value is in BST false if not
// Does:       finds a value
bool BinarySearchTree::find(int value)
{
    Node *n = NULL;
    if (find(root, n, value)){
        return true;
    }
    return false;
}

// Function:   find (private)
// Parameters: Node *root - pointer to root
//             Node *&found - pointer to address of found
//             int val - value to be found
// Returns:    true if value is found and returns the pointer to the node
//             of the found value
// Does:       see above
bool BinarySearchTree::find(Node *root, Node *&found, int val) 
{
    if (root == NULL) {
        return false;
    }
    if (val == root->data) {
        found = root;
        return true;
    }
    if (val > root->data) {
        return (find(root->right, found, val)); 
    }
    else {
        return (find(root->left, found, val));
    } 
    return false;
}

// Function:   tree_height (public)
// Parameters: none
// Returns:    int value of height of tree
// Does:      returns the height of tree
int BinarySearchTree::tree_height() const {
        return tree_height(root) - 1;
}

// Function:   tree_height (private)
// Parameters: Node *node - root node
// Returns:    int value of height of tree
// Does:       returns the height of tree
int BinarySearchTree::tree_height(Node *node) const {
        if (node == NULL) {
            return 0;
        }
        int height_left  = 1 + tree_height(node->left);
        int height_right = 1 + tree_height(node->right);

        if (height_left > height_right) {
            return height_left;
        } else {
            return height_right;
        }
}

// Function:   node_count (public)
// Parameters: none
// Returns:    number of nodes in BST
// Does:       returns the total number of nodes
int BinarySearchTree::node_count() const {
        return node_count(root);
}

// Function:   node_count (private)
// Parameters: none
// Returns:    number of nodes in BST
// Does:       returns the total number of nodes
int BinarySearchTree::node_count(Node *node) const {
        if (node == NULL) {
            return 0;
        }
        return 1 + node_count(node->left) + node_count(node->right);
}

// Function:   count_total
// Parameters: none
// Returns:    sum of all the node values (including duplicates)
// Does:       return the sum of all the node values (including duplicates)
int BinarySearchTree::count_total() const {
        return count_total(root);
}

// Function:   count_total
// Parameters: Node *node - root node
// Returns:    sum of all the node values (including duplicates)
// Does:       return the sum of all the node values (including duplicates)  
int BinarySearchTree::count_total(Node *node) const {
        if (node == NULL) {
        return 0;
    }
    int node_value = node->data * node->count;
    return node_value + count_total(node->left) + count_total(node->right);
}

// // Function:   I don't use this one
// // Parameters: 
// // Returns:    
// // Does:      
// BinarySearchTree::Node *BinarySearchTree::find_parent(Node *node,
//                                                       Node *child) const {
//         if (node == nullptr)
//                 return nullptr;

//         // if either the left or right is equal to the child,
//         // we have found the parent
//         if (node->left == child or node->right == child) {
//                 return node;
//         }

//         // Use the binary search tree invariant to walk the tree
//         if (child->data > node->data) {
//                 return find_parent(node->right, child);
//         } else {
//                 return find_parent(node->left, child);
//         }
// }

// Function:   print_tree
// Parameters: none
// Returns:    nothing
// Does:      use the printPretty helper to make the tree look nice
void BinarySearchTree::print_tree() const {

        size_t      numLayers  = tree_height() + 1;
        size_t      levelWidth = 4;
        const char *rootPrefix = "-> ";

        // Need numLayers * levelWidth character for each layer of tree.
        // Add an extra levelWidth characters at front to avoid if statement
        // 1 extra char for nul character at end
        char *start = new char[(numLayers + 1) * levelWidth + 1];

        print_tree(root, start + levelWidth, start + levelWidth, rootPrefix);
        delete[] start;

}

   
// Logic and Output Reference: 
// https://www.techiedelight.com/c-program-print-binary-tree/
void BinarySearchTree::print_tree(Node *node, char *const currPos,
                                  const char *const fullLine,
                                  const char *const branch) const {

        if (node == nullptr)
                return;

        // 4 characters + 1 for nul terminator
        using TreeLevel                    = char[5];
        static const int       levelLength = sizeof(TreeLevel) - 1;
        static const TreeLevel UP = ".-- ", DOWN = "`-- ", EMPTY = "    ",
                               CONNECT = "   |";
        // Copies prev into dest and advances dest by strlen(prev)
        auto set = [](char *dest, const char *prev) {
                size_t p = strlen(prev);
                return (char *)memcpy(dest, prev, p) + p;
        };

        print_tree(node->right, set(currPos, EMPTY), fullLine, UP);

        // Clear any characters that would immediate precede the "branch"
        // Don't need to check for root (i.e start of array),fullLine is padded
        set(currPos - levelLength, EMPTY);

        // Terminate fullLine at current level
        *currPos = '\0';

        std::cout << fullLine << branch << node->data
                  << (node->count > 1 ? "*" : "") << endl;

        // Connect upper branch to parent
        if (branch == UP)
                set(currPos - levelLength, CONNECT);

        // Connect lower branch to parent
        print_tree(node->left, set(currPos, CONNECT), fullLine, DOWN);
}

// Function:   createNode
// Parameters: int val - the value to insert into the tree
// Returns:    a new Node with the value of the int
// Does:       creates a new BST node
BinarySearchTree::Node *BinarySearchTree::createNode(int val) const  
{
    Node *n   = new Node;
    n->data   = val;
    n->count  = 1;
    n->left   = NULL;
    n->right  = NULL;
    n->parent = NULL;
    return n;
}

// Function:   inOrder (public)
// Parameters: none
// Returns:    nothing
// Does:       calls private inOrder
void BinarySearchTree::inOrder() {
    inOrder(root);
}

// Function:   inOrder (private)
// Parameters: Node *root - the root pointer
// Returns:    nothing
// Does:       prints in order traversal of BST
void BinarySearchTree::inOrder(Node *root) 
{
    if (root == NULL)
    {
        return;
    }
    else {
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }
}

// Function:   inOrderReverse (public)
// Parameters: none
// Returns:    nothing
// Does:       calls private function
void BinarySearchTree::inOrderReverse() {
    inOrderReverse(root);
}

// Function:   inOrderReverse (private)
// Parameters: Node *root - pointer to root node
// Returns:    nothing
// Does:       prints in order reverse      
void BinarySearchTree::inOrderReverse(Node *root) {
    if (root == NULL){
        return;
    }
    else {
        inOrderReverse(root->right);
        cout << root->data << " ";
        inOrderReverse(root->left);       
    }
}

// Function:   postOrder (public)
// Parameters: none
// Returns:    nothing
// Does:       calls private funtion
void BinarySearchTree::postOrder()
{
    postOrder(root);
}

// Function:   postOrder (private)
// Parameters: Node * root - pointer to root node
// Returns:    nothing
// Does:       prints post order traversal of BST     
void BinarySearchTree::postOrder(Node *root) 
{
    if (root == NULL)
    {
        return;
    }
    else 
    {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->data << " ";
    }
}

// Function:   preOrder (public)
// Parameters: none
// Returns:    nothing
// Does:       calls private function
void BinarySearchTree::preOrder() {
    preOrder(root);
} 

// Function:   preOrder (private)
// Parameters: Node *root - pointer to root node
// Returns:    nothing
// Does:       prints pre order traversal of BST
void BinarySearchTree::preOrder(Node *root) 
{
    if (root == NULL) {
        return;
    }
    else {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Function:   levelOrder (public)
// Parameters: none
// Returns:    nothing
// Does:       calls private function      
void BinarySearchTree::levelOrder() 
{
    levelOrder(root);
}

// Function:   levelOrder (private)
// Parameters: Node *root - pointer to root node
// Returns:    nothing
// Does:       prints level order traversal of BST  
void BinarySearchTree::levelOrder(Node *root) 
{
    if (root == NULL)
    {
        return;
    }
    queue <Node *> q;

    q.push(root);

    while (! q.empty()) {
        Node *n = q.front();
        cout << n->data << " ";
        q.pop();
        if (n->left != NULL)
        {
            q.push(n->left);
        }
        if (n->right != NULL) 
        {
            q.push(n->right);
        }
    }
}

// Function:   findPath (public)
// Parameters: int target - value you want to find th path to
// Returns:    string of path
// Does:       finds path to target
string BinarySearchTree::findPath(int target)
{
    return findPath(root, target);
}

// Function:   findPath (private)
// Parameters: int target - value you want to find th path to
// Returns:    string of path
// Does:       finds path to target    
string BinarySearchTree::findPath(Node *root, int target)
{
    string found = "Target Found!";
    if (root == NULL) {
        return "";
    }
    else if (root->data == target) {
        return found;
    }
    string L = findPath(root->left, target);
    string R = findPath(root->right, target);

    if (L != "") {
        return "L " + L;
    }
    else if (R != "") {
        return "R " + R;
    }
    return "";
}

// Function:   findEven (public)
// Parameters: none
// Returns:    int of how many even values are in BST
// Does:       finds number of even values in BST
int BinarySearchTree::findEven() 
{
    return findEven(root);
}

// Function:   findEven (private)
// Parameters: pointer to the root
// Returns:    int of how many even values are in BST
// Does:       finds number of even values in BST    
int BinarySearchTree::findEven(Node *root) 
{
    int x = 0;
    if (root == NULL) {
        return x;
    }
    if (root->data % 2 == 0) {
        x = 1;
    }
    return x + findEven(root->left) + findEven(root->right);

}

// Function:   findOdd (public)
// Parameters: none
// Returns:    int of how many Odd values are in BST
// Does:       finds number of Odd values in BST
int BinarySearchTree::findOdd()
{
    return findOdd(root);
}

// Function:   findOdd (private)
// Parameters: pointer to the root
// Returns:    int of how many Odd values are in BST
// Does:       finds number of Odd values in BST     
int BinarySearchTree::findOdd(Node *root) 
{
    int x = 0;
    if (root == NULL) {
        return x;
    }
    if (root->data < 0) {
        int pos_flip = root->data * -1;
        if (pos_flip % 2 == 1) {
            x = 1;
        }
    }
    else {
        if (root->data % 2 == 1) {
            x = 1;
        }
    }
    return x + findOdd(root->left) + findOdd(root->right);
}

// Function:   removeAll (public)
// Parameters: none
// Returns:    nothing
// Does:       deletes all values of BST
void BinarySearchTree::removeAll() {
    post_order_delete(root);
}

// Function:   makenew
// Parameters: int numElem - number of new elements to be addded
//             int rangelow - low range of new elements
//             int rangehigh - high range of new elements
// Returns:    a new BST with the number of values requested
// Does:       makes a new BST
BinarySearchTree BinarySearchTree::makeNew(int numElem, int rangelow, 
                                           int rangehigh)
{
    BinarySearchTree temp;
    srand(time(NULL));
    if (rangelow == 0) {
        for (int i = 0; i < numElem; ++i) {
            temp.insert(rand() % (rangehigh + 1));
        }
    }
    else if (rangelow > 0) {
        rangehigh = rangehigh - rangelow;
        for (int i = 0; i < numElem; ++i) {
            temp.insert(rand() % (rangehigh + 1) + rangelow);
        }
    }
    else if (rangelow < 0) {
        if (rangehigh + rangelow == 0) {
            for (int i = 0; i < numElem; ++i) {
                temp.insert(rand() % (rangehigh * 2) + rangelow);
            }
        } else {
            rangehigh = rangehigh + (rangelow * -1);
            for (int i = 0; i < numElem; ++i) {
                temp.insert(rand() % (rangehigh + 1) + rangelow);
            }
        }
    }
    return  temp;
}

// Function:   insMany
// Parameters: int numElem - number of new elements to be addded
//             int rangelow - low range of new elements
//             int rangehigh - high range of new elements
// Returns:    nothing
// Does:       inserts many values into BST
void BinarySearchTree::insMany(int numElem, int rangelow, int rangehigh) 
{
    if (rangelow == 0) {
        for (int i = 0; i < numElem; ++i) {
            insert(rand() % (rangehigh + 1));
        }
    }
    else if (rangelow > 0) {
        rangehigh = rangehigh - rangelow;
        for (int i = 0; i < numElem; ++i) {
            insert(rand() % (rangehigh + 1) + rangelow);
        }
    }
    else if (rangelow < 0) {
        if (rangehigh + rangelow == 0) {
            for (int i = 0; i < numElem; ++i) {
                insert(rand() % (rangehigh * 2) + rangelow);
            }
        } else {
            rangehigh = rangehigh + (rangelow * -1);
            for (int i = 0; i < numElem; ++i) {
                insert(rand() % (rangehigh + 1) + rangelow);
            }
        }
    }
}

// Function:   bushify_tree (public)
// Parameters: none
// Returns:    nothing
// Does:       calls private function
void BinarySearchTree::bushify_tree() 
{
    bushify_tree(root);
}

// Function:   bushify_tree (private)
// Parameters: Node *root - pointer to root node
// Returns:    nothing
// Does:       Makes tree bushy
void BinarySearchTree::bushify_tree(Node *root) 
{
    if (root == NULL) {
        cout << "An empty tree cannot be more bushy!!  Please insert at\n"
                "least 3 values!" << endl;
        return;
    }
    if (node_count() < 3) {
        cout << "A tree with < 3 nodes cannot be more bushy!  Please insert\n"
                "at least 3 values!" << endl;
        return;
    }
    int tempsize = node_count();
    // cout << "tempsize is: " << tempsize << endl;
    vector <NodeCopy> tempvec; // create vector of NodeCopy structs to store
                               // a copy of the BST Data
    tempvec.reserve(tempsize);

    int index = 0;             // create int and int pointer to act as an  
    int *intptr = &index;      // index for insertion to the new vector

    // Use our helper function inOrderCopy to insert into our vector all the
    // information stored in the tree
    inOrderCopy(root, tempvec, intptr);

    // delete the old tree so we can use the vector to reinsert the values
    // in a more bushy manner!
    post_order_delete(root);

    int start  = 0;
    // int end    = tempvec.size(); // gets the number of nodes to be copied
    int end    = tempsize;
    int size   = end;

    // run the recursive helper that makes your new bushy tree!!
    bushify_helper(tempvec, start, end, size);
}

// Function:   bushify_helper
// Parameters: vector<NodeCopy> tempvec - temp vector of values of BST
//             int start - index of start of vector
//             int end   - index of end of vector
//             int size  - size of vector
// Returns:    nothing
// Does:       actually does the recurive bushifying of tree
void BinarySearchTree::bushify_helper(vector<NodeCopy> &tempvec, int start,
                                       int end, int size)
{
    if (start > end) { // Base case
        return;
    }

    int mid = (start + end) / 2;

    // ensures we don't index past the last element in the array.
    if (mid >= size) {
        return;
    }

    for (int i = 0; i < tempvec[mid].freq; i++) {
        insert(tempvec[mid].val);
    }

    bushify_helper(tempvec, start, mid - 1, size);

    bushify_helper(tempvec, mid + 1, end, size);
}

// Function:   inOrderCopy
// Parameters: Node *root - root pointer
//             vector<NodeCopy> &tempvec - copy of the old BST
//             int *&intptr - index of vector to be added
// Returns:    nothing
// Does:       Makes a sorted list in a vector of copies of the nodes 
//             by in order traversing the BST and copying the data held
void BinarySearchTree::inOrderCopy(Node *root, vector<NodeCopy> &tempvec, 
                                   int *&intptr) 
{
    if (root == NULL)
    {
        return;
    }
    else {
        inOrderCopy(root->left, tempvec, intptr);
        NodeCopy n;
        tempvec.push_back(n);
        tempvec[*intptr].val  = root->data;
        tempvec[*intptr].freq = root->count;
        *intptr = *intptr + 1;
        inOrderCopy(root->right, tempvec, intptr);
    }
}

// Function:   rocketman (public)
// Parameters: none
// Returns:    nothing
// Does:       calls private function
void BinarySearchTree::rocketMan()
{
    rocketMan(root);
}

// Function:   rocketMan (private)
// Parameters: Node *root - root pointer
// Returns:    nothing
// Does:       silly function that makes a cool but useless pattern in the BST
void BinarySearchTree::rocketMan(Node *root)
{
    if (root == NULL) {
        cout << "An empty tree cannot be more bushy!!  Please insert at\n"
                "least 3 values!" << endl;
        return;
    }
    if (node_count() < 3) {
        cout << "A tree with < 3 nodes cannot be more bushy!  Please insert\n"
                "at least 3 values!" << endl;
        return;
    }

    vector <NodeCopy> tempvec; // create vector of NodeCopy structs to store
                               // a copy of the BST Data

    int index = 0;             // create int and int pointer to act as an  
    int *intptr = &index;      // index for insertion to th enew vector

    // Use our helper function inOrderCopy to insert into our vector all the
    // information stored in the tree
    inOrderCopy(root, tempvec, intptr);

    // delete the old tree so we can use the vector to reinsert the values
    // in a more bushy manner!
    post_order_delete(root);

    int size      = tempvec.size();
    int rocketTip = size / 2; // gets the index of the tip of the rocket

    // Add our new root to the tree and make sure to add any duplicates if our
    // root had more than one of itself stored in the node!
    for (int i = 0; i < tempvec[rocketTip].freq; i++){
        insert(tempvec[rocketTip].val);
    }
    // loop through top half of the vector and bouncily insert the upper half
    // values.  We increment i by 2 to make sure our new tree isn't just 
    // linear on each side!
    for (int i = rocketTip + 2; i <= size; i = i + 2) {
        if (i == size) {
            for (int j = 0; j < tempvec[i - 1].freq; j++) {
                insert(tempvec[i - 1].val);
            }
        } else {
            for (int j = 0; j < tempvec[i].freq; j++) {
                insert(tempvec[i].val);
            }
            for (int k = 0; k < tempvec[i - 1].freq; k++) {
                insert(tempvec[i - 1].val);
            }
        }
    }

    // loop through bottom half of the vector and bouncily insert lower half
    // values.  We decrement by 2 to make sure that our new tree isn't just
    // linear on each side!
    for (int i = rocketTip - 2; i >= -1; i = i - 2) {
        if (i < 0) {
            for (int j = 0; j < tempvec[i + 1].freq; j++) {
                insert(tempvec[i + 1].val);
            }
        } else {
            for (int j = 0; j < tempvec[i].freq; j++) {
                insert(tempvec[i].val);
            }
            for (int k = 0; k < tempvec[i + 1].freq; k++) {
                insert(tempvec[i + 1].val);
            }
        }
    } 
}

// Function:   howMany (public)
// Parameters: int target - target
// Returns:    nothing
// Does:       calls private funciton
void BinarySearchTree::howMany(int target) 
{
    howMany(root, target);
}

// Function:   howMany (private)
// Parameters: node *root - the freakin root node
//             int target - the freakin number you want to know how many of kid
// Returns:    nothing
// Does:       lots of stuff including telling you how many of a number is in 
//             the figgin BST.  1000 lines later im finally done... 
void BinarySearchTree::howMany(Node *root, int target) 
{
    if (root == NULL) {
        cout << "Empty Tree!!" << endl;
        return;
    }
    Node *found;
    if ( ! find(root, found, target)) {
        cout << "Target is not in BST!!" << endl;
    } else {
        cout << "There are " << found->count << " " << target <<
                "s in the BST." << endl;
    }
}

high_resolution_clock::time_point BinarySearchTree::getStart()
{
    high_resolution_clock::time_point start = high_resolution_clock::now();
    return start;
}

   
void BinarySearchTree::printRuntime(high_resolution_clock::time_point start) const
{
    high_resolution_clock::time_point end = high_resolution_clock::now();
    milliseconds elapsed = duration_cast<milliseconds>(end - start);
    nanoseconds  nan     = duration_cast<nanoseconds>(end - start);
    microseconds mic     = duration_cast<microseconds>(end - start);
    
    double mili    = elapsed.count();
    double seconds = mili / 1000;
    double micro   = mic.count();
    double nano    = nan.count();

    cout << "\nTime Elapsed: " << nano << " nanoseconds" << endl;

    cout << "Time Elapsed: " << micro << " microseconds" << endl;

    cout << "Time Elapsed: " << mili << " milliseconds" << endl;
    
    cout << "Time Elapsed: " << seconds << " seconds" << endl;
}






/*
 * BinarySearchTree.h
 * COMP15
 * Spring 2019
 *
 * Interface of the Binary Search Tree class.
 * Behaves like a standard BST except that it handles multiplicity
 * If you insert twice a number and then remove it once, then it will
 * still be in the data structure
 */

#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include <string>
#include <vector>
#include <utility>
#include <chrono>

using namespace std::chrono;

class BinarySearchTree {
public:
        // constructor
        BinarySearchTree();

        // destructor
        ~BinarySearchTree();

        // copy constructor
        BinarySearchTree(const BinarySearchTree &source);

        // assignment overload
        BinarySearchTree &operator=(const BinarySearchTree &source);

        // find_min() returns the minimum value in the tree
        // returns INT_MAX if the tree is empty
        int find_min() const;

        // find_max() returns the maximum value in the tree
        // returns INT_MIN if tree is empty
        int find_max() const;

        // contains() returns true if the value is in the tree,
        // false if it is not in the tree
        bool contains(int value) const;

        // insert() inserts the value into the Binary Search Tree.
        // If the value is already in the tree, the node's count
        // is incremented by 1
        void insert(int value);

        // remove() does a full removal from the tree (NOT lazy removal)
        // If a node's count is greater than one, the count is
        // decremented, and the node is not removed.
        // Nodes with a count of 0 must be fully removed using the
        // following algorithm (discussed in class): if the node has no
        // children, simply remove it.  If the node has one child,
        // "bypass" the node to the child from the parent.  If the node
        // has two children, first find the minimum node of the
        // right child, replace the node's data with the value and
        // count of right's minimum, and then recursively delete
        // right's minimum.
        bool remove(int value);

        // returns the maximum distance from the root to it's farthest
        // leaf.  Note:  An empty tree has a height of -1, a tree with
        // just a root has a height of 0, and a tree with a root and
        // one or two children has a height of 1, etc.
        int tree_height() const;

        // returns the total number of nodes (NOT including duplicates)
        // i.e., if a tree contains 3, 4, 4, the number of nodes would
        // only be two, because the fours are contained in one node.
        int node_count() const;

        // return the sum of all the node values (including duplicates)
        // For the previous example, the count_total() would be
        // 3 + 4 + 4 = 11
        int count_total() const;

        // print the tree (written for you)
        void print_tree() const;

        /* ***************** some stuff I did for fun ******************* */
        /* *********** Mostly for use with BSTInteractively ************* */

        int    getRootVal();
        void   inOrder();
        void   inOrderReverse();
        void   postOrder();
        void   preOrder();
        void   levelOrder();
        bool   find(int value);
        bool   isEmpty();
        int    findEven();
        int    findOdd();
        void   removeAll();
        void   bushify_tree();
        void   rocketMan();
        void   howMany(int target);
        void   insMany(int numElem, int rangelow, int rangehigh);

        std::string findPath(int target);

        BinarySearchTree makeNew(int numElem, int rangelow, int rangehigh);

        void   printRuntime(high_resolution_clock::time_point start) const;
        high_resolution_clock::time_point getStart();
private:
        // Binary Search Tree Node:
        // - data is the value
        // - count is the number of times the data has been inserted
        //   into the tree (minus removals)
        //
        struct Node {
                int   data;
                int   count;
                Node *left;
                Node *right;
                Node *parent;
        };
        // For use only with bushify_tree function!!
        struct NodeCopy{
                int val;
                int freq;
        };

        // I wanted to try and write bushify again with stl pair per Mark
        // sheldons suggestion.
        std::pair <int, int> NodeData;


        // the root of the tree (starts as NULL)
        Node *root;

        // the following nine functions are private helper functions
        // for the public functions. We do not want to expose the
        // internals of the tree publicly, so we pass the root (and
        // other information in some cases) to the functions below
        // from the public functions.
        Node *find_min(Node *node) const;
        Node *find_max(Node *node) const;
        bool  contains(Node *node, int value) const;
        void  insert(Node *node, Node *parent, int value);
        // Students will implement one of the following remove functions
        bool  remove(Node *node, int value);
        bool  remove(Node *node, Node **ptr_to_ptr_to_me, int value);
        int   tree_height(Node *node) const;
        int   node_count(Node *node) const;
        int   count_total(Node *node) const;
        Node *pre_order_copy(Node *node) const;
        // used by the destructor to delete nodes recursively
        void post_order_delete(Node *node);
        
        // find_parent (written for you) is necessary for removing
        // the right_min of a node when removing a node that has
        // two children
        Node *find_parent(Node *node, Node *child) const;

        // Pretty print
        void print_tree(Node *node, char *const currPos,
                        const char *const fullLine,
                        const char *const branch) const;

        // create nodes:
        Node *createNode(int val) const;

        // helper functions and utility functions
        void  rem_help_min(Node *found);
        void  rem_help_max(Node *found);
        bool  find(Node *root, Node *&found, int val);
        Node *copy_node(int data, int count) const;

        // this is a cool one.  For copying trees, since I have a parent 
        // pointer, it is nesseseary to reconstruct the parent relationships
        // after the tree is created, since I can't do it while coping nodes.
        void set_parents(Node *root);


        /* ***************** some stuff I did for fun ******************* */
        /* *********** Mostly for use with BSTInteractively ************* */

        void   inOrder(Node *root);
        void   inOrderReverse(Node *root);
        void   postOrder(Node *root);
        void   preOrder(Node *root);
        void   levelOrder(Node *root);
        void   bushify_tree(Node *root);
        void   bushify_helper(std::vector<NodeCopy> &tempvec, int start,
                                                    int end, int size);
        void   inOrderCopy(Node *root, std::vector<NodeCopy> &tempvec, 
                            int *&index);
        void   rocketMan(Node *root);
        void   howMany(Node *root, int target);
        int    findEven(Node *root);
        int    findOdd(Node *root);
        Node  *getRoot();
        std::string findPath(Node *root, int target);

        

        

};

#endif /* BINARYSEARCHTREE_H_ */













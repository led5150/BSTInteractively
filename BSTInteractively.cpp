/******************************************************************************
* Tufts - Comp 15
* Created By: Matt Champlin
* 10/25/19
* 
* BSTInteractively.cpp
*   This program uses the BinarySearchTree implementation to create a BST of
*   a user given size and range of numbers.  You then can interactively do 
*   things with the BST, like print pretty and add and delete etc.
******************************************************************************/


#include <iostream>
#include <time.h>
#include <chrono>
#include "BinarySearchTree.h"

using namespace std;
using namespace chrono;


// function headers
BinarySearchTree createBST();
void whatYouCanDo();
int  intcheck();
void dostuff(BinarySearchTree *b);
void run();



// tiny little main! yay.
int main() 
{
    srand(time(NULL));
    run();
    return 0;
}





// Function:   run
// Parameters: none
// Returns:    nothing
// Does:       Creates a BinarySearchTree object and runs the driver dostuff()
void run() 
{

    BinarySearchTree bst = createBST();
    BinarySearchTree *b  = &bst;

    whatYouCanDo();
    dostuff(b);
}


// Function:   createBST
// Parameters: none
// Returns:    A initialized BinarySearchTree object
// Does:       Works to initialize the initial BST to be used for the program
//             prompts user with what you need to enter to make a BST and

BinarySearchTree createBST() 
{
    BinarySearchTree b;
    int num_elements;
    int range_low;
    int range_high;
    cout << "Welcome to BST Maker!!  This will make you a noiiiccee BST\n"
            "First, how many things do you want in the tree?  They are ints\n"
            "you have no choice in that matter... :D but you can tell me how\n"
            "many ints you want.  So...how many?\n";
    num_elements = intcheck();
    cout << "\nGreat!  I'm making you a BST with " << num_elements << " ints!"
         << endl;
    cout << "One more thing, what is the range of elements you want?" << endl;
    cout << "You can even do negative numbers!  Fist, the low range: ";
    range_low = intcheck();
    cout << "And now the high range please: ";
    range_high = intcheck();

    high_resolution_clock::time_point start = high_resolution_clock::now();

    if (range_low == 0) {
        for (int i = 0; i < num_elements; ++i) {
            b.insert(rand() % (range_high + 1));
        }
    }
    else if (range_low > 0) {
        range_high = range_high - range_low;
        for (int i = 0; i < num_elements; ++i) {
            b.insert(rand() % (range_high + 1) + range_low);
        }
    }
    else if (range_low < 0) {
        if (range_high + range_low == 0) {
            for (int i = 0; i < num_elements; ++i) {
                b.insert(rand() % (range_high * 2) + range_low);
            }
        } else {
            range_high = range_high + (range_low * -1);
            for (int i = 0; i < num_elements; ++i) {
                b.insert(rand() % (range_high + 1) + range_low);
            }
        }
    }

    high_resolution_clock::time_point end = high_resolution_clock::now();
    milliseconds elapsed = duration_cast<milliseconds>(end - start);
    double mili    = elapsed.count();
    double seconds = mili / 1000;

    cout << "Time Elapsed: " << mili << " milliseconds" << endl;
    
    cout << "Time Elapsed: " << seconds << " seconds" << endl;

    cout << "\nHere is your Binary Search Tree!!\n" 
            "Duplicate numbers are denoted by an '*'." << endl;
    // b.print_tree();
    return b;
}

// Function:   whatYouCanDo
// Parameters: none
// Returns:    nothing
// Does:       Prints to user what they can do with the BST
void whatYouCanDo() 
{
    cout << endl;
    cout << "Here's what you can do with your newly created BST!\n";
    cout << "If below you see [enter] this means you will be prompted for \n";
    cout << "more input after hitting enter!  Otherwise, hitting enter will\n";
    cout << "Just do the thing it says it does.\n\n";
    cout << "TYPE:                      DOES: \n\n";     
    cout << "      io                         prints inOrder traversal\n";
    cout << "      ior                        prints inOrder reversed\n";
    cout << "      post                       prints postOrder traversal\n";
    cout << "      pre                        prints preOrder traversal\n";
    cout << "      lo                         prints levelOrder traversal\n";
    cout << "      ins     [value]            inserts a value\n";
    cout << "      insmany [enter]            inserts many values\n";
    cout << "      remove  [value]            removes a value\n";
    cout << "      find    [value]            finds a value\n";
    cout << "      findmax                    finds max value\n";
    cout << "      findmin                    finds min value\n";
    cout << "      howmany  [value]           finds # of a given value\n";
    cout << "      findpath [value]           finds path to value\n";
    cout << "      treeheight                 finds the height of the BST\n";
    cout << "      add                        adds all values in BST\n";
    cout << "      findeven                   # of all even values in BST\n";
    cout << "      findodd                    # of all odd values in BST\n";
    cout << "      nodecount                  number of nodes in BST\n";
    cout << "      root                       prints root value\n";
    cout << "      removeall                  removes all elements\n";
    cout << "      makenew [enter]            makes a new BST\n";
    cout << "      bushify                    makes BST Bushier!\n";
    cout << "      rocketman                  makes BST into a ROCKET!!\n";
    cout << "      pp                         prints out a pretty tree!\n";
    cout << "      what?                      prints this again!\n";
    cout << "      exit                       quits and destroys BST\n\n";
}

// Function:   dostuff
// Parameters: a pointer to a BinarySearchTree object
// Returns:    nothing
// Does:       driver for the program.  Takes in user commands and does stuff
//             with the bst like bushify and rocketman!  try it out!  
void dostuff(BinarySearchTree *b) 
{
    string command = "";
    cout << "So, what would you like to do?\n";
    cout << "Command: ";
    cin >> command;

    while (command != "exit") {
        if (command == "io")
        {
            high_resolution_clock::time_point start = b->getStart();
            b->inOrder();
            b->printRuntime(start);
        }
        else if (command == "ior")
        {
            high_resolution_clock::time_point start = b->getStart();
            b->inOrderReverse();
            b->printRuntime(start);
        }
        else if (command == "post")
        {
            high_resolution_clock::time_point start = b->getStart();
            b->postOrder();
            b->printRuntime(start);
        }
        else if (command == "pre")
        {
            high_resolution_clock::time_point start = b->getStart();
            b->preOrder();
            b->printRuntime(start);
        }
        else if (command == "lo")
        {
            high_resolution_clock::time_point start = b->getStart();
            b->levelOrder();
            b->printRuntime(start);
        }
        else if (command == "ins")
        {
            int val = intcheck();
            high_resolution_clock::time_point start = b->getStart();
            b->insert(val);
            b->printRuntime(start);
        }
        else if (command == "insmany")
        {
            cout << "How many Elements?: ";
            int numElem   = intcheck();
            cout << "Range Low?: ";
            int rangelow  = intcheck();
            cout << "Range High?: ";
            int rangehigh = intcheck();
            high_resolution_clock::time_point start = b->getStart();
            b->insMany(numElem, rangelow, rangehigh);
            b->printRuntime(start);
        }
        else if (command == "remove")
        {
            int val = intcheck();
            high_resolution_clock::time_point start = b->getStart();
            b->remove(val);
            b->printRuntime(start);
        }
        else if (command == "find")
        {
            int val = intcheck();
            high_resolution_clock::time_point start = b->getStart();
            if (b->contains(val)) {
                cout << "Value " << val << " is in the BST!" << endl;
            } else {
                cout << "Value " << val << " is NOT in the BST!" << endl;
            }
            b->printRuntime(start);
        }
        else if (command == "findmax") 
        {
            high_resolution_clock::time_point start = b->getStart();
            cout << "Max Value is: " << b->find_max() << endl;
            b->printRuntime(start);
        }
        else if (command == "findmin") 
        {
            high_resolution_clock::time_point start = b->getStart();
            cout << "Min Value is: " << b->find_min() << endl;
            b->printRuntime(start);
        }
        else if (command == "findpath")
        {
            int val = intcheck();
            high_resolution_clock::time_point start = b->getStart();
            cout << b->findPath(val);
            b->printRuntime(start);
        }
        else if (command == "add")
        {
            high_resolution_clock::time_point start = b->getStart();
            cout << b->count_total();
            b->printRuntime(start);
        }
        else if (command == "what?")
        {
            whatYouCanDo();
        }
        else if (command == "findeven")
        {
            high_resolution_clock::time_point start = b->getStart();
            cout << b->findEven();
            b->printRuntime(start);
        }
        else if (command == "findodd")
        {
            high_resolution_clock::time_point start = b->getStart();
            cout << b->findOdd();
            b->printRuntime(start);
        }
        else if (command == "root") 
        {
            if (b->isEmpty()) {
                cout << "EMPTY BST!!" << endl;
            } else {
                cout << b->getRootVal() << endl;
            }
        }
        else if (command == "nodecount")
        {
            high_resolution_clock::time_point start = b->getStart();
            cout << b->node_count();
            b->printRuntime(start);
        }
        else if (command == "removeall")
        {
            high_resolution_clock::time_point start = b->getStart();
            b->removeAll();
            b->printRuntime(start);
        }
        else if (command == "pp")
        {
            high_resolution_clock::time_point start = b->getStart();
            b->print_tree();
            b->printRuntime(start);
        }
        else if (command == "treeheight")
        {
            high_resolution_clock::time_point start = b->getStart();
            cout << "The height of the BST is: " << b->tree_height();
            cout << endl;
            b->printRuntime(start);
        }
        else if (command == "bushify")
        {
            high_resolution_clock::time_point start = b->getStart();
            b->bushify_tree();
            b->printRuntime(start);
        }
        else if (command == "rocketman")
        {
            high_resolution_clock::time_point start = b->getStart();
            b->rocketMan();
            b->printRuntime(start);
        }
        else if (command == "howmany")
        {
            int val = intcheck();
            high_resolution_clock::time_point start = b->getStart();
            b->howMany(val);
            b->printRuntime(start);
        }
        else if (command == "makenew")
        {
            cout << "How many Elements?: ";
            int numElem   = intcheck();
            cout << "Range Low?: ";
            int rangelow  = intcheck();
            cout << "Range High?: ";
            int rangehigh = intcheck();
            high_resolution_clock::time_point start = b->getStart();
            BinarySearchTree b2 = b->makeNew(numElem, rangelow, rangehigh);
            cout << "We made you a noiiiccee BST with " << numElem 
                 << " elements!" << endl;
            *b = b2;
            b->printRuntime(start);
        }
        else {
            cout << "Invalid Input!  Try again!" << endl;
        }
        cout << "\nCommand: ";
        cin >> command;
    }
}

// Function:   intcheck ** Helper function for user input **
// Parameters: none
// Returns:    an int taken in with cin.
// Does:       provides a way to ensure user input is always an int.  If they 
//             enter anything else, it will complain and demand the user type
//             the int again.
int  intcheck() 
{
    int val;
    cin >> val;
    while (cin.fail()) {
        cin.clear();
        cin.ignore();
        cout << "Invalid Input! Enter a Number Please!" << endl;
        cin >> val;
    }
    return val;
}









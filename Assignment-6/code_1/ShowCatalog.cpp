#include "ShowCatalog.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

ShowCatalog::ShowCatalog() {
    // TODO 1)
    // constructor: initalize any member variables of the class to default
    root = nullptr;
}

void destructorHelper(ShowItem* ptrRoot){
    if (ptrRoot != nullptr){
        // delete nodes in post order
        destructorHelper(ptrRoot->left);
        destructorHelper(ptrRoot->right);
        
        delete ptrRoot;
        ptrRoot = nullptr;
    }
}

// deletes all nodes in tree
ShowCatalog::~ShowCatalog() {
    // TODO 2)
    // destructor: free all memory that was allocated
    // traverse through the whole list and delete as you go, set root = nullptr
    destructorHelper(root);
}

// will print out the tree in pre order
void printShowHelper(ShowItem *currShow){
    if (currShow){
        cout << "Show: " << currShow->title << " " << currShow->userRating << endl;
        printShowHelper(currShow->left);
        printShowHelper(currShow->right);
    }
}

void ShowCatalog::printShowCatalog() {
    // TODO 3)
    ShowItem *current = root;
    if (current == nullptr){
        cout << "Tree is Empty. Cannot print" << endl;
    }
    else {
        printShowHelper(current);
    }
}
// will find show we need by traversing through the tree
ShowItem* getShowHelper(ShowItem* currShow, string showTitle){
    if (currShow != nullptr){
        if (showTitle == currShow->title){
            return currShow;
        }
        else if (showTitle < currShow->title){
            currShow = getShowHelper(currShow->left, showTitle);
        }
        else if (showTitle > currShow->title){
            currShow = getShowHelper(currShow->right, showTitle);
        }
        else {
            currShow = nullptr;
        }
    }
    return currShow;
}

void ShowCatalog::getShow(string title) {
    // TODO 4)
    // find the show with the given title, then print out its information:

    // if the show isnt found, print this message instead:
    // cout << "Show not found." << endl;
    ShowItem* desiredNode = root;
    desiredNode = getShowHelper(desiredNode, title);
    if (desiredNode == nullptr){
        cout << "Show not found." << endl;
    }
    else {
        cout << "Show Info:" << endl;
        cout << "==================" << endl;
        cout << "Title :" << desiredNode->title << endl;
        cout << "Year :" << desiredNode->year << endl;
        cout << "Show Rating :" << desiredNode->showRating << endl; cout << "User Rating :" << desiredNode->userRating << endl;
    }
}

ShowItem* addShowHelper(ShowItem *currShow, ShowItem *showName){
    
    if(currShow == nullptr){
        return new ShowItem(*showName);
    }
    else if(showName->title < currShow->title){
        currShow->left = addShowHelper(currShow->left, showName);
    }
    else if(showName->title > currShow->title){
        currShow->right = addShowHelper(currShow->right, showName);
    }
    return currShow;
}

void ShowCatalog::addShowItem(string title, int year, string showRating, float userRating) {
    // TODO 3)
    ShowItem* temp = new ShowItem(title, year, showRating, userRating);
    root = addShowHelper(root, temp);
    delete temp;
}
// will find and print all leaf nodes
void printLeafHelper(ShowItem *currNode){
    // if node is null, return
    if (currNode == nullptr){
        return;
    }
    // if node is a leaf node, print
    if (currNode->left == nullptr && currNode->right == nullptr){
        cout << currNode->title << endl;
        return;
    }
    // if the left child exists, find leaf
    if (currNode->left != nullptr){
        printLeafHelper(currNode->left);
    }
    // if the right child exists, find leaf
    if (currNode->right != nullptr){
        printLeafHelper(currNode->right);
    }
    
}
 
void ShowCatalog::printLeafNodes() {
    // TODO 7)
    // print all leaf nodes of the BST using the following format:
    // cout << root->title << endl;
    ShowItem* rootptr = root;
    printLeafHelper(rootptr);
    
}

void searchShowsHelper(ShowItem* currNode, char titleChar , ShowItem* showsWithChar[], int i, int* counter){
    //ShowItem* desiredShowsArray[10];
    // TODO:: needs to find all the nodes starting with the letter, not just the first one
    if (currNode == nullptr){
            return;
        }
    if (currNode->title.at(0) == titleChar && currNode->title != showsWithChar[i]->title){
        showsWithChar[i] = currNode;
        i += 1;
        *counter = *counter + 1;
    }
    
    if (currNode->left){
        searchShowsHelper(currNode->left, titleChar,showsWithChar, i, counter);
    }
    
    if (currNode->right){
        searchShowsHelper(currNode->right, titleChar, showsWithChar, i, counter);
    }
    
}
void ShowCatalog::searchShows(char titleChar) {
    // TODO 5)
    ShowItem* desiredShow = root;
    ShowItem* desiredShowArray[10];
    int counter = 0;
    int* counterptr = &counter;
    if (root == nullptr){
        cout << "Tree is Empty. Cannot search Shows" << endl;
    }
    else {
        searchShowsHelper(desiredShow, titleChar, desiredShowArray, 0, counterptr);
        
        cout << "Shows that starts with " << titleChar << ":" << endl;
        for (int i = 0; i < counter; i ++){
            cout << desiredShowArray[i]->title << "(" << desiredShowArray[i]->year << ") " << desiredShowArray[i]->userRating << endl;
        }
    }
}

void displayNumRatingHelper(ShowItem* currNode, string showRating, int &count){
    // similar to search shows function, and updates count every time it finds a show
    if (currNode == nullptr){
        return;
    }
    if (currNode->showRating == showRating){
        count = count + 1;
    }
    if (currNode->left){
        displayNumRatingHelper(currNode->left, showRating, count);
    }
    if (currNode->right){
        displayNumRatingHelper(currNode->right, showRating, count);
    }
}
void ShowCatalog::displayNumShowRating(int &count, string showRating) {
    // TODO 6)
    // change the reference variable count ot have count of all shows with showRating given in the parameters
    // basically the count will be the number of movies that have the rating of showRating
    ShowItem* rootptr = root;
    displayNumRatingHelper(rootptr, showRating, count);
}

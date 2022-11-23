#include "ShowCatalog.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

/* Completed functions. DO NOT MODIFY*/
ShowCatalog::ShowCatalog()
{
    root = nullptr;
}

/* Completed functions. DO NOT MODIFY*/
void destroyNode(ShowItem *current)
{
    if (current != nullptr)
    {
        destroyNode(current->left);
        destroyNode(current->right);

        delete current;
        current = nullptr;
    }
}

/* Completed functions. DO NOT MODIFY*/
ShowCatalog::~ShowCatalog()
{
    destroyNode(root);
}

/* Completed functions. DO NOT MODIFY*/
void printShowHelper(ShowItem *m)
{
    if (m != nullptr)
    {
        cout << "Show: " << m->title << " " << m->userRating << endl;
        printShowHelper(m->left);
        printShowHelper(m->right);
    }
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::printShowCatalog()
{
    if (root == nullptr)
    {
        cout << "Tree is Empty. Cannot print" << endl;
        return;
    }
    printShowHelper(root);
}

/* Completed functions. DO NOT MODIFY*/
ShowItem *getShowHelper(ShowItem *current, string title)
{
    if (current == NULL)
        return NULL;

    if (current->title == title)
        return current;

    if (current->title > title)
        return getShowHelper(current->left, title);

    return getShowHelper(current->right, title);
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::getShow(string title)
{
    ShowItem *node = getShowHelper(root, title);
    if (node != nullptr)
    {
        cout << "Show Info:" << endl;
        cout << "==================" << endl;
        cout << "Title :" << node->title << endl;
        cout << "Year :" << node->year << endl;
        cout << "Show Rating :" << node->showRating << endl;
        cout << "User Rating :" << node->userRating << endl;
        return;
    }

    cout << "Show not found." << endl;
}

/* Completed functions. DO NOT MODIFY*/
ShowItem *addNodeHelper(ShowItem *current, ShowItem *newNode)
{
    if (current == nullptr)
    {
        return newNode;
    }

    if (current->title > newNode->title)
    {
        current->left = addNodeHelper(current->left, newNode);
    }
    else
    {
        current->right = addNodeHelper(current->right, newNode);
    }

    return current;
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::addShowItem(string title, int year, string showRating, float userRating)
{
    if (root == nullptr)
    {
        root = new ShowItem(title, year, showRating, userRating);
        return;
    }

    root = addNodeHelper(root, new ShowItem(title, year, showRating, userRating));
}

/* TODO */
// make min value finder function
ShowItem* findSmallestVal(ShowItem* currNode){
    ShowItem* current = currNode;
    while (current && current->left != nullptr){
        current = current->left;
    }
    return current;
}

ShowItem* removeShowHelper(ShowItem* currNode, string title){
    if (currNode){
        if (title > currNode->title){
            currNode->right = removeShowHelper(currNode->right, title);
        }
        else if (title < currNode->title){
            currNode->left = removeShowHelper(currNode->left, title);
        }
        else {
            if (currNode->left == nullptr && currNode->right == nullptr){
                delete currNode;
                currNode = nullptr;
                return nullptr;
            }
            else if (currNode->left != nullptr && currNode->right == nullptr){
                ShowItem* temp = currNode->left;
                delete currNode;
                currNode = nullptr;
                return temp;
            }
            else if (currNode->right != nullptr && currNode->right == nullptr){
                ShowItem* temp = currNode->right;
                delete currNode;
                currNode = nullptr;
                return temp;
            }
            else {
                ShowItem* minValNode = findSmallestVal(currNode->right);
                currNode->title = minValNode->title;
                currNode->userRating = minValNode->userRating;
                currNode->right = removeShowHelper(currNode->right, minValNode->title);
                return currNode;
            }
        }
    }
    return currNode;
}

void ShowCatalog::removeShow(std::string title)
{
    // TODO 1)
    root = removeShowHelper(root, title);
}

/* TODO */
ShowItem* findParentPtr(ShowItem* currNode, string title){
    if (currNode == nullptr){
        return nullptr;
    }
    else if (currNode->right != nullptr && currNode->right->title == title){
        return currNode;
    }
    else if (currNode->left != nullptr && currNode->left->title == title){
        return currNode;
    }
    else if (currNode->title > title){
        return findParentPtr(currNode->left, title);
    }
    else {
        return findParentPtr(currNode->right, title);
    }
}

void ShowCatalog::rightRotate(std::string title)
    {
        // TODO 2)
        ShowItem* show = getShowHelper(root, title);
        
        if (show == nullptr || show->left == nullptr){
            return;
        }
        ShowItem* showLeft = show->left;
        show->left = showLeft->right;
        
        ShowItem* parent = findParentPtr(root, title);
        
        if (parent == nullptr){
            root = showLeft;
        }
        else if (parent->left == show){
            parent->left = showLeft;
        }
        else {
            parent->right = showLeft;
        }
        showLeft->right = show;
    }

void ShowCatalog::leftRotate(std::string title)
{
    // TODO 3)
    ShowItem* show = getShowHelper(root, title);
    
    if (show == nullptr || show->right == nullptr){
        return;
    }
    ShowItem* showRight = show->right;
    
    show->right = showRight->left;
    
    ShowItem* parent = findParentPtr(root, title);
    
    if (parent == nullptr){
        root = showRight;
    }
    else if (parent->left == show){
        parent->left = showRight;
    }
    else {
        parent->right = showRight;
    }
    showRight->left = show;
}

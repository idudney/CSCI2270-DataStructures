/*************************************************************/
/*                   ShowsList Definition                    */
/*************************************************************/
/* TODO: Implement the member functions of class ShowsList   */
/*     This class uses a linked-list of Show structs to      */
/*     represent the schedule of shows                       */
/*************************************************************/

#include "ShowsList.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

/*
 * Purpose: Constructor for empty linked list
 * @param none
 * @return none
 */
ShowsList::ShowsList() {
    /*
    DO NOT MODIFY THIS
    This constructor is already complete. 
    */
    head = nullptr;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool ShowsList::isEmpty() {
    /* finished. do not touch. */
    return (head == NULL);
}

/*
 * Purpose: prints the current list of shows nicely
 * @param none
 * @return none
 */
void ShowsList::displayShows() {
    // TODO: Copy-paste your solution from Assignment 3
    Show* showPtr = head;
    
    if (head == nullptr){ // if the linked list is empty
        cout << "nothing in path" << endl;
    }
    
    else { // otherwise, print out the shows list
        cout << "== CURRENT SHOWS LIST ==" << endl;
        while (showPtr != nullptr){
            cout << showPtr->name << "-> ";
            showPtr = showPtr->next;
        }
        
        cout << "NULL" << endl;
        cout << "===" << endl;
    }
}


/*
 * Purpose: Add a new show to the shows linked list
 *   between the previous and the show that follows it in the list.
 * @param previousShow the show that comes before the new show
 * @param showName name of the new Show
 * @return none
 */
void ShowsList::addShow(Show* previousShow, string showName) {
    // TODO: Copy-paste your solution from Assignment 3
    Show *newShow = new Show();
    newShow->name = showName;
    
    if (previousShow == nullptr){
        // add show to the beginning of list
        cout << "adding: " << showName << " (HEAD)" << endl;
        newShow->next = head;
        head = newShow;
    }
    
    else if (previousShow->next == nullptr){
        // add show to the end of list
        // the next show name gets added after the previous show
        previousShow->next = newShow;
        cout << "adding: " << showName << " (prev: " << previousShow->name << ")" << endl;
    }
    
    else {
        newShow->next = previousShow->next;
        previousShow->next = newShow;
        cout << "adding: " << showName << " (prev: " << previousShow->name << ")" << endl;
    }
}

/*
 * Purpose: populates the ShowsList with the predetermined shows
 * @param none
 * @return none
 */
void ShowsList::buildShowsList() {
    // TODO: Copy-paste your solution from Assignment 3
    purgeCompleteShowList();
       
       string showArray[5] = {"Friends","Ozark","Stranger Things","The Boys","Better Call Saul"};
       //int i = 0;
       for (int i = 0; i < 5; i ++){
           string currentShow = showArray[i];
           if (i == 0){
               Show* previousShow = searchShow(showArray[i]);
               addShow(previousShow, currentShow);
           }
           else{
               Show* previousShow = searchShow(showArray[i-1]);
               addShow(previousShow, currentShow);
           }

       } 
}

/*
 * Purpose: Search the ShowsList for the specified show and return a pointer to that node
 * @param showName - name of the show to look for in list
 * @return pointer to node of show, or NULL if not found
 *
 */
Show* ShowsList::searchShow(string showName) {
    // TODO: Copy-paste your solution from Assignment 3
    if (head == nullptr){
        return nullptr;
    }
    // if head is not null, iterate from head to the end and find show name that is equal and return it
    Show* current = head;
    while(current != nullptr){
        if (current->name == showName){
            return current;
        }
        else {
            current = current->next;
        }
    }
    return nullptr;
}

/*
 * Purpose: Give a new rating to a show
 * @param receiver - name of the show that is receiving the rating
 * @param rating - the rating that is being given to a show
 * @return none
 */
void ShowsList::addRating(string receiver, double rating) {
    // TODO: Copy-paste your solution from Assignment 3
    Show* receiverRating = searchShow(receiver);
    
    if (head == nullptr){
        cout << "Empty list" << endl;
    }
    else if(receiverRating == nullptr){
        cout << "Show not found" << endl;
    }
    else {
        receiverRating->numberRatings++;
        receiverRating->rating = (receiverRating->rating*(receiverRating->numberRatings-1) + rating)/receiverRating->numberRatings;
        cout << "The rating has been updated: " << receiverRating->rating << endl;
    }
}


/****************************************************/
/*  ASSIGNMENT 4: Functions to be completed below.  */
/****************************************************/


/*
 * Purpose: Delete the Show in the list with the specified name.
 * @param showName - name of the Show to delete in the list.
 * @return none
 */
void ShowsList::removeShows(string showName)
{
    //TODO: Complete this function
    // TODO 2)
  
    Show *showNameptr = nullptr;
    showNameptr = searchShow(showName);
    
    if (showNameptr == nullptr) {
         cout << "Show does not exist." << endl;
        return;
    }
    
    // if the show we want to delete is the head
    if (showNameptr == head){
        Show *temp = head;
        head = head->next;
        delete temp;
        temp = nullptr;
    }
    // if the show we want to delete is not the head
    Show *pres = head;
    Show *prev = nullptr;
    
    if (showNameptr != nullptr) {
        while (prev != showNameptr && pres!= nullptr){
            prev = pres;
            pres = pres->next;
            if (pres == showNameptr){
                prev->next = pres->next;
                delete pres;
                pres = nullptr;
                break;
            }
        }
    }
}

/*
 * Purpose: deletes all Shows in the list starting from the head of the linked list.

 * @param: none
 * @return: none
 */
void ShowsList::purgeCompleteShowList()
{
    // TODO: Complete this function
    // TODO 3) DONE
    
    Show *showName = head;
    if (head == nullptr){
        return;
    }

    while (head != nullptr){
        showName = head;
        head = showName->next;
        cout << "deleting: " << showName->name << endl;
        delete showName;
        showName = nullptr;
    }
    cout << "Deleted show list" << endl;
}

/*
* Purpose: Creates a loop from last node to the show name specified.
* @param showName - name of the show to loop back to
* returns the last node before loop creation (to break the loop)
*/
Show* ShowsList::produceGlitch(string showName) 
{
    /*
    DO NOT MODIFY THIS
    This function is already complete. 
    */
    Show* ptr = searchShow(showName);
    Show* temp = head;
    while(temp && temp->next!=NULL){
        temp=temp->next;
    }
    if(ptr && temp)
        temp->next=ptr;
    return temp;
}

/*
 * Purpose: to detect loop in the linked list
 * @return: true if loop is detected, else false
 */
bool ShowsList::findGlitch() 
{
    // TODO: Complete this function
    // TODO 1)
    
    Show *slowptr = head;
    Show *fastptr = head;
    while (slowptr != nullptr && fastptr->next != nullptr){
        slowptr = slowptr->next;
        fastptr = fastptr->next->next;
        if (slowptr == fastptr){
            return true;
            break;
        }
    }
   
    return false;
}

void ShowsList::rearrangeShowList(int start, int end)
{
    // TODO: Complete this function
    // TODO 4) manipulate next pointer to re-adjust the linked list
    
    Show *startptr = head;
    Show *endptr = head;
    Show *tailptr = head;
    int startIndex = start;
    int endCounter = 0;
    int endCounter2 = end;
    
    if (head == nullptr){
        cout << "Linked List is Empty" << endl;
    }
    while (tailptr->next != nullptr){
        tailptr = tailptr->next;
        endCounter += 1;
    }
    
    if (start != 0){
        while (startptr != nullptr){
            startptr = startptr->next;
            startIndex -= 1;
            if (startIndex == 0){
                break;
            }
        }
    }
    if (start == 0){
        startptr = head;
    }
    
    while (endptr != nullptr){
        endptr = endptr->next;
        endCounter2 -= 1;
        if (endCounter2 == 0){
            break;
        }
    }
    // now we have a pointer to the start index, the end index, and the tail
    // we want to set everything after tail = everything between start and end index, then set the end->next = nullptr
    if (endptr == tailptr){
        return;
    }
    // if the end index is greater than or equal to the number of nodes
    if (end >= endCounter){
        cout << "Invalid end index" << endl;
        return;
    }
    Show* beforeStartptr = head;
    Show* endptr1 = endptr;
    Show* endptr2 = endptr;
    Show* endptr3 = endptr;
    
    // i somehow need a pointer to the ORIGINAL linked list
    if (startptr != head && start != end){
        while (beforeStartptr->next != startptr){
            beforeStartptr = beforeStartptr->next;
        }
        while (endptr2 != tailptr){
            // to check if endptr ever reaches the tail
            endptr2 = endptr2->next;
            // to set the endptr to the endptr next
            endptr1 = endptr->next;
            // we want the node before the start to point to the end of the index
            beforeStartptr->next = endptr1;
            // we want the endptr1 node to point to the start ptr
            endptr1->next = startptr;
            startptr = startptr->next;
        }
        endptr3->next = nullptr;
    }
    // if the start index = 0
    // set new pointer = our original tail pointer
    Show *startptr2 = startptr;
    Show *afterEndptr = head;
    if (startptr == head){
        Show *newSpot = new Show();
        
        head = endptr->next;
        while (afterEndptr!= endptr->next){
            // retrievs a pointer to the node after the end
            afterEndptr = afterEndptr->next;
        }
        // will put all of the nodes from beginning index to end, at the end of the list or after the tail
        while (startptr2 != afterEndptr){
            startptr2 = startptr2->next;
            newSpot = startptr;
            tailptr->next = newSpot;
            startptr = startptr->next;
            //tailptr->next = newSpot;
            tailptr = tailptr->next;
        }
        //startptr2->next = nullptr;
        tailptr->next = nullptr;
    }
    //Show *headptr = head;
    if (start == end){
        Show *newSpot = new Show();
        tailptr->next = newSpot;
        head->next = startptr->next;
        newSpot = startptr;
        return;
    }
    //displayShows();
     
}

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
    // TODO 1)
    // Print the names of each node in the linked list. Below is an example of correct output using the default setup.
    /*
     == CURRENT SHOWS LIST ==
     Friends-> Ozark-> Vikings-> Stranger Things-> Boys-> NULL
     
     ===
     */
    
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
    // TODO 2)
    // Insert a new show with name showName in the linked list after the show pointed to by previousShow.
    // If previousShow is NULL, then add the new show to the beginning of the list.
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

    // TODO:: for some reason this function is setting the next node after head to null
}


/*
 * Purpose: populates the ShowsList with the predetermined shows
 * @param none
 * @return none
 */
void ShowsList::buildShowsList() {
    // TODO 3)
    // for every show, we need to call the addShow function and pass the previous movie, and the next movie in. we will find the previous movie by building our searchShow function, we will then pass the movie we were just on through that function, and it will return our "previous" movie.
    Show* next;
    while(head != NULL){
        next = head->next;
        delete head;
        head = next;
    }
    
    string showArray[5] = {"Friends","Ozark","Stranger Things","The Boys","Better Call Saul"};
    int i = 0;
    do {
        string currentShow = showArray[i];
        Show* previousShow = searchShow(showArray[i-1]);
        i ++;
        addShow(previousShow, currentShow);
    } while(i != 5);
   
    /*
     Add the following six shows, in order, to the list with addShow:
     1) "Friends"
     2) "Ozark"
     3) "Vikings:
     4) "Stranger Things"
     5) "The Boys"
     6) "Better Call Saul"
     - this is the default setup of shows in the linked list, so you can keep 0 as the rating value and the numberRatings for each of them
     */
    // we want the head to be Friends, and the tail to be better call saul
    
    
}

/*
 * Purpose: Search the ShowsList for the specified show and return a pointer to that node
 * @param showName - name of the show to look for in list
 * @return pointer to node of show, or NULL if not found
 *
 */
Show* ShowsList::searchShow(string showName) {
    // TODO 4)
    // return a pointer to the node with showName
    // if showName cannot be found, return NULL
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
    // TODO 5)
    /*
     - Find the node with the name receiver
     - for the reciever node, update the rating
     - update the rating following the running average rating formula of the previous assignment
     - update the numberRatings too
     
        node->numberRatings++;
        node->rating = (node->rating*(node->numberRatings-1) + rating)/node->numberRatings
     
     - if the list is empty, print "Empty list" and exit the function and print endl
     - if the node is not present, print "Show not found", and print endl
     - otherwise, print the updated rating using the following cout assuming temp is pointing to the concerned node
     
        cout << "The rating has been updated: " << node->rating << endl;
     */
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

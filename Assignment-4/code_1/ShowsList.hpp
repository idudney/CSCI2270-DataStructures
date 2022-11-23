/****************************************************************/
/*                     ShowsList Definition                     */
/****************************************************************/
/* LEAVE THIS FILE AS IS! DO NOT MODIFY ANYTHING! =]            */
/****************************************************************/

//#pragma once
#ifndef ShowsList_HPP__
#define ShowsList_HPP__
#include <iostream>

using namespace std;

// Show: node struct that will be stored in the ShowsList linked-list
struct Show
{
    std::string name;          // name of the show
    double rating;             // rating this show has received
    int numberRatings;         // no. of ratings passed through this show
    Show *next;                // pointer to the next show
};

// class for storing and manipulating linked-list of shows
class ShowsList {
    private:
        // pointer to head of linked-list of shows
        Show* head;
    public:
        // See writeup for method descriptions
        ShowsList();
        bool isEmpty();
        void displayShows();
        void addShow(Show* previousShow, std::string showName);
        void buildShowsList();
        Show* searchShow(std::string showName);
        void addRating(std::string receiver, double rating);
        
        /* Assignment-4 related functions*/
        void removeShows(std::string showName);
        void purgeCompleteShowList();
        Show* produceGlitch(std::string showName);
        bool findGlitch();
        void rearrangeShowList(int start, int end);
};
#endif

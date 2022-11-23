#include "EnqueueDequeue.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

EnqueueDequeue::EnqueueDequeue(){
	/* Already implemented, don't change */
    queueFront = -1;
	queueEnd = -1;
}

bool EnqueueDequeue::isEmpty(){
	//TODO
    // return true if the queue is empty
    // return false otherwise
    if (counter == 0){
        return true;
    }
    return false;
}

bool EnqueueDequeue::isFull(){
	//TODO
    // return true if the queue is full
    // return false otherwise
    if (counter == SIZE){
        return true;
    }
    return false;
}

void EnqueueDequeue::enqueue(std::string show){
	//TODO
    if (isFull()){
            cout << "Queue full, cannot add a new show" << endl;
        }
    if (!isFull()){
        if (isEmpty()){
            queueFront = 0;
            queueEnd = queueEnd + 1;
            queue[queueFront] = show;
            counter ++;
        }
        else {
            if (queueEnd +1 != SIZE){
                queue[queueEnd+1] = show;
            }
            queueEnd = (queueEnd+1)%SIZE;
            counter ++;
        }
    }
}


void EnqueueDequeue::dequeue(){
	//TODO
    // remove the first show from the queue if the quue is not empty and modify queueFront and/or queueEnd if appropriate
    // otherwise print "Queue empty, cannot dequeue show"
    string show = "";
    if (isEmpty()){ // if the queue is empty
        cout << "Queue empty, cannot dequeue show" << endl; // print out error message
    }
    if (!isEmpty()){
        if (counter > 1){ // if there is more than 1 show in the queue
            queue[queueFront] = ""; // delete it
            queueFront = (queueFront+1)%SIZE; // update queue front
            counter--;
        }
        else if (counter == 1){// if there is only one show left
            queue[queueFront] = ""; // delete it
            queueEnd = -1; // reset index
            queueFront = -1;// reset index
            counter = 0;
        }
    }
}


string EnqueueDequeue::peek(){
	//TODO
   
    if(isEmpty()){ // if the queue is empty
        cout << "Queue empty, cannot peek" << endl; // print error message and return blank string
        return "";
    }
    return queue[queueFront]; // otherwise return the front of the queue
}

int EnqueueDequeue::queueSize(){
    //TODO
    // return the number of shows in the queue
    return counter;
}

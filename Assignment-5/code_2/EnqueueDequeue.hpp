#ifndef ENQUEUEDEQUEUE_H__
#define ENQUEUEDEQUEUE_H__

/****************************************************************/
/*                    EnqueueDequeue Class                      */
/****************************************************************/
/* LEAVE THIS FILE AS IS! DO NOT MODIFY ANYTHING! =]            */
/****************************************************************/
#pragma once

#include <string>

const int SIZE = 20;

class EnqueueDequeue
{
private:
  int queueFront; //the index in queue[] that will be dequeued next
  int queueEnd; //the index in queue[] that was most recently enqueued
  int counter = 0; //to keep track the number of shows in the queue
  std::string queue[SIZE];

public:
  EnqueueDequeue();
  bool isEmpty();
  bool isFull();
  void enqueue(std::string show);
  void dequeue();
  std::string peek();
  int queueSize();   
  int getQueueFront() { return queueFront; } //used for testing
  int getQueueEnd() { return queueEnd; }     //used for testing
  std::string* getQueue() { return queue; }  //used for testing
};
#endif
#include <iostream>
#include <cstdlib>
#include <iostream>
#include "MessageDecoder.hpp"

using namespace std;
# define SIZE 50

MessageDecoder::MessageDecoder()
{
	/*
    DO NOT MODIFY THIS
    This constructor is already complete. 
    */
	head = NULL;
}

MessageDecoder::~MessageDecoder()
{
	// TODO 5)
    // pop everything off the stack and set head to NULL
}

bool MessageDecoder::isEmpty()
{
	/* finished. do not touch. */
    return (head == NULL);
}

void MessageDecoder::push(char ch)
{
	// TODO 1)
    // insert a new node with ch onto the top of the stack (beginning of linked list)
    Parser *temp = new Parser;
    temp->ch = ch;
    if (isEmpty()){
        head = temp;
        head->next = nullptr;
    }
    else {
        temp->next = head;
        head = temp;
    }
}

void MessageDecoder::pop()
{   
	// TODO 2)
    Parser *headptr = head;
    // if the stack is empty, print "Stack empty, cannot pop an item." and return.
    if (isEmpty()){
        cout << "Stack empty, cannot pop an item." << endl;
        return;
    }
    // if the stack is not empty, delete the top most item from the stack
    else {
        head = head->next;
        delete headptr;
    }
}

Parser* MessageDecoder::peek()
{
	// TODO 3)
    // if the stack is empty, print "Stack empty, cannot peek." and return NULL.
    // if the stack is not empty, return a pointer to the top of the stack
    if (isEmpty()){
        cout << "Stack empty, cannot peek." << endl;
        return nullptr;
    }
    else {
        Parser *topPtr = head;
        return topPtr;
    }
	return nullptr;
}

void MessageDecoder::evaluate(char str[])
{
    Parser *currChar = head;
    char secretMessage[50];
    for (int i = 0; str[i] != '\0' && i < SIZE; i ++){
        push(str[i]);
        
    }
    Parser *headptr = head;
    Parser *firstCharptr = head;
    int j = 0;
    currChar = headptr;
    while (currChar != nullptr && currChar->ch != '}'){
        firstCharptr = firstCharptr->next;
        currChar = currChar->next;
    }
    if (firstCharptr!= nullptr){
        firstCharptr = firstCharptr->next;
    }
    else {
        cout << "No secret message" << endl;
    }
    while (firstCharptr != nullptr && firstCharptr->ch != '{'){
        secretMessage[j] = firstCharptr->ch;
        j +=1;
        cout << firstCharptr->ch;
        pop();
        firstCharptr = firstCharptr->next;
    }

}

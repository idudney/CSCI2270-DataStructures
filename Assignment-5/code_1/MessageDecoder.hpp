#ifndef DECODEWORDS_H__
#define DECODEWORDS_H__
#include <iostream>

struct Parser
{
    char ch;
    Parser *next;
};

class MessageDecoder
{
private:
  Parser* head; // pointer to the top of the stack

public:
  MessageDecoder();
  ~MessageDecoder();
  bool isEmpty();
  void push(char ch);
  void pop();
  Parser* peek();
  Parser* getStackHead() { return head; }
  void evaluate(char str[]);
};
#endif


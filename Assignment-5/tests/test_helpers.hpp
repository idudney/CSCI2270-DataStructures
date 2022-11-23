#ifndef TEST_H__
#define TEST_H__
#include <string>
#include <iostream>
#include <fstream>
#include <array>
#include "../code_1/MessageDecoder.hpp"
#include "../code_2/EnqueueDequeue.hpp"
using namespace std;

// TODO add detailed explanation on what the function should do
std::string exec(const char* cmd);
std::string readFileIntoString(std::string fileName);

string test_evaluate(char* arr, int length);
string test_push(char* arr, int length);
string test_pop(char* arr, int length);
string test_peek(char* arr, int length);
string test_all(char* arr, int length);


string test_consQ();
string test_enQ(string arr, int length);
string test_deQ(string arr, int length, int dequeue);
string test_peekQ(string arr, int length, int dequeue);
string test_allQ(string show, string* op, int length);


#endif // TEST_H__
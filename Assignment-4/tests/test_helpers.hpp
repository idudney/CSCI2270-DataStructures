#ifndef TEST_H__
#define TEST_H__
#include <string>
#include <iostream>
#include <fstream>
#include <array>

using namespace std;

// TODO add detailed explanation on what the function should do
std::string exec(const char* cmd);
std::string readFileIntoString(std::string fileName);

string test_removeShow(string name, bool build);
string test_purgeCompleteShowList(bool build);
string test_findGlitch(string name, bool build);
string test_rearrangeShowList(int start, int end, bool build);


#endif // TEST_H__

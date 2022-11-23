// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code_1/ShowsList.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include <iomanip>

using namespace std;

class test : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)0;
			outgrade.close();
		}
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
			std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
		}
	}

	void add_points_to_grade(double points){
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
		}
	}
	
	static double total_grade;
	static double max_grade;
};

double test::total_grade = 0;
double test::max_grade = 100;


/////////////////////////////////////////
// Test Helper Functions
/////////////////////////////////////////

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}



std::string readFileIntoString(std::string fileName){
	std::string line, out;
  	ifstream A;
  	A.open(fileName);
  	if(!A){throw std::runtime_error("could not open file: " + fileName);}
	while(getline(A,line)){
		out = out+line+"\n";
	}
	return out;
}

std::string readFileInto(std::string fileName){
	std::string line, out;
  	ifstream A;
  	A.open(fileName);
  	if(!A){throw std::runtime_error("could not open file: " + fileName);}
	while(getline(A,line)){
		out = out+line+"\n";
	}
	return out;
}

/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////

// Test the buildShowsList function [5 POINTS]
TEST_F(test, TestBuildShowsList) {
	ShowsList showList;
	testing::internal::CaptureStdout();
	showList.buildShowsList();
	string receivedOut = testing::internal::GetCapturedStdout();
	string expectedOut = "adding: Friends (HEAD)\nadding: Ozark (prev: Friends)\nadding: Stranger Things (prev: Ozark)\nadding: The Boys (prev: Stranger Things)\nadding: Better Call Saul (prev: The Boys)\n";

	ASSERT_EQ(receivedOut, expectedOut);
	add_points_to_grade(5);
}

// Test the isEmpty() function [5 POINTS]
TEST_F(test, TestIsEmpty) {
	ShowsList showList;
	
	bool isEmptyValue = showList.isEmpty();
	ASSERT_EQ(isEmptyValue, true);
	add_points_to_grade(2.5);

	testing::internal::CaptureStdout();
	showList.buildShowsList();
	
	// Not using it, but have to capture for proper
	// compilation.
	string check = testing::internal::GetCapturedStdout();
	
	isEmptyValue = showList.isEmpty();
	ASSERT_EQ(isEmptyValue, false);
	add_points_to_grade(2.5);
}

// Test the displayShows function [10 POINTS]
TEST_F(test, TestDisplayShows) {
	ShowsList showList;

	// Check for empty list
	testing::internal::CaptureStdout();
	showList.displayShows();
	string receivedOut = testing::internal::GetCapturedStdout();
	string expectedOut = "nothing in path\n";
	ASSERT_EQ(receivedOut, expectedOut);
	add_points_to_grade(5);

	// After Building once.
	testing::internal::CaptureStdout();
	showList.buildShowsList();
	string check = testing::internal::GetCapturedStdout(); //Ignore. 

	testing::internal::CaptureStdout();
	showList.displayShows();
	receivedOut = testing::internal::GetCapturedStdout();
	expectedOut = "== CURRENT SHOWS LIST ==\nFriends-> Ozark-> Stranger Things-> The Boys-> Better Call Saul-> NULL\n===\n";

	ASSERT_EQ(receivedOut, expectedOut);
	add_points_to_grade(5);
}

// Test the searchShow function [10 POINTS]
TEST_F(test, TestSearchShow) {
	ShowsList showList;

	// Check for empty list.
	Show* showPtr = showList.searchShow("Ozark");
	ASSERT_EQ(showPtr, nullptr);
	add_points_to_grade(3);

	// Build a list
	testing::internal::CaptureStdout();
	showList.buildShowsList();
	string showListOut = testing::internal::GetCapturedStdout(); // Ignore

	// Hit case.
	showPtr = showList.searchShow("Ozark");
	ASSERT_NE(showPtr, nullptr);
	ASSERT_EQ(showPtr->name, "Ozark");
	add_points_to_grade(4);

	// Miss case.
	showPtr = showList.searchShow("Dark");
	ASSERT_EQ(showPtr, nullptr);
	add_points_to_grade(3);
}

// Test the addShow function [20 POINTS]
TEST_F(test, TestAddShow) {
	ShowsList showList;

	// When previousShow is null 
	// and the list is empty.
	testing::internal::CaptureStdout();
	showList.addShow(NULL, "Dark");
	showList.displayShows();
	string addShowOut = testing::internal::GetCapturedStdout();
	string expectedAddShowOut = "adding: Dark (HEAD)\n== CURRENT SHOWS LIST ==\nDark-> NULL\n===\n";
	ASSERT_EQ(expectedAddShowOut, addShowOut);
	add_points_to_grade(5);


	// When previousShow is null
	// and the list is not empty.
	testing::internal::CaptureStdout();
	showList.addShow(NULL, "Seinfeld");
	showList.displayShows();
	addShowOut = testing::internal::GetCapturedStdout();
	expectedAddShowOut = "adding: Seinfeld (HEAD)\n== CURRENT SHOWS LIST ==\nSeinfeld-> Dark-> NULL\n===\n";
	ASSERT_EQ(expectedAddShowOut, addShowOut);
	add_points_to_grade(5);

	// Insert somewhere in the middle.
	testing::internal::CaptureStdout();
	Show* seinfeld = showList.searchShow("Seinfeld");
	showList.addShow(seinfeld, "Friends");
	showList.displayShows();
	addShowOut = testing::internal::GetCapturedStdout();
	expectedAddShowOut = "adding: Friends (prev: Seinfeld)\n== CURRENT SHOWS LIST ==\nSeinfeld-> Friends-> Dark-> NULL\n===\n";
	ASSERT_EQ(expectedAddShowOut, addShowOut);
	add_points_to_grade(5);

	// Insert at the end.
	testing::internal::CaptureStdout();
	Show* dark = showList.searchShow("Dark");
	showList.addShow(dark, "Cobra Kai");
	showList.displayShows();
	addShowOut = testing::internal::GetCapturedStdout();
	expectedAddShowOut = "adding: Cobra Kai (prev: Dark)\n== CURRENT SHOWS LIST ==\nSeinfeld-> Friends-> Dark-> Cobra Kai-> NULL\n===\n";
	ASSERT_EQ(expectedAddShowOut, addShowOut);
	add_points_to_grade(5);


}

// Test AddRating Function [20 POINTS]
TEST_F(test, TestAddRating) {
	ShowsList showList;

	testing::internal::CaptureStdout();
	showList.addRating("Friends", 4.5);
	string addShowOut = testing::internal::GetCapturedStdout();
	string expectedAddShowOut = "Empty list\n";
	ASSERT_EQ(expectedAddShowOut, addShowOut);
	add_points_to_grade(5);

	testing::internal::CaptureStdout();
	showList.addShow(NULL, "Friends");
	showList.addRating("Dark", 4);
	addShowOut = testing::internal::GetCapturedStdout();
	expectedAddShowOut = "adding: Friends (HEAD)\nShow not found\n";
	ASSERT_EQ(expectedAddShowOut, addShowOut);
	add_points_to_grade(5);

	testing::internal::CaptureStdout();
	showList.buildShowsList();
	showList.addRating("Ozark", 4);
	showList.addRating("Ozark", 4.5);
	showList.addRating("Ozark", 5.0);
	showList.addShow(NULL, "Dark");
	showList.addRating("Dark", 4.6);
	addShowOut = testing::internal::GetCapturedStdout();
	expectedAddShowOut = "adding: Friends (HEAD)\nadding: Ozark (prev: Friends)\nadding: Stranger Things (prev: Ozark)\nadding: The Boys (prev: Stranger Things)\nadding: Better Call Saul (prev: The Boys)\nThe rating has been updated: 4\nThe rating has been updated: 4.25\nThe rating has been updated: 4.5\nadding: Dark (HEAD)\nThe rating has been updated: 4.6\n";
	ASSERT_EQ(expectedAddShowOut, addShowOut);
	add_points_to_grade(10);

}


// Test the entire program [30 POINTS]
TEST_F(test, TestApp_1){
	string desired = readFileIntoString("../tests/expected_1.txt");
	string resp = exec("./run_app_1 ../tests/input_1.txt");
	ASSERT_EQ(desired, resp);
  	add_points_to_grade(10);

	desired = readFileIntoString("../tests/expected_2.txt");
	resp = exec("./run_app_1 ../tests/input_2.txt");
	ASSERT_EQ(desired, resp);
  	add_points_to_grade(10);

	desired = readFileIntoString("../tests/expected_3.txt");
	resp = exec("./run_app_1 ../tests/input_3.txt");
	ASSERT_EQ(desired, resp);
  	add_points_to_grade(10);
}

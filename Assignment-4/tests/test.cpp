// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "test_helpers.hpp"
#include "../code_1/ShowsList.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include <sstream>

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
// Tests start here
/////////////////////////////////////////

TEST_F(test, TestRemoveShow)
{
    //testcase1
    string expected_array, result;
    bool build = true;
    expected_array = "adding: Friends (HEAD)\nadding: Ozark (prev: Friends)\nadding: Stranger Things (prev: Ozark)\nadding: The Boys (prev: Stranger Things)\nadding: Better Call Saul (prev: The Boys)\n** Default list constructed **\n== CURRENT SHOWS LIST ==\nFriends-> Ozark-> Stranger Things-> The Boys-> Better Call Saul-> NULL\n===\n** Deleting Ozark!\n== CURRENT SHOWS LIST ==\nFriends-> Stranger Things-> The Boys-> Better Call Saul-> NULL\n===\n";
    result = test_removeShow("Ozark", build);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(5);
    
    //testcase2 delete @ head
    expected_array = "adding: Friends (HEAD)\nadding: Ozark (prev: Friends)\nadding: Stranger Things (prev: Ozark)\nadding: The Boys (prev: Stranger Things)\nadding: Better Call Saul (prev: The Boys)\n** Default list constructed **\n== CURRENT SHOWS LIST ==\nFriends-> Ozark-> Stranger Things-> The Boys-> Better Call Saul-> NULL\n===\n** Deleting Friends!\n== CURRENT SHOWS LIST ==\nOzark-> Stranger Things-> The Boys-> Better Call Saul-> NULL\n===\n";
    result = test_removeShow("Friends", build);

    ASSERT_EQ(expected_array, result);
    add_points_to_grade(5);
    
    //testcase3 unsucessful search
    expected_array = "adding: Friends (HEAD)\nadding: Ozark (prev: Friends)\nadding: Stranger Things (prev: Ozark)\nadding: The Boys (prev: Stranger Things)\nadding: Better Call Saul (prev: The Boys)\n** Default list constructed **\n== CURRENT SHOWS LIST ==\nFriends-> Ozark-> Stranger Things-> The Boys-> Better Call Saul-> NULL\n===\n** Deleting Manifest!\nShow does not exist.\n== CURRENT SHOWS LIST ==\nFriends-> Ozark-> Stranger Things-> The Boys-> Better Call Saul-> NULL\n===\n";
    result = test_removeShow("Manifest", build);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(5);
    
    //testcase4 empty list
    expected_array = "nothing in path\n** Deleting Manifest!\nShow does not exist.\nnothing in path\n";
    result = test_removeShow("Manifest", false);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(5);
    
    //testcase5 delete @ end
    expected_array = "adding: Friends (HEAD)\nadding: Ozark (prev: Friends)\nadding: Stranger Things (prev: Ozark)\nadding: The Boys (prev: Stranger Things)\nadding: Better Call Saul (prev: The Boys)\n** Default list constructed **\n== CURRENT SHOWS LIST ==\nFriends-> Ozark-> Stranger Things-> The Boys-> Better Call Saul-> NULL\n===\n** Deleting Better Call Saul!\n== CURRENT SHOWS LIST ==\nFriends-> Ozark-> Stranger Things-> The Boys-> NULL\n===\n";
    result = test_removeShow("Better Call Saul", build);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(5);
    
}

TEST_F(test, TestPurgeCompleteShowList)
{
    //testcase1
    string expected_array, result;
    bool build = true;
    expected_array  = "adding: Friends (HEAD)\nadding: Ozark (prev: Friends)\nadding: Stranger Things (prev: Ozark)\nadding: The Boys (prev: Stranger Things)\nadding: Better Call Saul (prev: The Boys)\n** Default list constructed **\n** Calling purgeCompleteShowList()\ndeleting: Friends\ndeleting: Ozark\ndeleting: Stranger Things\ndeleting: The Boys\ndeleting: Better Call Saul\nDeleted show list\n** Does head == NULL? (true if network was deleted): True\n";
    result = test_purgeCompleteShowList(build);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(20);   
}


TEST_F(test, TestfindGlitch)
{
    //testcase1
    string expected_array, result;
    expected_array="adding: Friends (HEAD)\nadding: Ozark (prev: Friends)\nadding: Stranger Things (prev: Ozark)\nadding: The Boys (prev: Stranger Things)\nadding: Better Call Saul (prev: The Boys)\n** Default list constructed **\n** Creating loop to Ozark\n** Calling findGlitch()\nLoop is detected\n** Breaking the loop\n** Calling displayShows()\n== CURRENT SHOWS LIST ==\nFriends-> Ozark-> Stranger Things-> The Boys-> Better Call Saul-> NULL\n===\n";
    result = test_findGlitch("Ozark", true);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(6);
    
    //testcase2 head loop
    expected_array="adding: Friends (HEAD)\nadding: Ozark (prev: Friends)\nadding: Stranger Things (prev: Ozark)\nadding: The Boys (prev: Stranger Things)\nadding: Better Call Saul (prev: The Boys)\n** Default list constructed **\n** Creating loop to Friends\n** Calling findGlitch()\nLoop is detected\n** Breaking the loop\n** Calling displayShows()\n== CURRENT SHOWS LIST ==\nFriends-> Ozark-> Stranger Things-> The Boys-> Better Call Saul-> NULL\n===\n";
    result = test_findGlitch("Friends", true);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(6);
    
    //testcase3 empty LL
    expected_array="** Creating loop to Friends\n** Calling findGlitch()\nNo loop found\n** Calling displayShows()\nnothing in path\n";
    result = test_findGlitch("Friends", false);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(6);
    
    //testcase4 unsuccessful target
    expected_array="adding: Friends (HEAD)\nadding: Ozark (prev: Friends)\nadding: Stranger Things (prev: Ozark)\nadding: The Boys (prev: Stranger Things)\nadding: Better Call Saul (prev: The Boys)\n** Default list constructed **\n** Creating loop to Manifest\n** Calling findGlitch()\nNo loop found\n** Calling displayShows()\n== CURRENT SHOWS LIST ==\nFriends-> Ozark-> Stranger Things-> The Boys-> Better Call Saul-> NULL\n===\n";
    result = test_findGlitch("Manifest", true);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(6);
    
    //testcase5 last node
    expected_array="adding: Friends (HEAD)\nadding: Ozark (prev: Friends)\nadding: Stranger Things (prev: Ozark)\nadding: The Boys (prev: Stranger Things)\nadding: Better Call Saul (prev: The Boys)\n** Default list constructed **\n** Creating loop to Better Call Saul\n** Calling findGlitch()\nLoop is detected\n** Breaking the loop\n** Calling displayShows()\n== CURRENT SHOWS LIST ==\nFriends-> Ozark-> Stranger Things-> The Boys-> Better Call Saul-> NULL\n===\n";
    result = test_findGlitch("Better Call Saul", true);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(6);
}



TEST_F(test, TestRearrangeShowList)
{
    //testcase1 take out nodes  from 1-3
    string expected_array, result;
    expected_array="adding: Friends (HEAD)\nadding: Ozark (prev: Friends)\nadding: Stranger Things (prev: Ozark)\nadding: The Boys (prev: Stranger Things)\nadding: Better Call Saul (prev: The Boys)\n** Default list constructed **\n** Shows list before rearrangement\n== CURRENT SHOWS LIST ==\nFriends-> Ozark-> Stranger Things-> The Boys-> Better Call Saul-> NULL\n===\n== After rearrangement ==\n== CURRENT SHOWS LIST ==\nFriends-> Better Call Saul-> Ozark-> Stranger Things-> The Boys-> NULL\n===\n";
    result = test_rearrangeShowList(1, 3, true);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(5);
    
    
    //testcase2 take out nodes  from 0-1
    
    expected_array="adding: Friends (HEAD)\nadding: Ozark (prev: Friends)\nadding: Stranger Things (prev: Ozark)\nadding: The Boys (prev: Stranger Things)\nadding: Better Call Saul (prev: The Boys)\n** Default list constructed **\n** Shows list before rearrangement\n== CURRENT SHOWS LIST ==\nFriends-> Ozark-> Stranger Things-> The Boys-> Better Call Saul-> NULL\n===\n== After rearrangement ==\n== CURRENT SHOWS LIST ==\nStranger Things-> The Boys-> Better Call Saul-> Friends-> Ozark-> NULL\n===\n";
    result = test_rearrangeShowList(0, 1, true);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(5);
    
    
    //testcase3 take invalid end index
    
    expected_array="adding: Friends (HEAD)\nadding: Ozark (prev: Friends)\nadding: Stranger Things (prev: Ozark)\nadding: The Boys (prev: Stranger Things)\nadding: Better Call Saul (prev: The Boys)\n** Default list constructed **\n** Shows list before rearrangement\n== CURRENT SHOWS LIST ==\nFriends-> Ozark-> Stranger Things-> The Boys-> Better Call Saul-> NULL\n===\n== After rearrangement ==\nInvalid end index\n== CURRENT SHOWS LIST ==\nFriends-> Ozark-> Stranger Things-> The Boys-> Better Call Saul-> NULL\n===\n";
    result = test_rearrangeShowList(2, 20, true);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(5);
    
    
    //testcase4 take single node
    
    expected_array="adding: Friends (HEAD)\nadding: Ozark (prev: Friends)\nadding: Stranger Things (prev: Ozark)\nadding: The Boys (prev: Stranger Things)\nadding: Better Call Saul (prev: The Boys)\n** Default list constructed **\n** Shows list before rearrangement\n== CURRENT SHOWS LIST ==\nFriends-> Ozark-> Stranger Things-> The Boys-> Better Call Saul-> NULL\n===\n== After rearrangement ==\n== CURRENT SHOWS LIST ==\nFriends-> Ozark-> The Boys-> Better Call Saul-> Stranger Things-> NULL\n===\n";
    result = test_rearrangeShowList(2, 2, true);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(5);
    
    //testcase5 invalid end index2:end index is last node
    
    expected_array="adding: Friends (HEAD)\nadding: Ozark (prev: Friends)\nadding: Stranger Things (prev: Ozark)\nadding: The Boys (prev: Stranger Things)\nadding: Better Call Saul (prev: The Boys)\n** Default list constructed **\n** Shows list before rearrangement\n== CURRENT SHOWS LIST ==\nFriends-> Ozark-> Stranger Things-> The Boys-> Better Call Saul-> NULL\n===\n== After rearrangement ==\nInvalid end index\n== CURRENT SHOWS LIST ==\nFriends-> Ozark-> Stranger Things-> The Boys-> Better Call Saul-> NULL\n===\n";
    result = test_rearrangeShowList(4, 4, true);
    ASSERT_EQ(expected_array, result);
    add_points_to_grade(5);
    
}




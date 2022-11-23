// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
// #include "../code_1/<HEADER FILE>.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include "test_helpers.hpp"

using namespace std;

class test_x : public ::testing::Test {
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

double test_x::total_grade = 0;
double test_x::max_grade = 100;







/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////
TEST_F(test_x, TestPush)
{
    string result, expected;
    char arr[] = "abcd";
    int len = 4;
    result = test_push(arr,  len);
    expected= "Print stack from top to bottom:\nd\nc\nb\na\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
}

TEST_F(test_x, TestPop)
{
    string result, expected;
    char arr[] = "abcd";
    int len = 4;
    result = test_pop(arr,  len);
    expected= "Print stack from top to bottom:\nd\nc\nb\na\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
}

TEST_F(test_x, TestPeek)
{
    string result, expected;
    char arr[] = "abcd";
    int len = 4;
    result = test_peek(arr,  len);
    expected= "Print stack from top to bottom:\nd\nc\nb\na\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
}

TEST_F(test_x, TestAll)
{
    string result, expected;
    char arr[] = "abcd";
    int len = 4;
    result = test_all(arr,  len);
    expected= "push: a\npush: b\npoping thrice \nStack empty, cannot pop an item.\npush: c\npush: d\nPrint stack from top to bottom:\nd\nc\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(8);
}


TEST_F(test_x, TestEvaluate){
    string result, expected;
    
    char s1[] = "{xyz}";
    int len1 = sizeof(s1) / sizeof(s1[0]);
    result = test_evaluate(s1,len1);
    expected= "zyx";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);
    
    char s2[] = "Lets watch {krazO} today";
    int len2 = sizeof(s2) / sizeof(s2[0]);
    result = test_evaluate(s2,len2);
    expected = "Ozark";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);
    
    char s3[] = "The show we are waiting for is {sdneirF}";
    int len3 = sizeof(s3) / sizeof(s3[0]);;
    result = test_evaluate(s3,len3);
    expected = "Friends";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);
    
    char s4[] = "I reaally love {sgnihT regnartS ehT}";
    int len4 = sizeof(s4) / sizeof(s4[0]);;
    result = test_evaluate(s4,len4);
    expected = "The Stranger Things";
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);
    
    char s5[] = "I can easily repeat {ylimaF nredoM ehT}";
    int len5 = sizeof(s5) / sizeof(s5[0]);;
    result = test_evaluate(s5,len5);
    expected = "The Modern Family";
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);

    char s6[] = "Is this really a show {Not a show";
    int len6 = sizeof(s6) / sizeof(s6[0]);;
    result = test_evaluate(s6,len6);
    expected = "No secret message\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);

}

TEST_F(test_x, TestStackCalMain)
{
    string desired = "Enter the encoded sentence\n#>Ozark";
    string resp = exec("./run_app_1 ../tests/stack_cal_main/input1.txt");
    ASSERT_EQ(desired, resp);
    add_points_to_grade(1);

    desired = "Enter the encoded sentence\n#>Nothing to evaluate";
    resp = exec("./run_app_1 ../tests/stack_cal_main/input2.txt");
    ASSERT_EQ(desired, resp);
    add_points_to_grade(1);

    desired = "Enter the encoded sentence\n#>No secret message\n";
    resp = exec("./run_app_1 ../tests/stack_cal_main/input3.txt");
    ASSERT_EQ(desired, resp);
    add_points_to_grade(1);

}

// queue testing
TEST_F(test_x, TestConsQ)
{
    string result, expected;
    result = test_consQ();
    expected = "Correct!\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
}

TEST_F(test_x, TestEnQ)
{
    string result, expected;
    
    int len = 4;
    result = test_enQ("show",  len);
    expected= "Print queue from front to back:\nshow0\nshow1\nshow2\nshow3\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
    
    len = 21;
    result = test_enQ("show",  len);
    expected= "Queue full, cannot add a new show\nPrint queue from front to back:\nshow0\nshow1\nshow2\nshow3\nshow4\nshow5\nshow6\nshow7\nshow8\nshow9\nshow10\nshow11\nshow12\nshow13\nshow14\nshow15\nshow16\nshow17\nshow18\nshow19\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
}

TEST_F(test_x, TestDeQ)
{
    string result, expected;
    
    int len = 4;
    result = test_deQ("show",  len, 3);
    expected= "dequeuing 3 times\nPrint queue from front to back:\nshow3\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
    
    
    len = 4;
    result = test_deQ("show", len, 5);
    expected= "dequeuing 5 times\nQueue empty, cannot dequeue show\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
}

TEST_F(test_x, TestPeekQ)
{
    string result, expected;
    
    int len = 0;
    int dq = 0;
    result = test_peekQ("show",  len, dq);
    expected= "enqueuing 0 elements\ndequeuing 0 times\npeeking in the queue\nQueue empty, cannot peek\n\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
    
    
    len = 4;
    result = test_peekQ("show",  len, 3);
    expected= "enqueuing 4 elements\ndequeuing 3 times\npeeking in the queue\nFront of the queue: show3\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
    
    len = 4;
    result = test_peekQ("show",  len, 5);
    expected= "enqueuing 4 elements\ndequeuing 5 times\nQueue empty, cannot dequeue show\npeeking in the queue\nQueue empty, cannot peek\n\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
}

TEST_F(test_x, TestAllQ)
{
    //enQ2 deQ2
    string result, expected;
    string seq1[] = {"E","E","D","D", "P"};
    int len1 = 5;
    result = test_allQ("show",seq1, len1);
    expected = "Enqueue(show0)\nEnqueue(show1)\nDequeue\nDequeue\nPeek\nQueue empty, cannot peek\n\nQueue is full? false\nQueue is empty? true\nQueue size: 0\nQueue front index: -1\nQueue back index: -1\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
    
    //enQ20 deQ10 enQ7
    string seq2[] = {"E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","D","D","D","D","D","D","D","D","D","D","E","E","E","E","E","E","E"};
    int len2 = 37;
    result = test_allQ("show", seq2, len2);
    expected = "Enqueue(show0)\nEnqueue(show1)\nEnqueue(show2)\nEnqueue(show3)\nEnqueue(show4)\nEnqueue(show5)\nEnqueue(show6)\nEnqueue(show7)\nEnqueue(show8)\nEnqueue(show9)\nEnqueue(show10)\nEnqueue(show11)\nEnqueue(show12)\nEnqueue(show13)\nEnqueue(show14)\nEnqueue(show15)\nEnqueue(show16)\nEnqueue(show17)\nEnqueue(show18)\nEnqueue(show19)\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nEnqueue(show20)\nEnqueue(show21)\nEnqueue(show22)\nEnqueue(show23)\nEnqueue(show24)\nEnqueue(show25)\nEnqueue(show26)\nQueue is full? false\nQueue is empty? false\nQueue size: 17\nQueue front index: 10\nQueue back index: 6\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
    
     //enQ20 deQ10 enQ10
    string seq3[] = {"E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","D","D","D","D","D","D","D","D","D","D","E","E","E","E","E","E","E","E","E","E"};
    int len3 = 40;
    result = test_allQ("show",seq3, len3);
    expected = "Enqueue(show0)\nEnqueue(show1)\nEnqueue(show2)\nEnqueue(show3)\nEnqueue(show4)\nEnqueue(show5)\nEnqueue(show6)\nEnqueue(show7)\nEnqueue(show8)\nEnqueue(show9)\nEnqueue(show10)\nEnqueue(show11)\nEnqueue(show12)\nEnqueue(show13)\nEnqueue(show14)\nEnqueue(show15)\nEnqueue(show16)\nEnqueue(show17)\nEnqueue(show18)\nEnqueue(show19)\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nEnqueue(show20)\nEnqueue(show21)\nEnqueue(show22)\nEnqueue(show23)\nEnqueue(show24)\nEnqueue(show25)\nEnqueue(show26)\nEnqueue(show27)\nEnqueue(show28)\nEnqueue(show29)\nQueue is full? true\nQueue is empty? false\nQueue size: 20\nQueue front index: 10\nQueue back index: 9\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
    
    //enQ20 deQ10 enQ10 deQ20
    string seq4[] = {"E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","D","D","D","D","D","D","D","D","D","D","E","E","E","E","E","E","E","E","E","E","D","D","D","D","D","D","D","D","D","D","D","D","D","D","D","D","D","D","D","D"};
    int len4 = 60;
    result = test_allQ("show",seq4, len4);
    expected = "Enqueue(show0)\nEnqueue(show1)\nEnqueue(show2)\nEnqueue(show3)\nEnqueue(show4)\nEnqueue(show5)\nEnqueue(show6)\nEnqueue(show7)\nEnqueue(show8)\nEnqueue(show9)\nEnqueue(show10)\nEnqueue(show11)\nEnqueue(show12)\nEnqueue(show13)\nEnqueue(show14)\nEnqueue(show15)\nEnqueue(show16)\nEnqueue(show17)\nEnqueue(show18)\nEnqueue(show19)\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nEnqueue(show20)\nEnqueue(show21)\nEnqueue(show22)\nEnqueue(show23)\nEnqueue(show24)\nEnqueue(show25)\nEnqueue(show26)\nEnqueue(show27)\nEnqueue(show28)\nEnqueue(show29)\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nQueue is full? false\nQueue is empty? true\nQueue size: 0\nQueue front index: -1\nQueue back index: -1\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
    
    
     //enQ20 deQ9 enQ4 deQ7
    string seq5[] = {"E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","D","D","D","D","D","D","D","D","D","E","E","E","E","D","D","D","D","D","D","D"};
    int len5 = 40;
    result = test_allQ("show",seq5, len5);
    expected = "Enqueue(show0)\nEnqueue(show1)\nEnqueue(show2)\nEnqueue(show3)\nEnqueue(show4)\nEnqueue(show5)\nEnqueue(show6)\nEnqueue(show7)\nEnqueue(show8)\nEnqueue(show9)\nEnqueue(show10)\nEnqueue(show11)\nEnqueue(show12)\nEnqueue(show13)\nEnqueue(show14)\nEnqueue(show15)\nEnqueue(show16)\nEnqueue(show17)\nEnqueue(show18)\nEnqueue(show19)\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nEnqueue(show20)\nEnqueue(show21)\nEnqueue(show22)\nEnqueue(show23)\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nQueue is full? false\nQueue is empty? false\nQueue size: 8\nQueue front index: 16\nQueue back index: 3\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);
       
}

TEST_F(test_x, TestMainQ)
{
    string desired;
    string resp;
    desired = readFileIntoString("../tests/queue_main/output1.txt");
    resp = exec("./run_app_2 ../tests/queue_main/input1.txt");
    ASSERT_EQ(desired, resp);
    add_points_to_grade(3.75);
    
    desired = readFileIntoString("../tests/queue_main/output2.txt");
    resp = exec("./run_app_2 ../tests/queue_main/input2.txt");
    ASSERT_EQ(desired, resp);
    add_points_to_grade(3.75);
    
    desired = readFileIntoString("../tests/queue_main/output3.txt");
    resp = exec("./run_app_2 ../tests/queue_main/input3.txt");
    ASSERT_EQ(desired, resp);
    add_points_to_grade(3.75);
    
    desired = readFileIntoString("../tests/queue_main/output4.txt");
    resp = exec("./run_app_2 ../tests/queue_main/input4.txt");
    ASSERT_EQ(desired, resp);
    add_points_to_grade(3.75);
}
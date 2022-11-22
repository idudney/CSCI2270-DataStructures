// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code_1/fundamentals_1.hpp"
#include "../code_2/fundamentals_2.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>

#define EPSILON 10e-6

using namespace std;

class test_fundamentals : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)0;
			outgrade.close();
		}

    // Clean up to ensure old output files are not present
    remove("../out_2_1.csv");
    remove("../out_2_2.csv");
    remove("../out_2_3.csv");
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

double test_fundamentals::total_grade = 0;
double test_fundamentals::max_grade = 100;

/////////////////////////////////////////
// Test Helper Functions
/////////////////////////////////////////

string desired_result("20\n-189,20\n-189,20,34.5\n-189,13,20,34.5\n-189,13,20,34.5,1009\n-189,12,13,20,34.5,1009\n-189,12,12.4,13,20,34.5,1009\n-189,12,12.4,12.5,13,20,34.5,1009\n-189,-9,12,12.4,12.5,13,20,34.5,1009\n");

bool compare_arrays(float a[], float b[], int size){
  bool pass = true;
  for(int i = 0; i<size; ++i){
    if(a[i] != b[i]){
      pass = false;
      cout << "Actual Output: " << a[i] << "\nExpected Output: " << b[i] << endl;
    }
  }
  return pass;
}

bool compare_structs(emissionInfo &a, emissionInfo &b){
  bool pass = false;
  if(a.countryName == b.countryName 
    && a.emission_in_2015 == b.emission_in_2015 
    && a.emission_in_2016 == b.emission_in_2016 
    && a.emission_in_2017 == b.emission_in_2017
    && a.emission_in_2018 == b.emission_in_2018
    && a.emission_in_2019 == b.emission_in_2019
    && a.average == b.average
  ){
    pass = true;
  }
  else{
    cout << "The actual and the expected emissionInfo structs are not the same." << endl;
  }
  return pass;
}

bool isFloatingPointNumber(string s) {
  int sz = s.size(), digCount = 0;
  bool dot = false;

  for (int i = 0; i < (int) s.size(); i++) {
    if (isdigit(s[i])) digCount++;
    else {
      if (s[i] == '.') dot = true;
    }
  }
  bool ans = digCount == (sz - 1) && dot == true;
  return ans;
}

bool compareFloats(double a, double b) {
  bool ans = abs(a - b) <= EPSILON;
  return ans;
}

bool sameFloatingPointNumbers(string a, string b) {
  bool same = isFloatingPointNumber(a) && isFloatingPointNumber(b) && compareFloats(stod(a), stod(b));
  return same;
}

vector <string> split (string s, char ch) {
  vector <string> tmp; string w = "";
  for (int i = 0; i < (int) s.size(); i++) {
    if (s[i] == ch) {
	tmp.push_back(w);
	w = "";
    } else {
	w += s[i];
    }
  }
  tmp.push_back(w);
  return tmp;
}

bool sameLineWithFloats (string a, string b) {
  vector <string> la = split(a, ',');
  vector <string> lb = split(b, ','); 

  int sza = la.size(), szb = lb.size();
  if (sza != szb) return false;

  for (int i = 0; i < sza; i++) {
    if (isFloatingPointNumber(la[i])) {
      if (!isFloatingPointNumber(lb[i]) || !sameFloatingPointNumbers(la[i], lb[i])) {
        return false;
      }
    } else {
      if (la[i] != lb[i]) return false;
    }
  }
  return true;
}

bool compare_files(string fileA, string fileB){
  std::string lineA, lineB;
  ifstream A, B;
  A.open(fileA);
  if(!A){throw std::runtime_error("could not open file: " + fileA);}
  B.open(fileB);
  if(!B){throw std::runtime_error("could not open file: " + fileB);}

  bool pass = true;
  while(getline(A,lineA) && getline(B,lineB)){
    if(lineA!=lineB && !sameLineWithFloats(lineA, lineB)){
      pass = false;
      cout << "Actual Output: " << lineA << "\nExpected Output: " << lineB << endl;
    }
  }
  return pass;
}

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

/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////

///////////////////
// Part 1
//////////////////

// Test the addToArrayAsc function [10 POINTS]
TEST_F(test_fundamentals, TestAddToArrayAsc){

  // Create a sample test array
  const int listsize=6;
  float l[listsize] = {29.5, 44.0 ,35.1 ,16.2, 9,200.4};
  float myArray[100];
  int sizeArray = 0;

  // After a single insert, the array size should be 1
  sizeArray = addToArrayAsc(myArray,sizeArray,l[0]);
  ASSERT_EQ(1,sizeArray);
  add_points_to_grade(1.43);

  // Check if after a single insert the correct element is contained within the array
  float array_A[] = {29.5};
  bool same = compare_arrays(myArray, array_A, sizeArray);
  ASSERT_TRUE(same);
  add_points_to_grade(1.43);

  // Insert another element, check for correct array orientation
  float array_B[] = {29.5,44};
  sizeArray = addToArrayAsc(myArray,sizeArray,l[1]);
  same = compare_arrays(myArray, array_B, sizeArray);
  ASSERT_TRUE(same);
  add_points_to_grade(1.43);

  // Insert another element, check for correct array orientation
  float array_C[] = {29.5,35.1,44};
  sizeArray = addToArrayAsc(myArray,sizeArray,l[2]);
  same = compare_arrays(myArray, array_C, sizeArray);
  ASSERT_TRUE(same);
  add_points_to_grade(1.43);

  // Insert another element, check for correct array orientation
  float array_D[] = {16.2,29.5,35.1,44};
  sizeArray = addToArrayAsc(myArray,sizeArray,l[3]);
  same = compare_arrays(myArray, array_D, sizeArray);
  ASSERT_TRUE(same);
  add_points_to_grade(1.43);

  // Insert another element, check for correct array orientation
  float array_E[] = {9,16.2,29.5,35.1,44};
  sizeArray = addToArrayAsc(myArray,sizeArray,l[4]);
  same = compare_arrays(myArray, array_E, sizeArray);
  ASSERT_TRUE(same);
  add_points_to_grade(1.43);
  
  // Insert another element, check for correct array orientation
  float array_F[] = {9,16.2,29.5,35.1,44,200.4};
  sizeArray = addToArrayAsc(myArray,sizeArray,l[5]);
  same = compare_arrays(myArray, array_F, sizeArray);
  ASSERT_TRUE(same);
  add_points_to_grade(1.43);

}

// Test the entire application program. Test that data file name
// passed in via command line can be read in, and that the
// addToArrayAsc function works within the context of the program.
// [35 POINTS]

TEST_F(test_fundamentals, TestApp_1){
  string resp = exec("./run_app_1 ../unsorted_numbers.txt");
  ASSERT_EQ(resp,desired_result);
  add_points_to_grade(35);
}

///////////////////
// Part 2
//////////////////

// Test the insertEmissionInfo function [10 POINTS]
TEST_F(test_fundamentals, TestInsertEmissionInfo){

  // Check if adding a single element correctly writes a 
  // struct within the array of structs

  emissionInfo emissions[10];
  insertEmissionInfo(emissions, "India", 10.0,10.0,10.0,10.0,10.0,0); 

  emissionInfo e;
  e.countryName = "India";
  e.emission_in_2015 = 10.0;
  e.emission_in_2016 = 10.0;
  e.emission_in_2017 = 10.0;
  e.emission_in_2018 = 10.0;
  e.emission_in_2019 = 10.0;
  e.average = 10.0;
  bool same = compare_structs(emissions[0], e);
  ASSERT_TRUE(same);
  add_points_to_grade(4);

  // Write 3 more records to the array of structs
  // Ensure that overall averages are being calculated correctly
  int idx = 0;
  insertEmissionInfo(emissions, "USA", 11.0,11.0,11.0,11.0,11.0,idx++);
  insertEmissionInfo(emissions, "Canada", 12.0,12.0,12.0,12.0,12.0,idx++);
  insertEmissionInfo(emissions, "Mexico", 13.0,13.0,13.0,13.0,13.0,idx++);
  same = false;
  double averages [] = {11.0, 12.0, 13.0};
  for (int i = 0; i < idx; i++) {
    ASSERT_EQ(emissions[i].average, averages[i]);
    add_points_to_grade(2);
  }
}


// Test the calcLetterGrade function [5 POINTS]
TEST_F(test_fundamentals, TestCalcEmissionZone){
  double averages [] = {2.0, 10.0, 6.0};

  ASSERT_EQ("GREEN",calcEmissionZone(averages[0]));
  add_points_to_grade(1.66);

  ASSERT_EQ("RED",calcEmissionZone(averages[1]));
  add_points_to_grade(1.66);

  ASSERT_EQ("ORANGE",calcEmissionZone(averages[2]));
  add_points_to_grade(1.66);

}


string desired_result_2_1("Czech Republic,9.43098,ORANGE\nKazakhstan,11.4874,RED\nKorea,12.0329,RED\nRussian Federation,11.2537,RED\n");
string desired_result_2_2("");
string desired_result_2_3("Cuba,2.38645,GREEN\nEgypt,2.48211,GREEN\nGeorgia,2.59083,YELLOW\nTunisia,2.62163,YELLOW\n");


// Test the entire program [40 POINTS]
// The program should print the results to both standard output and to a csv file
// - each case tests for both. 
TEST_F(test_fundamentals, TestApp_2){
  string resp_2_1 = exec("./run_app_2 ../co2_emission.csv ../out_2_1.csv 9.0 12.5");
  ASSERT_EQ(resp_2_1,desired_result_2_1);
  add_points_to_grade(6);
  bool same = compare_files("../out_2_1.csv","../tests/expected_2_1.csv");
  ASSERT_TRUE(same);
  add_points_to_grade(8);

  string resp_2_2 = exec("./run_app_2 ../co2_emission.csv ../out_2_2.csv 10.0 0.5");
  ASSERT_EQ(resp_2_2,desired_result_2_2);
  add_points_to_grade(6);
  same = compare_files("../out_2_2.csv","../tests/expected_2_2.csv");
  ASSERT_TRUE(same);
  add_points_to_grade(7);

  string resp_2_3 = exec("./run_app_2 ../co2_emission.csv ../out_2_3.csv 2.3 2.65");
  ASSERT_EQ(resp_2_3,desired_result_2_3);
  add_points_to_grade(6);
  same = compare_files("../out_2_3.csv","../tests/expected_2_3.csv");
  ASSERT_TRUE(same);
  add_points_to_grade(7);

}

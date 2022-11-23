// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code_1/array_double.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include <iomanip>

using namespace std;

class test_arrayDouble : public ::testing::Test {
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

double test_arrayDouble::total_grade = 0;
double test_arrayDouble::max_grade = 100;

/////////////////////////////////////////
// Test Helper Functions
/////////////////////////////////////////

bool compare_arrays(string a[], string b[], int size){
  bool pass = true;
  for(int i = 0; i<size; ++i){
    if(a[i] != b[i])
      pass = false;
  }
  return pass;
}

void compare_arrays_structs(movieRecord a[], movieRecord b[], int size){
  for(int i = 0; i<size; ++i){
	  ASSERT_EQ(a[i].movieCount, b[i].movieCount) << "Array differs at index i=" << i;
	  ASSERT_EQ(a[i].movieName, b[i].movieName) << "Array differs at index i=" << i;
  }
  return;
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

void genStructArray(movieRecord *& structArray, string stringArray[], int counts[], float averages[], int l){
	for(int i = 0; i<l; i++){
		movieRecord newstruct = movieRecord();
		newstruct.movieName = stringArray[i];
		newstruct.movieCount = counts[i];
		newstruct.avgUserRating = averages[i];
		structArray[i] = newstruct;
	}
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

// Test arrays
string array_A_sorted[] = {"The Foreigner","Tropic Thunder","Tropic Thunder", "Cinderella"}; 
string array_B_sorted[] = {"The Foreigner", "Collide","Justice League","Tropic Thunder","Tropic Thunder","Scooby-Doo",
"Tron",
"Cinderella",
"The Foreigner",
"Borat",
"Tropic Thunder",
"The Odyssey",	
"Inchon" };
int testArrLength_A = 4;
int testArrLength_B = 13;
int array_A_counts_sorted[] = {3, 8, 9, 7};
int array_B_counts_sorted[] = {2, 9, 7, 2, 5, 3, 7, 1, 9, 9, 3, 2, 1};
string array_A[] = {"Cinderella","Tropic Thunder", "The Foreigner", "Tropic Thunder"}; 
string array_B[] = {"Cinderella","Tropic Thunder", "The Foreigner", "Tropic Thunder","Tron","Scooby-Doo",
"Justice League",
"Collide",	
"Inchon",
"The Odyssey",	
"Tropic Thunder",
"The Foreigner",
"Borat" };
int array_A_counts[] = {7, 9, 3, 8};
int array_B_counts[] = {1, 5, 2, 2, 7, 3, 7, 9, 1, 2, 3, 9, 9};
float array_A_averages[] = {0.67, 0.78, 0.99, 0.8};
float array_B_averages[] = {0.67, 0.78, 0.99, 0.8, 0.69, 0.75, 0.8, 0.91, 0.2, 0.3, 0.5,0.66, 0.53};
string array_A_print = "Movie Ratings\n---------------------------------------\n0.670 The Foreigner\n0.780 Tropic Thunder\n0.990 Tropic Thunder\n0.800 Cinderella\n";
string array_B_print = "Movie Ratings\n---------------------------------------\n0.670 The Foreigner\n0.780 Collide\n0.990 Justice League\n0.800 Tropic Thunder\n0.690 Tropic Thunder\n0.750 Scooby-Doo\n0.800 Tron\n0.910 Cinderella\n0.200 The Foreigner\n0.300 Borat\n0.500 Tropic Thunder\n0.660 The Odyssey\n0.530 Inchon\n";

// Test the isIgnoreWord() function [8 POINTS]
TEST_F(test_arrayDouble, TestCheckMovieToBeIncluded){
	// test case 1: check for PG-13
	bool isValid;
	string movieRatings[5] = {
		"P","G","PG","R","PG-13"
	};
	string rating = "PG-13";
	isValid = checkMovieToBeIncluded(movieRatings[4], rating);
	ASSERT_EQ(false, isValid);
	add_points_to_grade(4);

	isValid = checkMovieToBeIncluded(movieRatings[0], rating);
	ASSERT_EQ(true, isValid);
	add_points_to_grade(4);
}

// Test the getTotalNumberOfIgnoreWords() function [20 POINTS]
TEST_F(test_arrayDouble, TestGetTotalMovies){
	// Generate an array of structs
	movieRecord* testArr_A = new movieRecord[testArrLength_A];
	genStructArray(testArr_A, array_A, array_A_counts, array_A_averages, testArrLength_A);
	// Test the function:
	int testA = getTotalMoviesCount(testArr_A, testArrLength_A);
	ASSERT_EQ(testA, 27);
	add_points_to_grade(10);

	delete[] testArr_A;

	// Generate an array of structs
	movieRecord* testArr_B = new movieRecord[testArrLength_B];
	genStructArray(testArr_B, array_B, array_B_counts, array_B_averages, testArrLength_B);
	// Test the function:
	int testB = getTotalMoviesCount(testArr_B, testArrLength_B);
	ASSERT_EQ(testB, 60);
	add_points_to_grade(10);

	delete[] testArr_B;
}

// Test the sortArray() function [16 POINTS]
TEST_F(test_arrayDouble, TestSortArray){
	// Generate an unsorted array of structs:
	movieRecord* testArr_A = new movieRecord[testArrLength_A];
	genStructArray(testArr_A, array_A, array_A_counts, array_A_averages, testArrLength_A);
	// Sort the array to test if sortArray() is working
	sortArray(testArr_A,testArrLength_A);
	// Generate the correctly sorted array of structs:
	movieRecord* sortedArrayOfStructs_A = new movieRecord[testArrLength_A];
	genStructArray(sortedArrayOfStructs_A, array_A_sorted, array_A_counts_sorted, array_A_averages, testArrLength_A);
	// Compare the two arrays:
	ASSERT_EQ(sizeof(testArr_A), sizeof(sortedArrayOfStructs_A)) << "Array has incorrect length";
	compare_arrays_structs(testArr_A, sortedArrayOfStructs_A, testArrLength_A);
	add_points_to_grade(8);
	delete[] testArr_A;
	delete[] sortedArrayOfStructs_A;

	// Generate an unsorted array of structs:
	movieRecord* testArr_B = new movieRecord[testArrLength_B];
	genStructArray(testArr_B, array_B, array_B_counts, array_B_averages, testArrLength_B);
	// Sort the array to test if sortArray() is working
	sortArray(testArr_B,testArrLength_B);		
	// Generate the correctly sorted array of structs:
	movieRecord* sortedArrayOfStructs_B = new movieRecord[testArrLength_B];
	genStructArray(sortedArrayOfStructs_B, array_B_sorted, array_B_counts_sorted, array_B_averages, testArrLength_B);
	// // Compare the two arrays:
	ASSERT_EQ(sizeof(testArr_B), sizeof(sortedArrayOfStructs_B)) << "Array has incorrect length";
	compare_arrays_structs(testArr_B, sortedArrayOfStructs_B, testArrLength_B);
	add_points_to_grade(8);
	delete[] testArr_B;
	delete[] sortedArrayOfStructs_B;
}

//Test the doubleArray function [3 POINTS]
TEST_F(test_arrayDouble, TestPrintTopNMovies){
	// Generate the correctly sorted array of structs:
	movieRecord* sortedArrayOfStructs_A = new movieRecord[testArrLength_A];
	genStructArray(sortedArrayOfStructs_A, array_A_sorted, array_A_counts_sorted, array_A_averages, testArrLength_A);
	// Use the following to redirect the standard output
	testing::internal::CaptureStdout();
	// Call the function
	printTopNMovies(sortedArrayOfStructs_A, testArrLength_A);
	// Record the functions std output to a sting variable
	string output = testing::internal::GetCapturedStdout();
	ASSERT_EQ(output, array_A_print);
	add_points_to_grade(1.5);

	// Generate the correctly sorted array of structs:
	movieRecord* sortedArrayOfStructs_B = new movieRecord[testArrLength_B];
	genStructArray(sortedArrayOfStructs_B, array_B_sorted, array_B_counts_sorted, array_B_averages, testArrLength_B);
	// Use the following to redirect the standard output
	testing::internal::CaptureStdout();
	// Call the function
	printTopNMovies(sortedArrayOfStructs_B, testArrLength_B);
	// Record the functions std output to a sting variable
	output = testing::internal::GetCapturedStdout();
	ASSERT_EQ(output, array_B_print);
	add_points_to_grade(1.5);
}

//Test the printeTenFromN() function [3 POINTS]
TEST_F(test_arrayDouble, TestDoubleArray){
	// Generate an unsorted array of structs:
	movieRecord* testArr_A = new movieRecord[testArrLength_A];
	genStructArray(testArr_A, array_A, array_A_counts, array_A_averages, testArrLength_A);
	int initialArrCapacity_A = testArrLength_A;
	//double the array
	doubleArray(testArr_A, testArrLength_A);
	// Compare the array length:
	ASSERT_EQ(testArrLength_A, initialArrCapacity_A * 2) << "Array has incorrect length";
	add_points_to_grade(1.5);
	delete[] testArr_A;

	movieRecord* testArr_B = new movieRecord[testArrLength_B];
	genStructArray(testArr_B, array_B, array_B_counts, array_B_averages, testArrLength_B);
	int initialArrCapacity_B = testArrLength_B;
	//double the array
	doubleArray(testArr_B, testArrLength_B);
	// Compare the array length:
	ASSERT_EQ(testArrLength_B, initialArrCapacity_B * 2) << "Array has incorrect length";
	add_points_to_grade(1.5);
	delete[] testArr_B;
}

// Test the entire program [50 POINTS]
TEST_F(test_arrayDouble, TestApp_1){
	string desired = readFileIntoString("../tests/expected_1_1.txt");
	string resp = exec("./run_app_1 ../tests/movies_1.txt PG-13 3");
	ASSERT_EQ(desired, resp);
  	add_points_to_grade(12.5);

	desired = readFileIntoString("../tests/expected_1_2.txt");
	resp = exec("./run_app_1 ../tests/movies_2.txt R 5");
	ASSERT_EQ(desired, resp);
  	add_points_to_grade(12.5);

	desired = readFileIntoString("../tests/expected_1_3.txt");
	resp = exec("./run_app_1 ../tests/movies_3.txt G 5");
	ASSERT_EQ(desired, resp);
  	add_points_to_grade(12.5);

	desired = readFileIntoString("../tests/expected_1_4.txt");
	resp = exec("./run_app_1 ../tests/movies_4.txt NC-17 5");
	ASSERT_EQ(desired, resp);
  	add_points_to_grade(12.5);
}

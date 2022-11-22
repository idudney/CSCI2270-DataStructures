# CSCI 2270 – Data Structures - Assignment 1: C++ Fundamentals 

## Objectives

1. Read-in command line arguments
2. Read a file
3. Loop through an array
4. Split a string
5. Create an array of struct types
6. Read and Write to a file

## Instructions

Write code to complete Parts 1 and 2. Implement the solution for each part as a separate program. To receive credit for your code, you will need to pass the necessary test cases. Use the following steps to test your code as you work on the assignment:

 1. Open up your Linux terminal, navigate to the build directory of this assignment (e.g. `cd build`).
 2. Run the `cmake ..` command.
 2. Run the `make` command.
 3. If there are no compilation errors, three executables will be generated within the build directory: `run_app_1`, `run_app_2`, and `run_tests`.
 4. If you would like to run your program including your app implementation in the `main` function, execute `run_app_1` from the terminal by typing `./run_app_1 ../unsorted_numbers.txt`. Similarly, you can execute `run_app_2` with the correct command line arguments.
 5. To run the grading tests, execute `run_tests` from the terminal by typing `./run_tests`. 

 *For Part 2 of the assignment, substitute ./run_app_2 for ./run_app_1 and follow the same steps.*

## Part 1 - Reading From a File Into a Sorted Array

**Overview:** Write a program that reads up to 100 numbers from a file. As you read the numbers, insert them into an array in ascending order.

 **For Part 1, your task is to implement the functions in `code_1\fundamentals_1.cpp` with the associated function prototypes located in `code_1\fundamentals_1.hpp`. The `main` function is defined in `app_1\main_1.cpp`.** You are encouraged to use `main_1.cpp` to test your functions as you implement them. 

### Part 1-A

Implement a function called `addToArrayAsc` that does the following:

* Takes in three arguments: 
    * `sortedArray[ ]` : sorted array that should be able to hold at most 100 floats
    * `numElements` : the number of elements inserted so far.
    * `newValue` : the incoming float value to be inserted into the sortedArray.
* Inserts `newValue` into `sortedArray` such that the  array is ordered in ascending order.
* Returns an integer containing the count of the elements inserted so far (i.e. the current size of the array).

The function header will appear as follows:
```
int addToArrayAsc(float sortedArray[], int numElements, float newValue);
```
**Note:** You are not permitted to use any library functions (i.e. `sort` from the `<algorithm>` library)

### Part 1-B
In this section you will write a complete program in `app_1\main_1.cpp`:
* Read a test file: Your program should take a single command line argument containing the name of the test data file.
    * Assume that the file is stored in the same directory as your program.
    * Open the file: 
        * If there is an error in opening the file, use the following error message and terminate execution, `std::cout << “Failed to open the file.” << std::endl;`
    * Your program can expect the file to contain up to 100 numbers on separate lines. For testing you can use the provided file named “unsorted_numbers.txt”, or create your own if you prefer.
    * Create an array of floats to store at most 100 floats.
    * Use the `getline` function to read the numbers one at a time. 
    * Store these numbers in a sorted array by passing them to the `addToArrayAsc` function (use your implementation from Part 1-A).
    * Each time a new number is read, print out the entire array after insertion, as shown in the example below.

| Input FileContents: arr.txt | Desired Output: |
|:--------------------------- |-----------------|
| 1                           | 1               |
| 6                           | 1,6             |
| 2                           | 1,2,6           |
| 12                          | 1,2,6,12        |
| 5                           | 1,2,5,6,12      |

## Part 2 - Working With an Array-of-Structs
**Overview**: For Part 2 of the assignment, you will be working with an external file again. You are expected to read from the file, be able to store and manipulate the data read from the file and write data to the standard output as well as the external file.

The function prototypes have been declared in `code_2\fundamentals_2.hpp`. Based on the instructions provided below, implement the required functions in `code_2\fundamentals_2.cpp`. As you write your code for each of the functions, you may use the `main` function in `app_2\main_2.cpp` to test the functions that you have implemented.

### Specifications

Your program will accomplish the following:

1. Read a `csv` file with up to 119 rows and 6 columns containing data on CO2 Emissions of various countries between the years 2015 and 2019.
2. Store the data from `co2_emission.csv` and average emission of each country in an array-of-structs.
3. Determine the zone (GREEN / YELLOW / ORANGE / RED) that a country belongs to based on the value of their average emission (with GREEN zone having minimum emissions and RED having the maximum).
4. Write out the country name, average CO2 emission, and zone to `output.csv` and the standard output.


Create an array that holds the `emissionInfo` struct objects. Use the following struct declaration:

    struct emissionInfo { 
        string countryName; 
        int emission_in_2015;
        int emission_in_2016; 
        int emission_in_2017;
        int emission_in_2018;
        int emission_in_2019;
        double average; 
    };

### Part 2-A
Write a function named `insertEmissionInfo`:
* The `insertEmissionInfo` function has the following declaration:
    ```
    void insertEmissionInfo(emissionInfo co2_emissions[], string countryName, int emission_in_2015, int emission_in_2016, int emission_in_2017, int emission_in_2018, int emission_in_2019, int length); 
    ```
* `co2_emissions[]` is an array-of-structs of type `emissionInfo`.
* `length` is the number of items currently stored in the array `co2_emissions[]`.
* Within the function, instantiate a local `emissionInfo` struct and store the `countryName`, `emission_in_2015`, `emission_in_2016`, `emission_in_2017`, `emission_in_2018` and `emission_in_2019` values.
* Take the average of all the emissions from the year 2015 to 2019 for each respective country and store it in the struct.
    * `co2_emissions[index].average = (emission_in_2015 + emission_in_2016 + emission_in_2017 + emission_in_2018 + emission_in_2019) / 5 ;`
* Add the struct to the co2_emissions array.

### Part 2-B
Write a function named `calcEmissionZone`:
* The `calcEmissionZone` function has the following declaration:
    ```
    string calcEmissionZone(double average); 
    ```

* Write IF-ELSE conditions to assign emission zones to each country based on their average CO2 emission using the following metrics

    | | |
    |-----|----|
    | greater than 10.0 (inclusive) | RED |
    | 5.0 (inclusive) to 10.0 (exclusive) | ORANGE |
    | 2.5 (inclusive) to 5.0 (exclusive) | YELLOW |
    | less than 2.5 (exclusive) | GREEN |
    
* Return the emission zone.

### Part 2-C

Write a complete program which includes the following: 
1. The struct and functions listed above.
2. A `main()` function defined as below:
    1. Expect four command line arguments
        1. the name of the input “.csv” file
        2. the name of the output “.csv” file
        3. a lower bound for average emission
        4. an upper bound for average emission
    2. Expect the input and output files to be stored in the same directory as your executable. Or else give proper path for files in command line arguments.
    3. Read from the input file, `co2_emission.csv`:
        * Each line can be read and decomposed using any of the following: 
            * `getline` function with the optional delimiter character.
            * `stringstream` object
        * Following the decomposition, convert each entry into its appropriate data type. Keep in mind that you must use the exact data types that are specified in the struct. (HINT: If needed, use `stod`, `stof` functions to convert from string to numerical types)
        * Call `insertEmissionInfo` function to update the co2_emissions array.
    4. Writing out to external files in C++ can be done very similarly as reading in. Instead of using an object of the `ifstream` class, as is done with input streams, use an object of the `ofstream` class. `csv` stands for comma separated values. Write to an output “.csv” file:
        * Write the `<country_name>,<emission_average>,<emission_zone>` (as shown in the sample output) of the countries whose `<emission_average>` is >= `lower_bound` and `<emission_average> <= upper_bound` to the output `.csv` file. Here, `lower_bound` and `upper_bound` represent the average emission values passed as command-line arguments to the program.
        * Do not sort the data while writing to the output file. The relative order will be the same as the input file. Only those countries with average emission within the bounds should be written to the output file.
    5. Make sure your program closes the output file when it is finished writing.

### Sample Input and Output:
Assuming that the input file, `co2_emission.csv` has the following content:
```
United States, 15.560, 15.149, 14.823, 15.223, 14.673 
Itay, 5.563, 5.498, 5.438, 5.377, 5.311
India, 1.647, 1.657, 1.733, 1.813, 1.798
Japan, 9.277, 9.189, 9.098, 8.801, 8.541
Qatar, 33.044, 32.746, 32.128, 31.068, 32.474
```
Running your program using the command: 
`./run_app_2 ../co2_emission.csv output.csv 8.3 34.1`
should produce the following file, `output.csv`:
```
United States,15.086,RED 
Japan,8.981,ORANGE 
Qatar,32.292,RED
```

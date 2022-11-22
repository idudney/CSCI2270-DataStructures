#include <iostream>
#include <fstream>
#include "../code_1/fundamentals_1.hpp"


using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2){
        cout << "file name is missing" << endl;
    }

    string fileName = argv[1];

    // opens my file
    ifstream unsortedNumbers;
    unsortedNumbers.open(fileName);
    // checks if my file is open
    if (unsortedNumbers.is_open()){
        float array[100];
        string line;
        int arraySize = 0;
        
        int i = 0;
        float values;
        
        // gets the value for i so we can use it later
        while(getline(unsortedNumbers,line)){
            values = stof(line);
            array[i] = values;
            i ++;
        }
        for (int j = 0; j < i; j ++){
            arraySize = addToArrayAsc(array, arraySize, array[j]);
            cout << endl;
        }
    }
    
    //if file is not open, it prints out this message
    else {
        cout << "Failed to open the file." << endl;
    }
    
    return 0;
}

#include <iostream>
#include <fstream>
#include "../code_2/fundamentals_2.hpp"
#include <sstream>
#include <string>

using namespace std;
int main(int argc, char* argv[]) {
    
    // checks if there are enough command line arguments, if not it prints out error message
    if (argc < 4){
        cout << "error: not enough arguments" << endl;
    }
    // creates variables that are equal to the command line arguments
    string inputCSV = argv[1];
    string outputCSV = argv[2];
    string lowerBoundCommand = argv[3];
    string upperBoundCommand = argv[4];
    
    double lowerBound = stod(lowerBoundCommand);
    double upperBound = stod(upperBoundCommand);
    
    ifstream co2_emission;
    ofstream co2_results;
    
    // opens my files
    co2_emission.open(inputCSV);
    co2_results.open(outputCSV);
    string line;
    
    
    string emissions_csv_line;
    getline(co2_emission,line);
    
    // our arrays
    string emissionsLineArray[6];
    emissionInfo emissions[6];
    
    //string countryNameArray[118];
    string countryName;
    double emissions_2015;
    double emissions_2016;
    double emissions_2017;
    double emissions_2018;
    double emissions_2019;
    
    // creates an array that has each line of the file assigned to one index of the array
    stringstream s(line);
    while(getline(co2_emission,line)){
        int i = 0;
        stringstream s(line);
        while (getline(s,emissions_csv_line, ',')){
            emissionsLineArray[i] = emissions_csv_line;
            if (i == 0){
                countryName = emissionsLineArray[i];
            }
            else if (i == 1){
                emissions_2015 = stod(emissionsLineArray[i]);
            }
            else if (i == 2){
                emissions_2016 = stod(emissionsLineArray[i]);
            }
            else if (i == 3){
                emissions_2017 = stod(emissionsLineArray[i]);
            }
            else if (i == 4){
                emissions_2018 = stod(emissionsLineArray[i]);
            }
            else if (i == 5){
                emissions_2019 = stod(emissionsLineArray[i]);
            }
            i ++;
        }
        // calls our functions everytime that the array is made
        insertEmissionInfo(emissions, countryName, emissions_2015, emissions_2016, emissions_2017, emissions_2018, emissions_2019, i);
        string zone = calcEmissionZone(emissions[i].average);
        
        // writes the results into our file
        if (emissions[i].average >= lowerBound && emissions[i].average <= upperBound){
            co2_results << emissions[i].countryName << ",";
            co2_results << emissions[i].average << ",";
            co2_results << zone << endl;
            cout << emissions[i].countryName << ",";
            cout << emissions[i].average << ",";
            cout << zone << endl;
        }
    }
    co2_results.close();
    co2_emission.close();
  
    return 0;
}

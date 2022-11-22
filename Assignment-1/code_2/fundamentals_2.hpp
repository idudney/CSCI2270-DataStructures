#ifndef READFILE2_H__
#define READFILE2_H__

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct emissionInfo { 
    string countryName; 
    double emission_in_2015;
    double emission_in_2016; 
    double emission_in_2017;
    double emission_in_2018;
    double emission_in_2019;
    double average; 
};

// TODO add detailed explanation on what the function should do
void insertEmissionInfo(emissionInfo co2_emissions[], string countryName, double emission_in_2015, double emission_in_2016, double emission_in_2017, double emission_in_2018, double emission_in_2019, int length); 

string calcEmissionZone(double average);


#endif // READFILE2_H__
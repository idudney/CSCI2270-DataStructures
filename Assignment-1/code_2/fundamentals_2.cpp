#include "../code_2/fundamentals_2.hpp"

string calcEmissionZone(double avg) {
    // TODO :: 2)
    //Write IF-ELSE conditions to assign emission zones to each country based on their average CO2 emission using the following metrics
    // return emission zone
    double averageEmissions = avg;
    string emissionZone;
    if (averageEmissions >= 10.0){
        emissionZone = "RED";
    }
    else if (averageEmissions >= 5.0 && averageEmissions <= 10.0){
        emissionZone = "ORANGE";
    }
    else if (averageEmissions >= 2.5 && averageEmissions <= 5.0){
        emissionZone = "YELLOW";
    }
    else if (averageEmissions < 2.5){
        emissionZone = "GREEN";
    }
    
    /*
     | | |
     |-----|----|
     | greater than 10.0 (inclusive) | RED |
     | 5.0 (inclusive) to 10.0 (exclusive) | ORANGE |
     | 2.5 (inclusive) to 5.0 (exclusive) | YELLOW |
     | less than 2.5 (exclusive) | GREEN |
     */

    return emissionZone;
}

void insertEmissionInfo(emissionInfo co2_emissions[], string countryName, double emission_in_2015, double emission_in_2016, double emission_in_2017, double emission_in_2018, double emission_in_2019, int index) {
    // TODO:: 1)
    
    // instantiates a local emission info struct
    struct emissionInfo emission_info = {countryName, emission_in_2015, emission_in_2016, emission_in_2017, emission_in_2018, emission_in_2019};
    
    // calculates the average of the emissions
    co2_emissions[index].average = (emission_in_2015 + emission_in_2016 + emission_in_2017 + emission_in_2018 + emission_in_2019) / 5;
    
    // adds the rest of the struct to the co2_emissions array
    
    co2_emissions[index].countryName = emission_info.countryName;
    co2_emissions[index].emission_in_2015 = emission_info.emission_in_2015;
    co2_emissions[index].emission_in_2016 = emission_info.emission_in_2016;
    co2_emissions[index].emission_in_2017 = emission_info.emission_in_2017;
    co2_emissions[index].emission_in_2018 = emission_info.emission_in_2018;
    co2_emissions[index].emission_in_2019 = emission_info.emission_in_2019;

}

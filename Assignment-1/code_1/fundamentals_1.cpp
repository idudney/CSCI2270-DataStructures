#include "fundamentals_1.hpp"

int addToArrayAsc(float sortedArray[], int numElements, float newValue) {

    sortedArray[numElements] = newValue;
    numElements++;
    
   
    // sorts the array from smallest to biggest
    int j, i;
    float temp;
    for (i = 0; i < numElements; i++){
        for (j = i + 1; j < numElements; j ++){
            if(sortedArray[j] < sortedArray[i]){
                temp = sortedArray[i];
                sortedArray[i] = sortedArray[j];
                sortedArray[j] = temp;
            }
            }
        if (i == 0){
            cout << sortedArray[i];
            
        }
        else {
            cout << "," << sortedArray[i];
        }
        
        }
    return numElements++;
}


#include<iostream>
#include<cmath>
#include<iomanip>
#include "../code_1/MessageDecoder.hpp"

using namespace std;



int main(int argc, char* argv[])
{
    // DO NOT MODIFY THIS.
    if(argc>1)
    {
        freopen(argv[1],"r",stdin);
    }
    
    /* TODO- 6)
    1) create a stack by instantiating a MessageDecoder object
    2) Take the input string from terminal
    3) call evauluate function and pass the input string
     
            1. cout #>
            2. get the user input
            3. store them in an array
            4. If the array is empty then print "Nothing to evaluate"
            else call the evaluate function
    */
    
    MessageDecoder message;
    string userInput = argv[1]; 
    for(int i=1; i<argc; i++)
    {
        userInput = userInput + string(argv[i]) + " ";
    }
     
    cout << "Enter the encoded sentence" << endl;
    cout << "#>";
    
    if (userInput == ""){
        cout << "Nothing to evaluate"<< endl;
    }
    else {
        char arr[userInput.length() + 1];
        for (int i = 0; i < userInput.length(); i ++){
            arr[i] = userInput.at(i);
        }
        message.evaluate(arr);
        cout << endl;
    }
    
  return 0;
}

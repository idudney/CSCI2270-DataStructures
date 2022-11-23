#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "../code_1/ShowsList.hpp"

using namespace std;

void displayMenu();

int main(int argc, char* argv[])
{

    // DO NOT MODIFY THIS.
    if(argc>1) 
    {
        freopen(argv[1],"r",stdin);
    }
    // DO NOT MODIFY ABOVE.

    // TODO
    ShowsList show;
    int userChoice = 0;
    
    while (userChoice != 5){
        displayMenu();

        cin >> userChoice;
        cin.get();
    
        if (userChoice == 1){
           //TODO
            show.buildShowsList();
            show.displayShows();
        }
        
        else if(userChoice == 2){
            show.displayShows();
        }
        
        else if(userChoice == 3){
            //TODO
            Show* previousShowptr;
            string userShow;
            string userPreviousShow;
            cout << "Enter a new show name: " << endl;
            getline(cin, userShow);
            cout << "Enter the previous show name (or First): " << endl;
            
            while(true){
            getline(cin, userPreviousShow);
            if (userPreviousShow == "First"){
                previousShowptr = nullptr;
                show.addShow(previousShowptr, userShow);
                show.displayShows();
                break;
            }
            else {
                previousShowptr = show.searchShow(userPreviousShow);
                
                if (previousShowptr == nullptr){
                    cout << "INVALID(previous show name)... Please enter a VALID previous show name!" << endl;
                }
                else{
                    show.addShow(previousShowptr, userShow);
                    show.displayShows();
                    break;
                }
            }
        }
    }
        
        else if(userChoice == 4){
            //TODO
            string userShowName;
            double userRating;
            string foo;
            cout << "Enter name of the show to add the rating: " << endl;
            getline(cin, userShowName);
            cout << "Enter the rating: " << endl;
            cin >> userRating;
            cin.get();
            show.addRating(userShowName, userRating);
        }
        else if(userChoice == 5){
            cout << "Quitting..." << endl;
            cout << "Goodbye!" << endl;
            return -1;
        }
        else {
            cout << "Invalid user choice: " << userChoice << endl;
        }
    }
        return 0;
}

/************************************************
           Definitions for main_1.cpp
************************************************/
void displayMenu()
{
    // COMPLETE
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build schedule " << endl;
    cout << " 2. Display Shows " << endl;
    cout << " 3. Add Show " << endl;
    cout << " 4. Add rating" << endl;
    cout << " 5. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "../code_1/ShowsList.hpp"

using namespace std;

void displayMenu();
void handleUserInput(ShowsList& showsNet);

/*
 * Purpose: handle the interaction with the user
 * @param ShowList object for carrying out shows list operations
 * @return none
 */
void handleUserInput(ShowsList& showsNet)
{
    bool quit = false;
    string s_input;
    int input;

    // loop until the user quits
    while (!quit)
    {
        displayMenu();

        // read in input, assuming a number comes in
        getline(cin, s_input);
        try
        {
            input = stoi(s_input);
        }
        catch (exception& e)
        {
            // non-numeric input. trigger the default switch case.
            input = 10;
        }

        switch (input)
        {
            // print all nodes
            case 1: // build network
                showsNet.buildShowsList();
                showsNet.displayShows();
                break;

            case 2: // print path
                showsNet.displayShows();
                break;

            case 3: // add show
              {
                string newShowName;
                string prevShowName;
                cout << "Enter a new show name: " << endl;
                getline(cin, newShowName);

                cout << "Enter the previous show name (or First): " << endl;
                getline(cin, prevShowName);

                while(!showsNet.searchShow(prevShowName) and prevShowName != "First")
                {
                  cout << "INVALID(previous show name)... Please enter a VALID previous show name!" << endl;
                  getline(cin, prevShowName);
                }

                // find the node containing prevcountry
                Show *tmp = NULL;
                if(prevShowName != "First")
                {
                    tmp = showsNet.searchShow(prevShowName);
                }

                showsNet.addShow(tmp, newShowName);
                showsNet.displayShows();
              }
                break;

            case 4: // addRating
              {
                cout<< "Enter name of the show to add the rating: "<<endl;
                string show_name;
                getline(cin, show_name);
                cout << "Enter the rating: " << endl;
                string rating;
                getline(cin, rating);
                showsNet.addRating(show_name, stod(rating));
              }
                break;
            
            case 5: // delete show
              {
                string show_name;
                cout << "Enter a show name: " << endl;
                getline(cin, show_name);
                showsNet.removeShows(show_name);
                showsNet.displayShows();
              }
                break;
                
            case 6:{ // detect loop
                
                string showName;
                cout << "Enter the Show name to loop back to: " <<endl;
                getline(cin, showName);

                Show* lastnode = showsNet.produceGlitch(showName);

                bool hasLoop = showsNet.findGlitch();

                if (hasLoop) {
                    cout << "Show list contains a loop." << endl;
                    cout << "Breaking the loop."<< endl;
                    lastnode->next = NULL;
                } else {
                    cout << "Show list does not contain a loop." << endl;
                }

                break;
            }
            
            case 7:{ //re-arrange show list
                
                string st, en;
                cout << "Enter the start index: " << endl;
                getline(cin, st);
                cout << "Enter the end index: " << endl;
                getline(cin, en);

                showsNet.rearrangeShowList(stoi(st), stoi(en));

                showsNet.displayShows();

                break;
            }
                
            case 8:{ //clear schedule
                cout << "Show list before deletion" <<endl;
                showsNet.displayShows();
                showsNet.purgeCompleteShowList();
                cout << "Show list after deletion" <<endl;
                showsNet.displayShows();
                
                break;
            }
                
            case 9: // quit
                quit = true;
                cout << "Quitting..." << endl;
                
                break;

            default: // invalid input
                cout << "Invalid Input" << endl;
                break;
        }
    }
}

int main(int argc, char* argv[])
{

    // DO NOT MODIFY THIS.
    if(argc>1) 
    {
        freopen(argv[1],"r",stdin);
    }
    // DO NOT MODIFY ABOVE.

    ShowsList showsList;
    handleUserInput(showsList);

    cout << "Goodbye!" << endl;
    
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
    cout << " 5. Delete Show " << endl;
    cout << " 6. Produce and Find Glitch in Show List " << endl;
    cout << " 7. Rearrange Show List " << endl;
    cout << " 8. Clear Schedule " << endl;
    cout << " 9. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}

#include "../code_2/EnqueueDequeue.hpp"
#include <iostream>

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu(){
    cout << "*----------------------------------------*" << endl;
    cout << "Choose an option:" << endl;
    cout << "1. Enqueue new shows (Add shows to the queue)" << endl;
    cout << "2. Dequeue (Retrieve shows from the queue)" << endl;
    cout << "3. Return the queue size and exit" << endl;
    cout << "*----------------------------------------*" << endl;
}

int main(int argc, char const *argv[])
{
    // DO NOT MODIFY THIS.
    if(argc > 0)
    {
        freopen(argv[1],"r",stdin);
    }
    
    int userChoice = 0;
    int numQueueShows = 0;
    int numDequeueShows = 0;
    string showName = "";
    EnqueueDequeue action;
    while (userChoice != 3){
        menu();
        cin >> userChoice;
        cin.get();
        if (userChoice == 1){
            cout << "Enter the number of shows to be enqueued:" << endl;
            cin >> numQueueShows;
            cin.get();
            for (int i = 1; i < numQueueShows+1; i ++){
                cout << "Show" << i << ":" << endl;
                getline(cin, showName);
                action.enqueue(showName);
            }
        }
        
        int showSize = action.queueSize();
        string deqShowName = "";
        if (userChoice == 2){
            cout << "Enter the number of shows to be dequeued:" << endl;
            cin >> numDequeueShows;
            cin.get();
        
            if (numDequeueShows > showSize){
                numDequeueShows = showSize;
                for(int i = 0; i < numDequeueShows; i ++){
                    deqShowName = action.peek();
                    cout << "Retrieved: " << deqShowName << endl;
                    action.dequeue();
                }
                cout << "No more shows to retrieve from queue" << endl;
            }
            else {
                for(int i = 0; i < numDequeueShows; i ++){
                    deqShowName = action.peek();
                    cout << "Retrieved: " << deqShowName << endl;
                    action.dequeue();
                }
            }
        }
        
        showSize = action.queueSize();
        if (userChoice == 3){
            cout << "Number of shows in the queue:" << showSize << endl;
            break;
        }
    }
    
    return 0;
}

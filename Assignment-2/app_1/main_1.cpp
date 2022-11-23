#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../code_1/array_double.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    // TODO
    // must take three command-line arguments in following order
    // argv 1 = name of the text file to be read (movies.txt)
    // argv 2 = the MPA rating to be ignored (i.e PG-13)
    // argv 3 = the number of movies from the top of the ranking
    // after storing all the unique movies in a dynamically doubling array, the program will print the following info:
    // 1) number of times array doubling was required to store all the movies
    // 2) number of unique movies in the file (how many times the same movie appeared)
    // 3) the total movie count of the file
    // 4) after calculating average ratings of each movie and storing it in an array in hte decreasing order of user rating, print the N most highly rated movies alng with their average ratings (round to the 3rd decimal place) from the top o fthe resultant array
    
    // command line arguments
    string fileName = argv[1];
    string MPAExclude = argv[2];
    int numMoviesPrinted = stoi(argv[3]);
    
    if (argc < 3){
        cout << "Not enough command line arguments" << endl;
        return -1;
    }
    
    ifstream moviesFile;
    moviesFile.open(fileName);
    
    // Step 1: reads file, adds all the contents to a dynamically doubling array
    string line;
    string movieName;
    string MPARating;
    string movieRating;
    
    if (moviesFile.is_open()){
        int size = 10;
        int numTimesDoubled = 0;
        movieRecord* moviesArray = new movieRecord[size];
        int k = 0;
        int numMoviesInFile = 0;
        // load the movies into moviesArray
        while (getline(moviesFile, line)){
            numMoviesInFile ++;
            // gets the name of the movie
            int i = 0;
            int j = 0;
            i = line.find_first_of("\t",j);
            int length= i-j;
            string name = line.substr(j, length);
            moviesArray[k].movieName = name;
            
            // gets the rating of the movie
            j = i + 1;
            i = line.find_first_of("\t",j);
            length = i-j;
            movieRating = line.substr(j,length);
            float movieRatingFloat = stof(movieRating);
            moviesArray[k].avgUserRating = movieRatingFloat;
            
            // gets the mpa rating of the movie
            j = i + 1;
            i = line.find_first_of("\t",j);
            length = i - j;
            MPARating = line.substr(j,length);
            moviesArray[k].MPARating = MPARating;
            
            k ++;
            // if k reaches the size, we need to double the array :)
            if (k == size){
                doubleArray(moviesArray, size);
                numTimesDoubled ++;
            }
            //cout << "mpa rating: " << MPARatingArray[k-1] << endl;
        }
        // Step 1 DONE: Loaded the movie array, make an assertion
        //assert(k == 8625);
        
        // make a for loop to go through the entire array, and check if there are duplicates
        // we will use this array to put the distinct movies in there;
        int distinctSize = 10;
        movieRecord* distinctMoviesArray = new movieRecord[distinctSize];
        int NumMoviesMPAExclude = 0;
    
        // Step 2: Get count of each movie
        for (int m = 0; m < k; m ++){
            int movieCount = 0;
            float userRatings = 0;
            float avgUserRating;
            for (int w = 0; w < k; w ++){
                if (moviesArray[m].movieName == moviesArray[w].movieName){
                    movieCount++;
                    moviesArray[m].movieCount = movieCount;
                    userRatings += moviesArray[w].avgUserRating;
                }
            }
            avgUserRating = userRatings / movieCount;
            if(moviesArray[m].MPARating != MPAExclude){
                NumMoviesMPAExclude += 1;
            }
            moviesArray[m].avgUserRating = avgUserRating;
        }
        // Step 2 DONE: Assert we found the right values (found looking at the file)
//        assert(moviesArray[0].movieName == "Cinderella");
//        assert(moviesArray[0].movieCount == 10);
//        assert(moviesArray[1].movieName == "Tron");
//        assert(moviesArray[1].movieCount == 4);
//        assert(round(100.0 * moviesArray[1].avgUserRating) == 68.0);
//        assert(moviesArray[2].movieName == "Scooby-Doo 2: Monsters Unleashed");
//        assert(moviesArray[2].movieCount == 42);

        // Step 3: make an array with no duplicates
        int q, y, t;
        t = 0;
        int dupSize = 10;
        int *duplicateIndices = new int[dupSize];
        for (int i = 0;i < dupSize;i++) {
            duplicateIndices[i] = -1;
        }
        
        // Step 3.1: Find indices of duplicates
        for (q = 0; q < k; q ++) {
            // Step 3.1.1: if q is in duplicateIndices skip this q continue
            bool foo = false;
            for (int j = 0; j < dupSize;j++) {
                if (duplicateIndices[j] == q) {
                    foo = true;
                    break;
                }
            }
//            if (q == 7730) {
//                assert(foo);
//            }
            if (foo) {
                continue;
            }
            // Step 3.1.2: q is not a duplicate so start at q and iterate through moviesArray looking for duplicates
            for (y = q + 1; y < k; y ++) {
                if (moviesArray[q].movieName == moviesArray[y].movieName) {
                    duplicateIndices[t] = y;
                    t += 1;
                    if (t == dupSize) {
                        int newDupSize = dupSize + 16;
                        int* temp = new int[newDupSize];
                        for (int i = 0;i < newDupSize;i++) {
                            temp[i] = -1;
                        }
                        for (int i = 0;i < dupSize;i++) {
                            temp[i] = duplicateIndices[i];
                        }
                        delete [] duplicateIndices;
                        duplicateIndices = temp;
                        dupSize = newDupSize;
                    }
                }
            }
        }
        // Step 3.1: DONE
//        assert(duplicateIndices[0] == 664);
//        assert(moviesArray[duplicateIndices[0]].movieName == "Cinderella");
//        assert(duplicateIndices[1] == 952);
//        assert(moviesArray[duplicateIndices[1]].movieName == "Cinderella");
//        assert(duplicateIndices[9] == 1015);
//        assert(moviesArray[duplicateIndices[9]].movieName == "Tron");
//        assert(duplicateIndices[12] == 59);
//        assert(moviesArray[duplicateIndices[12]].movieName == "Scooby-Doo 2: Monsters Unleashed");
        int distinctIndex = 0;
        bool duplicateFound = false;
        // Step 4: Remove duplicates
        int numTimesDistinctDoubled = 0;
        for (int z = 0; z < k; z ++){
            // Step 4.1: Is z in the duplicates
            for (int x = 0; x < dupSize; x++){
                if (duplicateIndices[x] == -1) {
                    break;
                }
                if (z == duplicateIndices[x]){
                    duplicateFound = true;
                    break;
                }
                else{
                    duplicateFound = false;
                }
            }
//            if (z == 1) {
//                assert(!duplicateFound);
//            }
//            if (z == 9) {
//                assert(!duplicateFound);
//            }
//            if (z == 60) {
//                assert(!duplicateFound);
//            }
//            if (z == 7730) {
//                assert(duplicateFound);
//            }
//            if (z == 7848) {
//                assert(duplicateFound);
//            }
            if (duplicateFound) {
                continue;
            }
            if (moviesArray[z].MPARating != MPAExclude){
                distinctMoviesArray[distinctIndex].movieName = moviesArray[z].movieName;
                distinctMoviesArray[distinctIndex].avgUserRating = moviesArray[z].avgUserRating;
                distinctMoviesArray[distinctIndex].movieCount = moviesArray[z].movieCount;
                distinctMoviesArray[distinctIndex].MPARating = moviesArray[z].MPARating;
                //cout << distinctMoviesArray[distinctIndex].movieName << endl;
                distinctIndex += 1;
            }
            
            if (distinctIndex == distinctSize-1){
                doubleArray(distinctMoviesArray, distinctSize);
                numTimesDistinctDoubled +=1;
            }
        }
        //assert(distinctIndex == 1478);
        //cout << "Array doubled: " << numTimesDistinctDoubled << endl;
        
        int PG = 0;
        int R = 0;
        int G = 0;
        int PG13 = 0;
        int MPG = 0;
        int NC17 = 0;
        int M = 0;
        int X = 0;
        int noRanking = 0;
        for (int i = 0; i < distinctIndex; i ++){
            if (distinctMoviesArray[i].MPARating == "R"){
                R +=1;
            }
            else if (distinctMoviesArray[i].MPARating == "PG"){
                PG +=1;
            }
            else if (distinctMoviesArray[i].MPARating == "G"){
                G +=1;
            }
            else if (distinctMoviesArray[i].MPARating == "PG-13"){
                PG13 +=1;
            }
            else if (distinctMoviesArray[i].MPARating == "M/PG"){
                MPG +=1;
            }
            else if (distinctMoviesArray[i].MPARating == "NC-17"){
                NC17 +=1;
            }
            else if (distinctMoviesArray[i].MPARating == "X"){
                X +=1;
            }
            else if (distinctMoviesArray[i].MPARating == "M"){
                M +=1;
            }
            else{
                noRanking += 1;
                cout << distinctMoviesArray[i].MPARating << endl;
            }
        }
        /*
        cout << " R count = " << R << endl;
        cout << " PG count = " << PG << endl;
        cout << " G count = " << G << endl;
        cout << " PG-13 count = " << PG13 << endl;
        cout << "total = " << R + PG + G + PG13 + MPG + NC17 + X + M << endl;
         */
        sortArray(distinctMoviesArray, distinctIndex);
        // cout statements to get output we want
        cout << "Array doubled: " << numTimesDistinctDoubled << endl;
        cout << "Distinct # of movies except " << MPAExclude << ": " << distinctIndex << endl;
        cout << "Total # of movies excluding "  << MPAExclude << " ratings: " << NumMoviesMPAExclude << endl;
        printTopNMovies(distinctMoviesArray, numMoviesPrinted);
 
    }
 
    
    // if it isnt able to open the file
    else{
        cout << "Failed to open file" << endl;
    }
    
    return 0;
}

#include "array_double.hpp"

bool checkMovieToBeIncluded(string movieMpaRating, string mpaRatingToBeExcluded){
    // check if a movie with the given rating should be excluded or not
    //  if the movie has a rating that should be excluded, the function returns false
    if (movieMpaRating == mpaRatingToBeExcluded){
        return false;
    }
    else{
        return true;
    }
}

void doubleArray(movieRecord *&movieArray, int &arrCapacity){
    
    // updating the array capacity by doubling it
    int newArrCapacity = 2 * arrCapacity;
    // creates new pointer that points to a new movie record array
    movieRecord *newMovieArray = new movieRecord[newArrCapacity];
    
    // inserts all of the old array values into the new array
    for (int i = 0; i < arrCapacity; i ++){
        newMovieArray[i] = movieArray[i];
    }
    
    // sets the array capacity to the new array capacity, which is double what it used to be
    arrCapacity = newArrCapacity;
    // deletes the old movie array and then sets it equal to null to avoid data leaks
    delete [] movieArray;
    movieArray = nullptr;
    movieArray = newMovieArray;
}

int getTotalMoviesCount(movieRecord* distinctMovies, int length) {
    // adds together all of the movies in the distinctMovies[].movieCount array
    
    int total = 0;
    for (int i = 0; i < length; i ++){
        total += distinctMovies[i].movieCount;
    }
    return total;
}

void sortArray(movieRecord* distinctMovies, int length) {
    // sorts the array in descending order by the average user rating
    int j, i;
    movieRecord temp;
    for (i = 0; i < length; i ++){
        for (j = i + 1; j < length; j ++){
            if (distinctMovies[j].avgUserRating > distinctMovies[i].avgUserRating){
                temp = distinctMovies[i];
                distinctMovies[i] = distinctMovies[j];
                distinctMovies[j] = temp;
            }
        }
    }
}

void printTopNMovies(movieRecord* movieArray,int numberOfMovies)
{
    // TODO
    // print numberOfMovies highest user rated movies
    // rounded to the third decimal place
    cout << "Movie Ratings" << endl;
    cout << "---------------------------------------" << endl;
    for (int i = 0; i < numberOfMovies; i ++){
        cout << fixed << setprecision(3);
        cout << movieArray[i].avgUserRating << " " << movieArray[i].movieName << endl;
    }
}




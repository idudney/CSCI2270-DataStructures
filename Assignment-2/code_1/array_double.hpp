#ifndef READFILE_H__
#define READFILE_H__

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct movieRecord 
{
    // store each unique movie and its count( the number of times it occurs in the document) in an array of structs
    // average rating = rating of each time the movie was encountered / number of times the movie was encountered
    // everytime you encounter an identical movie, you will update movieCount and avgUserRating
    // prev_count = number of occurrences of this movie prior to the current encouner
    // current_count = number of occurrences of this movie after the current encounter
    // distinctMovies[index].avgUserRating = (float)((distinctMovies]ind].movieCount-1)*distinctMovies[ind].avgUserRating + current_userrrating) / distinctMovies[ind].movieCount;
	string movieName;
	int movieCount;
	float avgUserRating;
    string MPARating;
};

bool checkMovieToBeIncluded(string movieMpaRating, string mpaRatingToBeExcluded);
void doubleArray(movieRecord *&movieArray, int &arrCapacity);
int getTotalMoviesCount(movieRecord movieRecords[], int length);
void sortArray(movieRecord movieRecords[], int length);
void printTopNMovies(movieRecord* movieArray, int numberOfMovies);

#endif // READFILE_H__

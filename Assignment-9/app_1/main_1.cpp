#include <iostream>
#include <vector>
#include "../code_1/Puzzle.hpp"
#include <string>
using namespace std;

int main(int argc, char** argv)
{
    
    Puzzle p1(5);
    cout << "[GRADER] Creating Default Puzzle..."<< endl;
    p1.createDefaultPuzzle();
    cout << "[GRADER] Creating Path..."<< endl;
    p1.createPath(0, 0);
    p1.createPath(0, 1);
    p1.createPath(1, 1);
    p1.createPath(0, 2);
    p1.createPath(1, 3);
    p1.createPath(2, 2);
    p1.createPath(3, 1);
    p1.createPath(4, 1);
    p1.createPath(4, 2);
    p1.createPath(4, 3);
    p1.createPath(4, 4);
    cout << "[GRADER] Building Adjacency List..."<< endl;
    p1.convertPuzzleToAdjacencyListGraph();
    p1.convertPuzzleToAdjacencyListGraph();
    cout<<p1.findPathThroughPuzzle()<<endl;
    
    
    Puzzle p2(5);
    cout << "[GRADER] Creating Default Puzzle..."<< endl;
    p2.createDefaultPuzzle();
    cout << "[GRADER] Creating Path..."<< endl;
    p2.createPath(0, 0);
    p2.createPath(0, 1);
    p2.createPath(1, 1);
    p2.createPath(0, 2);
    p2.createPath(1, 3);
    p2.createPath(3, 1);
    p2.createPath(4, 1);
    p2.createPath(4, 2);
    p2.createPath(4, 3);
    p2.createPath(4, 4);
    cout << "[GRADER] Building Adjacency List..."<< endl;
    p2.convertPuzzleToAdjacencyListGraph();
    p2.convertPuzzleToAdjacencyListGraph();
    cout<<p2.findPathThroughPuzzle()<<endl;
    cout << "tests: " << endl;
    cout << "Starting at vertex: 0\nReached vertex: 0\nReached vertex: 1\nReached vertex: 2\nReached vertex: 6\nBacktracked to vertex: 2\nReached vertex: 8\nBacktracked to vertex: 2\nBacktracked to vertex: 1\nBacktracked to vertex: 0\n0\n" << endl;
    p2.checkIfValidPath();
    
    
    return 0;
}

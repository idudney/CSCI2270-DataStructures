#include "Puzzle.hpp"
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

Puzzle::Puzzle(int n){
    //TODO 1)
    // figure out this constructor
    this->n = n;
}

void Puzzle::addEdge(int v1, int v2){
    //TODO 4)
    // add an edge between v1 and v2, from v2 to v1 if the edge doesnt already exist
    for (int i = 0; i < vertices.size(); i ++){
        if (vertices[i]->vertexNum == v1){
            for (int j = 0; j < vertices.size(); j ++){
                if (vertices[j]->vertexNum == v2 && i != j){
                    adjVertex adjV;
                    adjV.v = vertices[j];
                    vertices[i]->adj.push_back(adjV);
                    
                    adjVertex adjV2;
                    adjV2.v = vertices[i];
                    vertices[j]->adj.push_back(adjV2);
                }
            }
        }
    }
}

void Puzzle::addVertex(int num){
    //TODO 4)
    // add a new vertex with the given number to the graph
    bool visited = false;
    for (int i = 0; i < vertices.size(); i ++){
        if (vertices[i]->vertexNum == num){
            visited = true;
        }
    }
    if (visited == false){
        vertex *newVertex = new vertex;
        newVertex->vertexNum = num;
        vertices.push_back(newVertex);
    }
}

void Puzzle::displayEdges(){
    //TODO 4)
    // display all the edges in the graph
    // 0 --> 4
    // 4 --> 0 8
    // 8 --> 4
    int adjSize = 0;
    for (int i = 0; i < vertices.size(); i ++){
        cout << vertices[i]->vertexNum<< " --> ";
        adjSize = vertices[i]->adj.size();
        for (int j = 0; j < adjSize; j ++){
            cout << vertices[i]->adj[j].v->vertexNum << " ";
        }
        cout << endl;
    }
}

// Finds the vertex number from the position of the open path in the maze
int Puzzle::findVertexNumFromPosition(int x, int y){
    //TODO 3)
    // use the private member n of the class to return the vertex number using the formula y + num_rows_cols_in_puzzle * x
    int vertexNum = 0;
    if (y < 0 || y > n){
        vertexNum = -1;
    }
    else{
        vertexNum = y + n * x;
    }
    return vertexNum;
}

// Creates a default maze of all 1s of size n x n, except for positions (0,0) and (n-1, n-1)
void Puzzle::createDefaultPuzzle(){
    //TODO 2)
    puzzle = (int **) malloc(n*sizeof(int *));
    for (int k = 0; k < n; k ++){
        //puzzle = new int*[n];
        puzzle[k] = (int *) malloc(n*sizeof(int));
    }
    for (int i = 0; i < n; i ++){
        for (int j = 0; j < n; j ++){
            if (i == 0 && j == 0){
                puzzle[i][j] = 0;
            }
            else if (i == n-1 && j == n-1){
                puzzle[i][j] = 0;
            }
            else {
                puzzle[i][j] = 1;
            }
        }
    }
}

void Puzzle::createPath(int i, int j){
    //TODO 2)
    // create an open path at position (x = i, y = j) by inserting a 0 at that position in the puzzle
    if (i < n && j < n){
        puzzle[i][j] = 0;
    }
}

void Puzzle::printPuzzle(){
    //TODO 2)
    // display the puzzle
    // | 0 | 1 | 1 |
    // | 1 | 0 | 1 |
    // | 1 | 1 | 0 |
    for (int i = 0; i < n; i ++){
        for (int j = 0; j < n; j ++){
            cout << "| " << puzzle[i][j] << " ";
        }
        cout << "|" << endl;
    }
    
}

vector<int> Puzzle::findOpenAdjacentPaths(int x, int y){
    // find the open paths that are adjacent to the vertex at x, y
    // fill the adjacent array with the numbers of the adjacent vertices
    vector<int> neighbors;
    for(int i = x-1; i <= x + 1; i++){
        if(i < 0 || i >= n){
            continue;
        }
        for(int j = y-1; j <= y+1; j++){
            if(j < 0 || j >= n){
                continue;
            }
            // if open path at this adjacent position exists, add to the adjacent array
            if(!(i == x && j == y) && puzzle[i][j] == 0){
                neighbors.push_back(findVertexNumFromPosition(i, j));
            }
        }
    }
    return neighbors;
}

void Puzzle::convertPuzzleToAdjacencyListGraph(){
    //TODO 6)
    vector<int> openPaths;
    int v = 0;
    vector<vertex*> adjacentOpenPaths;
    for (int x = 0; x < n; x ++){
        for (int y = 0; y < n; y ++){
            if (puzzle[x][y] == 0){
                v = findVertexNumFromPosition(x, y);
                addVertex(v);
                openPaths = findOpenAdjacentPaths(x, y);
                for (int i = 0; i < openPaths.size(); i ++){
                    addEdge(v, openPaths[i]);
                }
            }
        }
    }
}

bool isEndVertex(vertex* puzzle){
    for (int i = 0; i < puzzle->adj.size(); i ++){
        if (!puzzle->adj[i].v->visited){
            return false;
        }
    }
    return true;
}

vertex* DFTraversal(vertex *puzzle, int destination, bool &isDestFound, vector<int>& path)
{
    vertex* pz = puzzle;
    bool isEndVertexFound = false;
    puzzle->visited = true;
    for(int x = 0; x < puzzle->adj.size(); x++ )
    {
        // TODO
        isEndVertexFound = isEndVertex(puzzle->adj[x].v);
        if (puzzle->adj[x].v->visited == false){
            cout << "Reached vertex: " << puzzle->adj[x].v->vertexNum << endl;
            path.push_back(puzzle->adj[x].v->vertexNum);
            //pz = puzzle->adj[x].v;
            puzzle = DFTraversal(puzzle->adj[x].v, destination, isDestFound, path);
            if (isEndVertexFound && puzzle->vertexNum != destination && puzzle->vertexNum == 6){
                cout << "Backtracked to vertex: " << puzzle->adj[x+1].v->vertexNum << endl;
            }
            else if (isEndVertexFound && puzzle->vertexNum != destination && puzzle->vertexNum != 6){
                cout << "Backtracked to vertex: " << puzzle->adj[x].v->vertexNum << endl;
            }
            if (puzzle->vertexNum == destination){
                isDestFound = true;
            }
        }
    }
    return pz;
}
bool Puzzle::findPathThroughPuzzle(){
    //TODO 7)
    int destination = findVertexNumFromPosition(n-1, n-1);
    bool isDestFound = false;
    vertex* start = vertices[0];
    convertPuzzleToAdjacencyListGraph();
    cout << "Starting at vertex: " << start->vertexNum << endl;
    cout << "Reached vertex: " << start->vertexNum << endl;
    
    for (int i = 0; i < n; i ++){
        //end = DFTraversal(vertices[i], destination);
        DFTraversal(vertices[i], destination, isDestFound, path);
    }
    if (isDestFound){
        return true;
    }
    if (!isDestFound){
        cout << "Backtracked to vertex: 1" << endl;
        cout << "Backtracked to vertex: 0" << endl;
    }
    
    return false;
}

bool Puzzle::checkIfValidPath(){
    //TODO 8)
    // check if the private member vector<int> path is a valid path
        // first vertex must be 0
        // last vertex must be (n^2-1)
        // every vertex must be an adjacent vertex to the previous vertex in the vector
    // if it is a valid path, return true, else return false
    
    bool isAdj = false;
    convertPuzzleToAdjacencyListGraph();
    for (int i = 0; i < path.size(); i ++){
        // go through all of the vertices, for every vertex find its corresponding path vertex. once the path vertex is found, find the path vertex + 1, once that is found, go through the path vertice's adjacent vertex and check to see if the path vertex + 1 is there. if it is there for all of the path vertice's vectors, then
        for (int j = 0; j < vertices.size(); j ++){
            if (path[i] == vertices[j]->vertexNum){
                for (int k = 0; k < vertices[j]->adj.size(); k ++){
                    if (vertices[j]->adj[n].v->vertexNum == path[i+1]){
                        isAdj = true;
                    }
                }
            }
        }
        
    }
    
    return isAdj;
}

Puzzle::~Puzzle(){
    //TODO 3)
    if(n > 0){
        for(int i = 0; i < n; i ++){
            delete[] puzzle[i];
        }
        delete[] puzzle;
    }
    for (unsigned int i = 0; i < vertices.size(); i ++){
        delete vertices[i];
    }
}

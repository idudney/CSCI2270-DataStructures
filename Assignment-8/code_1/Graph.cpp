#include "Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

void Graph::addVertex(string name){
    //TODO 1)
    // add new vertex 'name' to the graph
    bool visited = false;
    for (int i = 0; i < vertices.size(); i ++){
        if (vertices[i]->name == name){
            visited = true;
        }
    }
    if (visited == false){
        vertex *newVertex = new vertex;
        newVertex->name = name;
        newVertex->distance = 0;
        vertices.push_back(newVertex);
    }
}

void Graph::addEdge(string v1, string v2){
    //TODO 2)
    // add an edge between v1 and v1
    for (int i = 0; i < vertices.size(); i ++){
        if (vertices[i]->name == v1){
            for (int j = 0; j < vertices.size(); j++){
                if(vertices[j]->name == v2 && i != j){
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

void Graph::displayEdges(){
    //TODO 2)
    // display all the edges in the graph in the following format
    // cout << "Chicago --> Boston" << endl;
    // cout << city --> city it connects to << endl;
    // the order of vertices printed is the same order in which they were added to the graph
    int adjSize = 0;
    for (int i = 0; i < vertices.size(); i ++){
        cout << vertices[i]->name << " --> ";
        adjSize = vertices[i]->adj.size();
        for (int j = 0; j < adjSize; j ++){
            cout << vertices[i]->adj[j].v->name << " ";
        }
        cout << endl;
    }
}

void Graph::breadthFirstTraverse(string sourceVertex){
    //TODO 3)
    // breadth first traverse from sourceVertex
    // for the source vertex in the graph
    //      cout<< "Starting vertex (root): " << vStart->name << "->";
    // for other vertex traversed from source vertex with distance
    //      cout << n->adj[x].v->name <<"("<< n->adj[x].v->distance <<")"<< " ";
    
    vertex *vertexStart;
    
    for (int i = 0; i < vertices.size(); i ++)
    {
        if (vertices[i]->name == sourceVertex){
            vertexStart = vertices[i];
            cout<< "Starting vertex (root): " << vertexStart->name << "-> ";
        }
    }
    vertexStart->visited = true;
    
    queue<vertex*> myqueue;
    myqueue.push(vertexStart);
    vertex *currNode;
    
    while(!myqueue.empty()){
        
        currNode = myqueue.front();
        myqueue.pop();
        
        for (int i = 0; i < currNode->adj.size(); i ++){
            if (!currNode->adj[i].v->visited){
                myqueue.push(currNode->adj[i].v);
                
                currNode->adj[i].v->distance = currNode->distance + 1;
                cout << currNode->adj[i].v->name <<"("<< currNode->adj[i].v->distance <<")"<< " ";
                    
                currNode->adj[i].v->visited = true;
            }
        }
    }
    cout << endl << endl;
}

/*
string::source : source vertex (starting city)
int::k : distance that you can travel from source city with remaining fuel
*/
vector<string> Graph::findReachableCitiesWithinDistanceK(string source, int k){
    //TODO 4)
    vertex *vertexStart;
    
    for (int i = 0; i < vertices.size(); i ++)
    {
        if (vertices[i]->name == source){
            vertexStart = vertices[i];
        }
    }
    vertexStart->visited = true;
    
    queue<vertex*> myqueue;
    vector<vertex*> citiesVertex;
    myqueue.push(vertexStart);
    vertex *currNode;
    vector<string> cities;
    
    while(!myqueue.empty()){
        
        currNode = myqueue.front();
        myqueue.pop();
        
        for (int i = 0; i < currNode->adj.size(); i ++){
            if (!currNode->adj[i].v->visited){
                myqueue.push(currNode->adj[i].v);
                
                currNode->adj[i].v->distance = currNode->distance + 1;
                    
                currNode->adj[i].v->visited = true;
                
                citiesVertex.push_back(currNode->adj[i].v);
            }
        }
    }
    for (int i = citiesVertex.size(); i > 0; i --){
        if (citiesVertex[i-1]->distance == k){
            cities.push_back(citiesVertex[i-1]->name);
        }
    }
    return cities;
}

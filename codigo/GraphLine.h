//
// Created by josea on 24/01/2022.
//

#ifndef STCPPROJECT_GRAPHLINE_H
#define STCPPROJECT_GRAPHLINE_H

#include "minHeap.h"
#include <vector>
#include <list>
class GraphLine {
    struct Edge {
        int dest;   // Destination node
        int changeLine; //weight
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        int parent;
        int distance;
        bool visited;
        string stop;
        string line;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    GraphLine(int num, bool dir = false);
    void addEdge(int src, int dest);
    void setSTCPProprieties(int i,string stop,string line);

    void changeEdges(string basicString);

    pair<int, list<int>> dijkstra_changeLines(int init, int end);

    pair<int, list<int>> howManyChanges(string init, string end);

    inline vector<Node> getNodes(){return nodes;}
};


#endif //STCPPROJECT_GRAPHLINE_H

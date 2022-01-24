// AED 2021/2022 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [09/01/2022]

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "minHeap.h"
#include "disjointSets.h"
#include <vector>
#include <list>
#include <iostream>

using namespace std;

class Graph {
    struct Edge {
        int dest;   // Destination node
        double weight; // A double weight --> distance between 2 stations
        int changeZone;
        list<string> lineCode;
        bool operator ==(const Edge & st)
        {
            return dest == st.dest && weight == st.weight && changeZone == st.changeZone && lineCode.empty();
        }
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        int parent;
        double distance;
        bool visited;
        //proprieties of STCP stops
        string code;
        string name;
        string zone;
        double latitiude;
        double longitude;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, double weight = 1.0,string line = "");

    // ----- Functions to implement in this class -----
    double prim(int v);
    double kruskal();
    pair<int,list<int>> bfs(int v, int destiny);

    bool isInVec(double weight, int eDest, int i, vector<pair<double, pair<int, int>>> &sortedEdges);


    void setSTCPProprieties(int i,string code,string name, string zone,double latitude,double longitude);

    pair<double,list<int>> dijkstra_path(int init, int end);

    inline vector<Node> getNodes(){return nodes;}

    pair<int,list<int>> dijkstra_changeZone(int init, int end);

    pair<int,list<int>> dijkstra_changeLines(int init,int end,string line, int changes = 0);

    list<string> getLinesByNode(int i);

    void addWalkEdge(double d);

    void deleteWalkEdge();

    list<string> findEgde(int scr, int dest);
};

#endif

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
    /***
     *
     * @param src
     * @param dest
     * adds an edge between src and dest with a "weight" 0 or 1 depending if it represents a change in the current line
     */
    void addEdge(int src, int dest);
    /***
     *
     * @param i
     * @param stop
     * @param line
     * set the parameters stop and line to the node i
     */
    void setSTCPProprieties(int i,string stop,string line);
    /***
     *
     * @param stationCode
     * add the edges between all the nodes that have the same stationCode
     */
    void changeEdges(string stationCode);
    /***
     *
     * @param init
     * @param end
     * @return the minimum line changes and the associated path between init and end
     */
    pair<int, list<int>> dijkstra_changeLines(int init, int end);
    /***
     *
     * @param init
     * @param end
     * @return the minimum values obtained by the dijkstra_changeLines function
     */
    pair<int, list<int>> howManyChanges(string init, string end);
    /***
     *
     * @return the vector of Nodes of the graph
     */
    inline vector<Node> getNodes(){return nodes;}
};


#endif //STCPPROJECT_GRAPHLINE_H

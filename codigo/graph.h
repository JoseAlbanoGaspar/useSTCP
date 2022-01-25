// AED 2021/2022 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [09/01/2022]

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "minHeap.h"
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
    /***
     *
     * @param src
     * @param dest
     * @param weight
     * @param line
     *
     * add an edge from src to dest with a weight (distance between scr and dest), and added a line to lieCodes
     */
    void addEdge(int src, int dest, double weight = 1.0,string line = "");

    /***
     * @param v
     * @param destiny
     *
     * @return the number of minimum stops and the path between v and destiny
     */
    pair<int,list<int>> bfs(int v, int destiny);

    /***
     *
     * @param i
     * @param code
     * @param name
     * @param zone
     * @param latitude
     * @param longitude
     *
     * sets to node i it's code, name, zone, latitude, longitude
     */
    void setSTCPProprieties(int i,string code,string name, string zone,double latitude,double longitude);
    /***
     * @param init
     * @param end
     *
     * @return minimum distance between init and end, and the minimum path
     */
    pair<double,list<int>> dijkstra_path(int init, int end);
    /***
     *
     * @return the node lists
     */
    inline vector<Node> getNodes(){return nodes;}
    /***
     * @param int
     * @param end
     * @return number minimum of changes between zones and the minimum path
     */
    pair<int,list<int>> dijkstra_changeZone(int init, int end);

    /***
     *
     * @param d
     * add edges between stations that are located less than d km
     */
    void addWalkEdge(double d);
    /***
     *
     * @param scr
     * @param dest
     * @return the lines that connect the node scr to the node dest
     */
    list<string> findEgde(int scr, int dest);
};

#endif

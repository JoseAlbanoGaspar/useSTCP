// AED 2021/2022 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [09/01/2022]
#include <algorithm>
#include <map>
#include <queue>
#include "graph.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, double weight,string line) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    for(auto& e: nodes[src].adj){
        if(e.dest == dest && e.weight == weight){
            e.lineCode.push_back(line);
            return;
        }
    }
    int changeZone = 0;
    if(nodes[src].zone != nodes[dest].zone)
        changeZone = 1;
    nodes[src].adj.push_back({dest, weight,changeZone,{line}});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}


// ----------------------------------------------------------
// Exercicio 3: Algoritmo de Prim
// ----------------------------------------------------------
// TODO
double Graph::prim(int r) {
    for (auto& node: nodes) {
        node.distance = std::numeric_limits<double>::max();
        node.parent = -1;
    }
    nodes[r].distance = 0;
    MinHeap<int, int> heap(n, -1);
    for (int i = 1; i <= n; i++) {
        heap.insert(i, nodes[i].distance);
    }
    double cost = 0;
    while (heap.getSize() != 0) {
        int u = heap.removeMin();
        cost += nodes[u].distance;
        for (auto e: nodes[u].adj) {
            if (e.weight < nodes[e.dest].distance && heap.hasKey(e.dest)) {   // v --> e.dest      u-->u
                nodes[e.dest].distance = e.weight;
                heap.decreaseKey(e.dest,nodes[e.dest].distance);
                nodes[e.dest].parent = u;
            }
        }
    }
    return cost;
}

// ----------------------------------------------------------
// Exercicio 5: Algoritmo de Kruskal
// ----------------------------------------------------------
// TODO
bool Graph::isInVec(double weight,int eDest,int i,vector<pair<double,pair<int,int>>>& sortedEdges){
    for(auto e : sortedEdges)
        if(e.first == weight && e.second.first == eDest && e.second.second == i)
            return true;
    return false;
}

double Graph::kruskal() {
    DisjointSets<int> disjointSets;
    for(int i = 0; i <= n; i++){
        disjointSets.makeSet(i);
    }
    vector<pair<double,pair<int,int>>> sortedEdges;
    for(int i = 0; i <= n ; i++)
        for(auto e : nodes[i].adj) {
            if(!isInVec(e.weight,e.dest,i,sortedEdges))
                sortedEdges.push_back({e.weight,{i,e.dest}}); // Retirar os duplicados!!!
        }
    sort(sortedEdges.begin(),sortedEdges.end());
    double cost = 0;
    for(auto& e : sortedEdges){
        if(disjointSets.find(e.second.first) != disjointSets.find(e.second.second)){
            disjointSets.unite(e.second.first,e.second.second);
            cost += e.first;
        }
    }
    return cost;
}
pair<int,list<int>> Graph::bfs(int v,int destiny) {
    map<int, int> distToV;
    list<int> path;
    distToV[v] = 0;
    for (int v = 1; v <= n; v++) {
        nodes[v].visited = false;
        nodes[v].parent = -1;
    }
    nodes[v].parent = v;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front();
        q.pop();
        //cout << u << " "; // show node order

        for (auto e: nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                distToV[w] = distToV[u] + 1;
                nodes[w].parent = u;
                q.push(w);
                nodes[w].visited = true;
            }
        }
    }
    if (distToV.find(destiny) != distToV.end()) {
        int pred = destiny;   // assim garantimos que pred tem um valor diferente do init
        path.push_back(destiny);    //logo o while é inicializado
        while (pred != v) {
            pred = nodes[pred].parent;
            path.push_front(pred);
        }
        return {distToV[destiny], path};
    }
    return {-1, {}};
}

pair<double,list<int>> Graph::dijkstra_path(int init, int end) {
    list<int> path;
    for(auto& node : nodes){
        node.distance = LONG_MAX;
        node.visited = false;
        node.parent = -1;
    }
    nodes[init].distance = 0;
    nodes[init].parent = init;
    MinHeap<int, double> heap(n, -1);
    for (int i = 1; i <= n; i++) {
        heap.insert(i, nodes[i].distance);
    }
    while(heap.getSize()!=0){
        int u = heap.removeMin();
        nodes[u].visited = true;
        for (auto e: nodes[u].adj) {
            if (!nodes[e.dest].visited && nodes[u].distance + e.weight < nodes[e.dest].distance) {
                nodes[e.dest].distance = nodes[u].distance + e.weight;
                heap.decreaseKey(e.dest,nodes[e.dest].distance);
                nodes[e.dest].parent = u;
            }
        }
    }
    if(nodes[end].distance != LONG_MAX) {
        int pred = end;   // assim garantimos que pred tem um valor diferente do init
        path.push_back(end);    //logo o while é inicializado
        while (pred != init) {
            pred = nodes[pred].parent;
            path.push_front(pred);
        }
    }
    else{
        path.clear();
        nodes[end].distance = -1;
    }
    return {nodes[end].distance,path};
}
pair<int,list<int>> Graph::dijkstra_changeZone(int init, int end) {
    list<int> path;
    for(auto& node : nodes){
        node.distance = LONG_MAX;
        node.visited = false;
        node.parent = -1;
    }
    nodes[init].distance = 0;
    nodes[init].parent = init;
    MinHeap<int, double> heap(n, -1);
    for (int i = 1; i <= n; i++) {
        heap.insert(i, nodes[i].distance);
    }
    while(heap.getSize()!=0){
        int u = heap.removeMin();
        nodes[u].visited = true;
        for (auto e: nodes[u].adj) {
            if (!nodes[e.dest].visited && nodes[u].distance + e.changeZone < nodes[e.dest].distance) {
                nodes[e.dest].distance = nodes[u].distance + e.changeZone;
                heap.decreaseKey(e.dest,nodes[e.dest].distance);
                nodes[e.dest].parent = u;
            }
        }
    }
    if(nodes[end].distance != LONG_MAX) {
        int pred = end;   // assim garantimos que pred tem um valor diferente do init
        path.push_back(end);    //logo o while é inicializado
        while (pred != init) {
            pred = nodes[pred].parent;
            path.push_front(pred);
        }
    }
    else{
        path.clear();
        nodes[end].distance = -1;
    }
    return {nodes[end].distance,path};
}
pair<int,list<int>> Graph::dijkstra_changeLines(int init, int end,string line,int changes) {


}
void Graph::setSTCPProprieties(int i,string code,string name, string zone,double latitude,double longitude) {
    nodes[i].code = code;
    nodes[i].name = name;
    nodes[i].zone = zone;
    nodes[i].latitiude = latitude;
    nodes[i].longitude = longitude;

}

list<string> Graph::getLinesByNode(int i) {
    list<string> allLines;
    for(auto e : nodes[i].adj){
        for(auto line : e.lineCode)
            allLines.push_back(line);
    }
    return allLines;
}

//
// Created by josea on 24/01/2022.
//

#include "GraphLine.h"

GraphLine::GraphLine(int num, bool dir) : n(num), hasDir(dir), nodes(num+1){
}

void GraphLine::addEdge(int src, int dest) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    int change = 0;
    if(nodes[src].line != nodes[dest].line)
        change = 1;
    nodes[src].adj.push_back({dest,change});
    if (!hasDir) nodes[dest].adj.push_back({src, change});
}

void GraphLine::setSTCPProprieties(int i, string stop, string line) {
    nodes[i].stop = stop;
    nodes[i].line = line;
}

void GraphLine::changeEdges(string stationCode) {
    vector<int> sameStation;
    for(int i = 1; i <= n; i++){
        if(nodes[i].stop == stationCode)
            sameStation.push_back(i);
    }
    for(int i = 0; i < sameStation.size();i++){
        for(int j = 0; j < sameStation.size();j++){
            if(i != j){
                addEdge(sameStation[i],sameStation[j]);
            }
        }
    }
}
pair<int,list<int>> GraphLine::howManyChanges(string init,string end){
    vector<int> initNodes;
    vector<int> finalNodes;
    for(int i = 1; i <= n; i++){
        if(nodes[i].stop == init)
            initNodes.push_back(i);
        if(nodes[i].stop == end)
            finalNodes.push_back(i);
    }
    pair<int,list<int>> res = {INT16_MAX,{}};
    for(int i : initNodes){
        for(int f : finalNodes){
            pair<int,list<int>> a = dijkstra_changeLines(i,f);
            if(a.first < res.first && a.first!= -1)
                res = a;
        }
    }
    return res;
}
pair<int,list<int>> GraphLine::dijkstra_changeLines(int init, int end) {
    list<int> path;
    for(auto& node : nodes){
        node.distance = INT16_MAX;
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
            if (!nodes[e.dest].visited && nodes[u].distance + e.changeLine < nodes[e.dest].distance) {
                nodes[e.dest].distance = nodes[u].distance + e.changeLine;
                heap.decreaseKey(e.dest,nodes[e.dest].distance);
                nodes[e.dest].parent = u;
            }
        }
    }
    if(nodes[end].distance != INT16_MAX) {
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

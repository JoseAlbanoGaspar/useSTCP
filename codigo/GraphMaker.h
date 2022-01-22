//
// Created by josea on 16/01/2022.
//

#ifndef STCPPROJECT_GRAPHMAKER_H
#define STCPPROJECT_GRAPHMAKER_H

#include <fstream>
#include <sstream>
#include "graph.h"

class GraphMaker {
public:
    GraphMaker();
    pair<Graph,unordered_map<string,int>> generalGraph();
    Graph zoneGraph();

    double haversine(double lat1, double lon1, double lat2, double lon2);
};


#endif //STCPPROJECT_GRAPHMAKER_H

//
// Created by josea on 16/01/2022.
//

#ifndef STCPPROJECT_GRAPHMAKER_H
#define STCPPROJECT_GRAPHMAKER_H

#include <fstream>
#include <sstream>
#include "graph.h"
#include "GraphLine.h"

class GraphMaker {
public:
    GraphMaker();
    /***
     *
     * @return general graph with all the connections between stations
     */
    pair<Graph,unordered_map<string,int>> generalGraph();
    /***
     *
     * @return graph utilized in company functions(mostConvenientPath_s, mostConvenientPath_p)
     */
    GraphLine lineGraph();
    /***
     *
     * @param lat1
     * @param lon1
     * @param lat2
     * @param lon2
     * @return distance between two points
     */
    double haversine(double lat1, double lon1, double lat2, double lon2);
};


#endif //STCPPROJECT_GRAPHMAKER_H

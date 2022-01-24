//
// Created by josea on 16/01/2022.
//

#ifndef STCPPROJECT_COMPANY_H
#define STCPPROJECT_COMPANY_H


#include "GraphMaker.h"
#include "graph.h"

class Company {
private:
    Graph graph = Graph(2487,true);
    unordered_map<string, int> stopMap;
public:
    Company();
    void run();

    void showPath(list<int> res,list<list<string>> lines);
    void processKey(char choice);

    void showMenu();
    void showMainMenu();
    void shortestPathByDistance_s();

    string chooseStation();

    void shortestPathByStops_s();


    void cheapestPath_s();

    void mostConvenientPath_s();

    void walkingAndBusPath_s();

    void shortestPathByDistance_p();

    void shortestPathByStops_p();

    void cheapestPath_p();

    void walkingAndBusPath_p();

    void mostConvenientPath_p();

    pair<int, int> choosePosition();

    list<list<string>> generateLines(list<int> stops,Graph &g);
};


#endif //STCPPROJECT_COMPANY_H

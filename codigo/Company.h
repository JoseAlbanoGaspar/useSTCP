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
    /***
     *
     * @param res
     * @param lines
     *
     * Displays the desiered path
     */
    void showPath(list<int> res,list<list<string>> lines);
    /***
     *
     * @param choice
     *
     * Processes de input from user
     */
    void processKey(char choice);
    /***
     *
     * Displays the menu with the available actions
     */
    void showMenu();
    /***
     *
     * Displays the main menu with the option to use stations or coordenates 
     */
    void showMainMenu();
    /***
     * 
     * Displays the shortest path by distance/receiving stations
     */
    void shortestPathByDistance_s();
    /***
     * Processes the input station from user 
     * @return the name of the station
     * 
     */
    string chooseStation();
    /***
     * Displays the shortest path passing through the lowest number of stations possible/receiving stations
     */
    void shortestPathByStops_s();

    /***
     * Displays the shortest path but passing through the lowest number of zones possible/receiving stations
     */
    void cheapestPath_s();
    /***
     * Displays the shortest path but changing line the lowest number of times possible/receiving stations
     */
    void mostConvenientPath_s();
    /***
     * Displays the shortest path but considering walking a certain distance/receiving stations
     */
    void walkingAndBusPath_s();
    /***
     * Displays the shortest path by distance/receiving coordenates
     */
    void shortestPathByDistance_p();
    /***
     * Displays the shortest path by distance/receiving coordenates
     */
    void shortestPathByStops_p();
    /***
     * Displays the shortest path passing through the lowest number of stations possible/receiving coordenates
     */
    void cheapestPath_p();
    /***
     * Displays the shortest path but passing through the lowest number of zones possible/receiving coordenates
     */
    void walkingAndBusPath_p();
    /***
     * Displays the shortest path but considering walking a certain distance/receiving coordenates
     */
    void mostConvenientPath_p();
    /***
     * 
     * @return the coordenates processed from user input
     */

    pair<int, int> choosePosition();
    /***
     * 
     * @param stops 
     * @param g 
     * @return the generated lines associated with each transition
     */

    list<list<string>> generateLines(list<int> stops,Graph &g);
};


#endif //STCPPROJECT_COMPANY_H

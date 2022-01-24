//
// Created by josea on 16/01/2022.
//

#include "Company.h"

Company::Company() {

}
void Company::showMenu(){
    cout <<"1 - Shortest path (by distance)" << endl;
    cout <<"2 - Shortest path (by number of stops)" << endl;
    cout <<"3 - Cheapest path (less zones)" << endl;
    cout <<"4 - Most Convenient path (less line's exchange)" << endl;
    cout <<"5 - Bus + Walking path" << endl;
    cout <<"6 - Exit" << endl;
}
void Company::showMainMenu(){
    char choice = 'i';
    while(choice != 'q'){
        cout << "STCP PROJECT" << endl;
        cout << "stations  - s ||  position - p:"<<endl;
        cout << "Press q to exit"<<endl;
        cin >> choice;
        if(choice == 'q'){
            break;
        }
        processKey(choice);
    }
}
void Company::processKey(char choice){
    if(choice == 's')
    {
        while(choice != '6') {
            showMenu();
            cin >> choice;
            switch (choice) {
                case '1':
                    shortestPathByDistance_s();
                    break;
                case '2':
                    shortestPathByStops_s();
                    break;
                case '3':
                    cheapestPath_s();
                    break;
                case '4':
                    mostConvenientPath_s();
                    break;
                case '5':
                    walkingAndBusPath_s();
                    break;
                case '6':
                    break;
            }
        }
    }
    else if(choice == 'p')
    {
        while(choice != '6') {
            showMenu();
            cin >> choice;
            switch (choice) {
                case '1':
                    shortestPathByDistance_p();
                    break;
                case '2':
                    shortestPathByStops_p();
                    break;
                case '3':
                    cheapestPath_p();
                    break;
                case '4':
                    mostConvenientPath_p();
                    break;
                case '5':
                    walkingAndBusPath_p();
                    break;
                case '6':
                    break;
            }
        }
    }
}
string Company::chooseStation() {
    string station;
    cout << "Station code:";
    cin >> station;
    return station;
}

void Company::shortestPathByDistance_s(){
    string station1 = chooseStation();
    string station2 = chooseStation();
    pair<double,list<int>> res = graph.dijkstra_path(stopMap[station1],stopMap[station2]);
    list<list<string>> takenLines = generateLines(res.second,graph);
    showPath(res.second,takenLines);
    cout << endl << "The distance is: " << res.first << " km." << endl;
}
void Company::shortestPathByStops_s(){
    string station1 = chooseStation();
    string station2 = chooseStation();
    pair<int,list<int>> res = graph.bfs(stopMap[station1],stopMap[station2]);
    list<list<string>> takenLines = generateLines(res.second,graph);
    showPath(res.second,takenLines);
    cout << endl << "This path only passes through " << res.first << " stations." << endl;
}
void Company::cheapestPath_s(){
    string station1 = chooseStation();
    string station2 = chooseStation();
    pair<int,list<int>> res = graph.dijkstra_changeZone(stopMap[station1],stopMap[station2]);
    list<list<string>> takenLines = generateLines(res.second,graph);
    showPath(res.second,takenLines);
    cout << endl << "This paths only contains " << res.first << " different zones." << endl;
}
void Company::mostConvenientPath_s(){
    string station1 = chooseStation();
    string station2 = chooseStation();
    graph.findPath(stopMap[station1],stopMap[station2]);



}

void Company::walkingAndBusPath_s(){
    GraphMaker graphMaker;
    string station1 = chooseStation();
    string station2 = chooseStation();
    double dist;
    cout << "Max distance you want to walk:";
    cin >> dist;
    pair<Graph,unordered_map<string,int>> newGraph = graphMaker.generalGraph();
    newGraph.first.addWalkEdge(dist);
    pair<double,list<int>> res = newGraph.first.dijkstra_path(newGraph.second[station1],newGraph.second[station2]);
    list<list<string>> takenLines = generateLines(res.second,newGraph.first);
    showPath(res.second,takenLines);
    cout << endl << "The distance is: " << res.first << " km." << endl;

}

void Company::shortestPathByDistance_p() {
    GraphMaker graphMaker;
    pair<int,int> pos1 = choosePosition();
    pair<int,int> pos2 = choosePosition();
    list<int> initialNodes;
    list<int> finalNodes;
    for(int i = 1; i < 2487; i++){
        if(graphMaker.haversine(pos1.first,pos1.second,graph.getNodes()[i].latitiude,graph.getNodes()[i].longitude) < 0.3){
            initialNodes.push_back(i);
        }
    }
    for(int i = 1; i < 2487; i++){
        if(graphMaker.haversine(pos2.first,pos2.second,graph.getNodes()[i].latitiude,graph.getNodes()[i].longitude) < 0.3){
            finalNodes.push_back(i);
        }
    }
    pair<double,list<int>> answer = {LONG_MAX,{}};
    for(int i : initialNodes){
        for(int j : finalNodes){
            pair<double,list<int>> res = graph.dijkstra_path(i,j);
            if(res.first < answer.first)
                answer = res;
        }
    }
    list<list<string>> takenLines = generateLines(answer.second,graph);
    showPath(answer.second,takenLines);
    cout << endl << "The distance is: " << answer.first << " km." << endl;
}

void Company::shortestPathByStops_p() {
    GraphMaker graphMaker;
    pair<int,int> pos1 = choosePosition();
    pair<int,int> pos2 = choosePosition();
    list<int> initialNodes;
    list<int> finalNodes;
    for(int i = 1; i < 2487; i++){
        if(graphMaker.haversine(pos1.first,pos1.second,graph.getNodes()[i].latitiude,graph.getNodes()[i].longitude) < 0.3){
            initialNodes.push_back(i);
        }
    }
    for(int i = 1; i < 2487; i++){
        if(graphMaker.haversine(pos2.first,pos2.second,graph.getNodes()[i].latitiude,graph.getNodes()[i].longitude) < 0.3){
            finalNodes.push_back(i);
        }
    }
    pair<int,list<int>> answer = {LONG_MAX,{}};
    for(int i : initialNodes){
        for(int j : finalNodes){
            pair<int,list<int>> res = graph.bfs(i,j);
            if(res.first < answer.first)
                answer = res;
        }
    }
    list<list<string>> takenLines = generateLines(answer.second,graph);
    showPath(answer.second,takenLines);
    cout << endl << "This path only passes through " << answer.first << " stations." << endl;
}
void Company::cheapestPath_p() {
    GraphMaker graphMaker;
    pair<int,int> pos1 = choosePosition();
    pair<int,int> pos2 = choosePosition();
    list<int> initialNodes;
    list<int> finalNodes;
    for(int i = 1; i < 2487; i++){
        if(graphMaker.haversine(pos1.first,pos1.second,graph.getNodes()[i].latitiude,graph.getNodes()[i].longitude) < 0.3){
            initialNodes.push_back(i);
        }
    }
    for(int i = 1; i < 2487; i++){
        if(graphMaker.haversine(pos2.first,pos2.second,graph.getNodes()[i].latitiude,graph.getNodes()[i].longitude) < 0.3){
            finalNodes.push_back(i);
        }
    }
    pair<int,list<int>> answer = {LONG_MAX,{}};
    for(int i : initialNodes){
        for(int j : finalNodes){
            pair<int,list<int>> res = graph.dijkstra_changeZone(i,j);
            if(res.first < answer.first)
                answer = res;
        }
    }
    list<list<string>> takenLines = generateLines(answer.second,graph);
    showPath(answer.second,takenLines);
    cout << endl << "This paths only contains " << answer.first << " different zones." << endl;
}
void Company::walkingAndBusPath_p() {

}
void Company::mostConvenientPath_p() {

}
void Company::showPath(list<int> res,list<list<string>> lines){
    for(auto i : res)
        cout <<  " --> " + graph.getNodes()[i].code;
    cout << endl;
    for(auto l : lines){
        for(string line : l)
            cout << line << " ";
        cout << endl;
    }
}
void Company::run() {
    GraphMaker graphMaker;
    pair<Graph,unordered_map<string,int>> graphInfo = graphMaker.generalGraph();
    graph = graphInfo.first;
    stopMap = graphInfo.second;
    showMainMenu();

    /*pair<int,list<int>> res =  graph.dijkstra_changeZone(stopMap["FEUP2"],stopMap["PVC1"]);
    showPath(res.second);
    cout << endl;
    cout << "Passa por " <<res.first << " zonas";*/

}

pair<int, int> Company::choosePosition() {
    double latitude,longitude;
    cout << "POSITION:" << endl;
    cout << " Latitude:";
    cin >> latitude;
    cout << " Longitude:" << endl;
    cin >> longitude;
    return {latitude,longitude};

}

list<list<string>> Company::generateLines(list<int> stops, Graph &g) {
    list<list<string>> lines;
    int count = 0;
    auto it = stops.begin();
    while(count != stops.size()-1){
        int scr = *it;
        it++;
        int dest = *it;
        list<string> line = g.findEgde(scr,dest);
        lines.push_back(line);
        count++;
    }
    return lines;
}



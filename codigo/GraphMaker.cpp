//
// Created by josea on 16/01/2022.
//

#include <cmath>
#include "GraphMaker.h"

GraphMaker::GraphMaker() {

}
double GraphMaker::haversine(double lat1, double lon1,
                        double lat2, double lon2)
{
    // distance between latitudes
    // and longitudes
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

pair<Graph,unordered_map<string,int>> GraphMaker::generalGraph() {
    Graph g(2487,true);
    unordered_map<string,vector<string>> stopInfo;
    unordered_map<string,int> stopcode_nodeNr;
    int nodenr = 1;
    ifstream file("dataset/stops.csv");
    if (file.is_open())
    {
        cout << "Reading Stops File" << endl;
        string line;
        getline(file,line);
        while (getline(file, line))
        {
            vector<string> answer;  // string array to store the result
            stringstream string_stream(line);  // creating string stream object

            while(string_stream.good())   // loop will continue if string stream is error free
            {
                string a;
                getline( string_stream, a, ',' );   //calling getline fuction
                answer.push_back(a);
            }
            stopInfo[answer[0]] = {answer[1],answer[2],answer[3],answer[4]};
            stopcode_nodeNr[answer[0]] = nodenr;
            nodenr++;
        }
        file.close();
    }
    else{
        cout << "not open" << endl;
    }
    //ler todas as linhas
    vector<string> lines;
    ifstream fileLines("dataset/lines.csv");
    cout << "Reading Lines File" << endl;
    if (fileLines.is_open())
    {
        string line;
        getline(fileLines,line);
        while (getline(fileLines, line))
        {
            stringstream string_stream(line);  // creating string stream object

            string a; //a gets the code of the line
            getline( string_stream, a, ',' );   //calling getline fuction

            lines.push_back(a);
        }
        fileLines.close();
    }
    else{
        cout << "not open" << endl;
    }
    //read all lines to add the edges
    for(auto& lineCode : lines){
        for(int i = 0; i < 2; i++) {
            string path = "dataset/line_" +lineCode + "_" + to_string(i) +".csv";
            cout << "Reading " + path + " File" << endl;
            ifstream stoplines(path);
            if (stoplines.is_open()) {
                string line,previous;
                getline(stoplines, line); //skip number of stops
                getline(stoplines,previous);
                if(stoplines.peek()!=EOF){   // circular lines exist!
                    g.setSTCPProprieties(stopcode_nodeNr[previous],previous,stopInfo[previous][0],stopInfo[previous][1],stod(stopInfo[previous][2]),stod(stopInfo[previous][3]));
                    while(getline(stoplines,line)){
                        g.setSTCPProprieties(stopcode_nodeNr[line], line, stopInfo[line][0], stopInfo[line][1],
                                             stod(stopInfo[line][2]), stod(stopInfo[line][3]));
                        g.addEdge(stopcode_nodeNr[previous], stopcode_nodeNr[line],
                                  haversine(stod(stopInfo[previous][2]), stod(stopInfo[previous][3]),
                                            stod(stopInfo[line][2]), stod(stopInfo[line][3])), lineCode);

                        previous = line;
                    }
                    stoplines.close();
                }
            } else {
                cout << "not open" << endl;
            }
        }
    }

    return {g,stopcode_nodeNr};
}

Graph GraphMaker::zoneGraph() {
    return Graph(0);
}

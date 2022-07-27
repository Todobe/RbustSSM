#include "Graph.h"
#include <fstream>
#include <iostream>

Graph::Graph(string network_file) {
    ifstream networkFile;
    networkFile.open(network_file, ios::in);
    if (!networkFile.is_open()) {
        cout << "No such file: " << network_file << " or permission denied." << endl;
        exit(0);
    }
    networkFile>>nodeNum>>edgeNum;
    for(int i=0;i<nodeNum;i++) {
        To.push_back(vector<int>());
        EdgeWeight.push_back(vector<double>());
    }
    int u,v;
    double weight;
    for(int i=0;i<edgeNum;i++){
        networkFile>>u>>v>>weight;
        Edges.push_back(make_pair(u,v));
        Weight[make_pair(u,v)]=weight;
        To[u].push_back(v);
        EdgeWeight[u].push_back(weight);
    }

    networkFile.close();
}

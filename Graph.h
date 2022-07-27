
#ifndef ROBUSTSSM_GRAPH_H
#define ROBUSTSSM_GRAPH_H

#include <vector>
#include <string>
#include <map>

using namespace std;

class Graph{
public:
    int nodeNum, edgeNum;
    vector<pair<int, int> > Edges;
    map<pair<int,int> ,double> Weight;
    vector<vector<int> > To;
    vector<vector<double> > EdgeWeight;

    Graph(string);
};

#endif //ROBUSTSSM_GRAPH_H

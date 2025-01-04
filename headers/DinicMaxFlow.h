#ifndef DINIC_MAX_FLOW_H
#define DINIC_MAX_FLOW_H

#include "FileReader.h"
#include "LinkCutTree.h"
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>

struct Edge {
    int v;
    int flow;
    int C;
    int rev;
};

class DinicMaxFlow {
private:
    vector<vector<Edge>> adj;
    vector<int> level;
    int n;
    int S;
    int T;
    int maxFlow;
    
    bool BFS(int s, int t, int scale);
    int sendFlow(int u, int flow, int t, vector<int>& start);

public:
    DinicMaxFlow();
    ~DinicMaxFlow();
    int computeFlow(Grafo &g);
};

#endif
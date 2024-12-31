#include "FileReader.h"
// Implementacion del Algoritmo de Dinic aplicado Flujo Maximo para un Grafo Dirigido
#include <algorithm>
#include <list>
#include <vector>
#include <iostream>
#include <queue>
#include <climits>
#include <cstring>
#include <string>

struct Edge {
    int v;
    int flow;
    int C;
    int rev;
};

class DinicMaxFlow {
    public:
        Grafo currentBest;
        int maxFlow;

        // Constructor
        DinicMaxFlow();

        // Destructor
        ~DinicMaxFlow();

    private:
        vector<vector<Edge>> adj;
        vector<int> level;

        bool BFS(int s, int t);
        int sendFlow(int u, int flow, int t, vector<int> &start);

    public:
        // New method to compute multi-source / multi-sink flow
        int computeFlow(Grafo &g);
};
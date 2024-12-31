#include "DinicMaxFlow.h"
#include <algorithm>

// Constructor
DinicMaxFlow::DinicMaxFlow(){
    maxFlow = 0;
}

// Destructor
DinicMaxFlow::~DinicMaxFlow(){
    // Destructor
}

// Método para obtener el flujo máximo
// Implementación de Dinic para n vertices fuentes y m vertices sumideros

// Helper BFS
bool DinicMaxFlow::BFS(int s, int t) {
    fill(level.begin(), level.end(), -1);
    level[s] = 0;
    list<int> queue;
    queue.push_back(s);
    while(!queue.empty()){
        int u = queue.front(); 
        queue.pop_front();
        for(auto &e : adj[u]){
            if(level[e.v] < 0 && e.flow < e.C){
                level[e.v] = level[u] + 1;
                queue.push_back(e.v);
            }
        }
    }
    return level[t] >= 0;
}

// Mandar flujo
int DinicMaxFlow::sendFlow(int u, int flow, int t, vector<int> &start){
    // Si ya llegamos al sumidero, se regresa el flujo
    if(u == t) return flow;
    // Mientras haya aristas por revisar
    for(; start[u] < (int)adj[u].size(); start[u]++){
        Edge &e = adj[u][start[u]];
        
        if(level[e.v] == level[u] + 1 && e.flow < e.C){
            int curr_flow = min(flow, e.C - e.flow);
            int temp_flow = sendFlow(e.v, curr_flow, t, start);
            if(temp_flow > 0){
                e.flow += temp_flow;
                adj[e.v][e.rev].flow -= temp_flow;
                return temp_flow;
            }
        }
    }
    return 0;
}

// Compute flow for multiple sources/sinks
int DinicMaxFlow::computeFlow(Grafo &g){
    // Find max node index to size adjacency
    int maxNode = 0;
    for(auto &edge: g.aristas){
        maxNode = max(maxNode, max(edge[0], edge[1]));
    }
    // Create super-source (S) and super-sink (T)
    int S = maxNode + 1;
    int T = maxNode + 2;
    int n = T + 1;

    adj.assign(n, {}); 
    level.assign(n, -1);

    // Build adjacency from Grafo
    auto addEdge = [&](int u, int v, int capacity){
        Edge a = {v, 0, capacity, (int)adj[v].size()};
        Edge b = {u, 0, 0,       (int)adj[u].size()};
        adj[u].push_back(a);
        adj[v].push_back(b);
    };

    // Link super-source to all fuentes
    for(int src : g.fuentes){
        addEdge(S, src, INT_MAX);
    }

    // Link all sumideros to super-sink
    for(int snk : g.sumideros){
        addEdge(snk, T, INT_MAX);
    }

    // Add edges from Grafo
    for(auto &edge : g.aristas){
        addEdge(edge[0], edge[1], edge[2]);
    }

    // Dinic loop
    maxFlow = 0;
    while(BFS(S, T)){
        vector<int> start(n, 0);
        while(int flow = sendFlow(S, INT_MAX, T, start)){
            maxFlow += flow;
        }
    }

    // Store final graph as currentBest if desired
    currentBest = g;
    return maxFlow;
}
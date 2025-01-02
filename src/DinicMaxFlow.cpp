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
    queue<int> q;
    q.push(s);

    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i = 0; i < (int)adj[u].size(); i++){ // { changed code }
            Edge &e = adj[u][i];
            // Use link-cut tree to check capacity
            if(level[e.v] < 0 && e.flow < e.C){
                // Splay this edge's node
                lct.splay(edgeNodes[e.rev]); // example usage
                level[e.v] = level[u] + 1;
                q.push(e.v);
            }
        }
    }
    return level[t] >= 0;
}

// Mandar flujo
int DinicMaxFlow::sendFlow(int u, int flow, int t, vector<int> &start) {
    if(u == t) return flow;
    for(; start[u] < (int)adj[u].size(); start[u]++){
        Edge &e = adj[u][start[u]];
        if(level[e.v] == level[u] + 1 && e.flow < e.C){
            int curr_flow = min(flow, e.C - e.flow);
            int temp_flow = sendFlow(e.v, curr_flow, t, start);
            if(temp_flow > 0){
                e.flow += temp_flow;
                adj[e.v][e.rev].flow -= temp_flow;

                // Example of cut in link-cut tree
                lct.cut(edgeNodes[e.rev]); // { changed code }

                return temp_flow;
            }
        }
    }
    return 0;
}

int DinicMaxFlow::computeFlow(Grafo &g){
    // Find max node index including fuentes and sumideros
    int maxNode = 0;
    for(auto &edge : g.aristas){
        maxNode = max(maxNode, max(edge[0], edge[1]));
    }
    for(auto src : g.fuentes){
        maxNode = max(maxNode, src);
    }
    for(auto snk : g.sumideros){
        maxNode = max(maxNode, snk);
    }

    int S = maxNode + 1;
    int T = maxNode + 2;
    int n = T + 1;

    adj.assign(n, {});
    level.assign(n, -1);
    edgeNodes.clear(); // { changed code }

    auto addEdge = [&](int u, int v, int capacity){
        Edge a = {v, 0, capacity, (int)adj[v].size()};
        Edge b = {u, 0, 0,       (int)adj[u].size()};
        adj[u].push_back(a);
        adj[v].push_back(b);

        // Create nodes in link-cut tree
        LCTNode* forwardNode = new LCTNode(capacity);
        LCTNode* reverseNode = new LCTNode(0);

        edgeNodes.push_back(forwardNode);  // track forward
        edgeNodes.push_back(reverseNode);  // track reverse
    };

    // Connect super source/sink
    for(int src : g.fuentes){
        addEdge(S, src, INT_MAX);
    }
    for(int snk : g.sumideros){
        addEdge(snk, T, INT_MAX);
    }
    // Add edges from g
    for(auto &edge : g.aristas){
        addEdge(edge[0], edge[1], edge[2]);
    }

    maxFlow = 0;
    // Dinic loop
    while(BFS(S, T)){
        vector<int> start(n, 0);
        while(int flow = sendFlow(S, INT_MAX, T, start)){
            maxFlow += flow;
        }
    }
    currentBest = g;
    return maxFlow;
}
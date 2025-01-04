#include "../headers/DinicMaxFlow.h"

// Constructor - inicializa el flujo máximo a 0
DinicMaxFlow::DinicMaxFlow() {
    maxFlow = 0;
}

// Destructor vacío 
DinicMaxFlow::~DinicMaxFlow() {
}

// Realiza una búsqueda en anchura (BFS) para construir el grafo de niveles
bool DinicMaxFlow::BFS(int s, int t, int scale) {
    // Reinicia los niveles a -1
    fill(level.begin(), level.end(), -1);
    level[s] = 0; // El nivel de la fuente es 0
    
    queue<int> q;
    q.push(s);
    
    // BFS tradicional
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        
        // Para cada arista adyacente al nodo actual
        for(Edge &e : adj[u]) {
            // Si el nodo no ha sido visitado y hay capacidad residual
            if(level[e.v] < 0 && e.flow + scale < e.C) {
                level[e.v] = level[u] + 1; // Asigna nivel
                q.push(e.v);
            }
        }
    }
    
    // Retorna true si se llegó al sumidero
    return level[t] >= 0;
}

// Envía flujo a través de un camino encontrado
int DinicMaxFlow::sendFlow(int u, int flow, int t, vector<int>& start) {
    // Si llegamos al sumidero, retornamos el flujo
    if(u == t)
        return flow;
    
    // Para cada arista del nodo actual
    for(; start[u] < static_cast<int>(adj[u].size()); start[u]++) {
        Edge &e = adj[u][start[u]];
        
        // Si el nodo siguiente está en el siguiente nivel y hay capacidad
        if(level[e.v] == level[u] + 1 && e.flow < e.C) {
            // Calcula el flujo que podemos enviar
            int curr_flow = min(flow, e.C - e.flow);
            int temp_flow = sendFlow(e.v, curr_flow, t, start);
            
            // Si se pudo enviar flujo
            if(temp_flow > 0) {
                e.flow += temp_flow; // Aumenta el flujo
                adj[e.v][e.rev].flow -= temp_flow; // Actualiza el flujo residual
                return temp_flow;
            }
        }
    }
    
    return 0; // No se pudo enviar más flujo
}

// Método principal que calcula el flujo máximo
int DinicMaxFlow::computeFlow(Grafo &g) {
    // Encuentra el nodo con el índice más alto
    int maxNode = 0;
    for(const auto &edge : g.aristas) {
        maxNode = max(maxNode, max(edge[0], edge[1]));
    }
    
    // Agrega dos nodos extra para super-fuente y super-sumidero
    n = maxNode + 2;
    S = n - 2; // Super-fuente
    T = n - 1; // Super-sumidero
    
    // Inicializa las estructuras de datos
    adj.clear();
    adj.resize(n);
    level.resize(n);
    
    // Construye el grafo con las aristas originales
    for(const auto &edge : g.aristas) {
        int u = edge[0], v = edge[1], cap = edge[2];
        
        // Crea aristas forward y reverse para el flujo residual
        Edge forward{v, 0, cap, static_cast<int>(adj[v].size())};
        Edge reverse{u, 0, 0, static_cast<int>(adj[u].size())};
        
        adj[u].push_back(forward);
        adj[v].push_back(reverse);
    }
    
    // Conecta super-fuente con las fuentes
    for(int source : g.fuentes) {
        Edge forward{source, 0, INT_MAX, static_cast<int>(adj[source].size())};
        Edge reverse{S, 0, 0, static_cast<int>(adj[S].size())};
        adj[S].push_back(forward);
        adj[source].push_back(reverse);
    }
    
    // Conecta sumideros con super-sumidero
    for(int sink : g.sumideros) {
        Edge forward{T, 0, INT_MAX, static_cast<int>(adj[T].size())};
        Edge reverse{sink, 0, 0, static_cast<int>(adj[sink].size())};
        adj[sink].push_back(forward);
        adj[T].push_back(reverse);
    }
    
    // Implementa escalado binario para mejorar la eficiencia
    int maxCap = 0;
    for(const auto &edge : g.aristas) {
        maxCap = max(maxCap, edge[2]);
    }
    int scale = 1;
    while(scale <= maxCap) scale <<= 1;
    scale >>= 1;

    // Algoritmo principal de Dinic
    maxFlow = 0;
    while(scale > 0) { // Para cada escala
        while(BFS(S, T, scale)) { // Mientras exista un camino aumentante
            vector<int> start(n, 0);
            // Envía flujo por los caminos encontrados
            while(int flow = sendFlow(S, INT_MAX, T, start)) {
                maxFlow += flow;
            }
        }
        scale >>= 1; // Reduce la escala
    }
    return maxFlow;
}
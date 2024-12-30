#include "Grafo.h"
// Implementacion del Algoritmo de Dinic aplicado Flujo Maximo para un Grafo Dirigido

class DinicMaxFlow {
    public:
        Grafo currentBest;
        int maxFlow;

        // Constructor
        DinicMaxFlow();

        // Destructor
        ~DinicMaxFlow();

        // Método para obtener el flujo máximo
        int getMaxFlow();

};
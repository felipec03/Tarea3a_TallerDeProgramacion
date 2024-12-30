#include <iostream>
#include <vector>


using namespace std;

// Implementación de Grafo dirigido ponderado para representación de lista de adyacencia
// Objetivo: Resolver el problema del flujo máximo en una red de transporte para n fuentes y m sumideros
class Grafo {
public:
    // Lista de nodos sumideros
    vector<int> sumideros;
    // Lista de nodos fuente
    vector<int> fuentes;
    // 3 columnas que representan origen, destino y capacidas -> aristas con peso
    vector<vector<int>> aristas;
    
    // Constructor vacío
    Grafo();

    // Constructor con parámetros
    Grafo(vector<int> sumideros, vector<int> fuentes, vector<vector<int>> aristas);

    // Método para agregar una arista al grafo
    void agregarArista(int origen, int destino, int capacidad);

    // Método para obtener la capacidad de una arista
    int obtenerCapacidad(int origen, int destino);

    // Método para obtener la capacidad de una arista
    void modificarCapacidad(int origen, int destino, int capacidad);

    // Método para imprimir el grafo
    void imprimirGrafo();
};
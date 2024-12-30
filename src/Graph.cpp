#include "../headers/Grafo.h"

// Implementación de Grafo para representación de lista de adyacencia
// Objetivo: Resolver el problema del flujo máximo en una red de transporte

// Constructor
Grafo::Grafo() {
    // Inicialización de las listas
    sumideros = vector<int>();
    fuentes = vector<int>();
    aristas = vector<vector<int>>();
}

// Constructor con parámetros
Grafo::Grafo(vector<int> sumideros, vector<int> fuentes, vector<vector<int>> aristas) {
    // Inicialización de las listas
    this->sumideros = sumideros;
    this->fuentes = fuentes;
    this->aristas = aristas;
}

// Método para agregar una arista al grafo
void Grafo::agregarArista(int origen, int destino, int capacidad) {
    // Se agrega la arista al grafo
    aristas.push_back({origen, destino, capacidad});
}

// Método para obtener la capacidad de una arista
int Grafo::obtenerCapacidad(int origen, int destino) {
    // Se recorren las aristas
    for (int i = 0; i < static_cast<int>(aristas.size()); i++) {
        // Se verifica si la arista es la que se busca
        if (aristas[i][0] == origen && aristas[i][1] == destino) {
            // Se retorna la capacidad de la arista
            return aristas[i][2];
        }
    }
    // Si no se encuentra la arista, se retorna 0
    return 0;
}

// Método para modificar la capacidad de una arista
void Grafo::modificarCapacidad(int origen, int destino, int capacidad) {
    // Se recorren las aristas
    for (int i = 0; i < static_cast<int>(aristas.size()); i++) {
        // Se verifica si la arista es la que se busca
        if (aristas[i][0] == origen && aristas[i][1] == destino) {
            // Se modifica la capacidad de la arista
            aristas[i][2] = capacidad;
        }
    }
}  

// Método para imprimir el grafo
void Grafo::imprimirGrafo() {

    // Imprimir nodos fuentes
    cout << "Fuentes: ";
    for (int i = 0; i < static_cast<int>(fuentes.size()); i++) {
        cout << fuentes[i] << " ";
    }
    cout << endl;

    // Imprimir nodos sumideros
    cout << "Sumideros: ";
    for (int i = 0; i < static_cast<int>(sumideros.size()); i++) {
        cout << sumideros[i] << " ";
    }
    cout << endl;

    // Se recorren las aristas
    for (int i = 0; i < static_cast<int>(aristas.size()); i++) {
        // Se imprime la arista
        cout << aristas[i][0] << " -> " << aristas[i][1] << " : " << aristas[i][2] << endl;
    }
}
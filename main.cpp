#include "../headers/DinicMaxFlow.h"
#include <chrono>

int main(){
    string archivo;
    cout << "Ingrese el nombre del archivo: ";
    cin >> archivo;
    FileReader fr = FileReader(archivo);
    Grafo g = fr.read(archivo);


    // Imprimir nodos fuentes
    cout << "Nodos fuentes: " << endl;
    for(int i = 0; i < static_cast<int>(g.fuentes.size()); i++){
        cout << g.fuentes[i] << " ";
    }
    cout << endl;

    // Imprimir nodos sumideros
    cout << "Nodos sumideros: " << endl;
    for(int i = 0; i < static_cast<int>(g.sumideros.size()); i++){
        cout << g.sumideros[i] << " ";
    }  
    cout << endl;

    // Empenzar a contar el tiempo
    auto start = chrono::high_resolution_clock::now();

    DinicMaxFlow dinic = DinicMaxFlow();
    int maxFlow = dinic.computeFlow(g);


    // Imprime el flujo máximo
    cout << "El flujo máximo es: " << maxFlow << endl;

    // Tiempo total
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Tiempo total: " << elapsed.count() << " [ms]" << endl;
    return 0;
}
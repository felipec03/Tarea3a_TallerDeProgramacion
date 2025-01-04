#include "../headers/DinicMaxFlow.h"
#include <chrono>

int main(){
    string archivo;
    cout << "Ingrese el nombre del archivo: ";
    cin >> archivo;
    FileReader fr = FileReader(archivo);

    cout << "Leyendo archivo..." << endl;
    auto startLectura = chrono::high_resolution_clock::now();
    Grafo g = fr.read(archivo);
    
    auto endLectura = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedLectura = endLectura - startLectura;
    cout << "Tiempo de lectura: " << elapsedLectura.count() << " [s]" << endl;


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
    cout << "Tiempo total: " << elapsed.count() << " [s]" << endl;
    return 0;
}
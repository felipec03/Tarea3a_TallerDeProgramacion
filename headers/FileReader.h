#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Implementación de FileReader para lectura de archivos
// El formato de lectura es
// Primera fila: Lista de nodos sumideros
// Segunda fila: Lista de nodos fuente
// Tercera fila para abajo: o = origen, d = destino y c = capacidad.
using namespace std;
class FileReader {
public:
    // Constructor
    FileReader(string filename);

    // Destructor
    ~FileReader();

    // Método para leer el archivo
    Grafo read(string filename);
    
};
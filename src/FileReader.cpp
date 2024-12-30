#include "../headers/FileReader.h"

// Constructor
FileReader::FileReader(string filename){
    std::cout << "FileReader constructor called" << std::endl;
}

// Destructor
FileReader::~FileReader(){
    std::cout << "FileReader destructor called" << std::endl;
}

// Metodo para leer un archivo
Grafo FileReader::read(string filename) {
    Grafo grafo;
    ifstream file(filename);
    string line;

    // Check for errors
    if (!file.is_open()) {
        cout << "Error: No se pudo abrir el archivo" << endl;
        return grafo;
    }
    
    // Read sources (first line)
    getline(file, line);
    stringstream ss1(line);
    int source;
    while (ss1 >> source) {
        grafo.fuentes.push_back(source);
    }
    
    // Read sinks (second line)
    getline(file, line);
    stringstream ss2(line);
    int sink;
    while (ss2 >> sink) {
        grafo.sumideros.push_back(sink);
    }
    
    // Read edges (remaining lines)
    while (getline(file, line)) {
        stringstream ss3(line);
        int origen, destino, capacidad;
        ss3 >> origen >> destino >> capacidad;
        grafo.agregarArista(origen, destino, capacidad);
    }
    
    return grafo;
}


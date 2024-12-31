#include "../headers/FileReader.h"

int main(){
    string filename;
    cout << "Ingrese el nombre del archivo: ";
    cin >> filename;
    FileReader fr = FileReader(filename);

    Grafo grafo = fr.read(filename);
    grafo.imprimirGrafo();

    return 0;
}
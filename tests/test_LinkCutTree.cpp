#include "../headers/LinkCutTree.h"
#include <iostream>

// Imprimir conexión entre dos nodos
void printConnection(LinkCutTree& lct, LCTNode* u, LCTNode* v) {
    bool result = lct.connected(u, v);
    std::cout << "Nodos " << u->flowData << " anyd " << v->flowData 
              << " están " << (result ? "conectados" : "no conectados...") << std::endl;
}

int main() {

    // Se crea un arbol de enlaces y cortes
    LinkCutTree lct;
    
    // Crear nodos de prueba
    LCTNode* nodes[6];
    for(int i = 0; i < 6; i++) {
        nodes[i] = new LCTNode(i);
    }


    cout << "Enlaces iniciales" << endl;
    // Create initial tree structure
    lct.link(nodes[0], nodes[1]);
    lct.link(nodes[1], nodes[2]);
    lct.link(nodes[2], nodes[3]);
    
    // Probar conexiones
    printConnection(lct, nodes[0], nodes[3]);
    printConnection(lct, nodes[0], nodes[4]);

    cout << "Haciendo un nodo raíz" << endl;
    lct.makeRoot(nodes[3]);
    std::cout << "El nodo 3 es una raíz!" << std::endl;

    cout << "Haciendo más enlaces" << endl;
    lct.link(nodes[4], nodes[3]);
    lct.link(nodes[4], nodes[5]);
    printConnection(lct, nodes[0], nodes[5]);

    cout << "Cortando conexiones" << endl;
    lct.cut(nodes[2]);
    printConnection(lct, nodes[0], nodes[3]);
    printConnection(lct, nodes[4], nodes[5]);

    cout << "Buscando raíces..." << endl;
    for(int i = 0; i < 6; i++) {
        LCTNode* root = lct.findRoot(nodes[i]);
        std::cout << "Raíz del nodo " << i << " -> " << root->flowData << std::endl;
    }

    for(int i = 0; i < 6; i++) {
        delete nodes[i];
    }

    return 0;
}
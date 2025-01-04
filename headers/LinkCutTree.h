#include <bits/stdc++.h>
using namespace std;

// Estructura de un nodo en el árbol de enlaces y cortes
struct LCTNode {
    // Nodos hijos y padre, definicion recursiva
    LCTNode *left, *right, *parent;

    // Bandera para indicar si el nodo está invertido
    bool reversed;

    // Implementación cambiada, guarda el flujo en el nodo
    int flowData;

    // Para mejor balanceo se guarda tamaño de sub arbol
    int size; 
    
    // Constructor, aun que se rompe "orientación a objetos"
    // basta con generar la raiz
    LCTNode(int f) : left(nullptr), right(nullptr), parent(nullptr), 
                     reversed(false), flowData(f), size(1) {}

    // Metodos dentro de la estructura

    // Función para verificar si el nodo es raíz
    inline bool isRoot() const {
        return !parent || (parent->left != this && parent->right != this);
    }
    
    // Push para propagar la inversión
    inline void push() {
        if (reversed) {
            swap(left, right);
            if (left) left->reversed ^= true;
            if (right) right->reversed ^= true;
            reversed = false;
        }
    }
    
    // Actualizar tamaño del nodo
    inline void update() {
        size = 1;
        if (left) size += left->size;
        if (right) size += right->size;
    }
};

// Definición de arbol de enlaces y cortes
class LinkCutTree {
private:
    // Funciones privadas
    // Función para propagar la inversión
    void pushDown(LCTNode* x);
    // Función para actualizar el nodo
    void updateNode(LCTNode* x);
    
public:
    // Funciones públicas
    // Función para rotar un nodo
    void rotate(LCTNode* x);
    // Función para hacer zig-zig o zag-zag
    void splay(LCTNode* u);
    // Función para acceder a un nodo
    LCTNode* access(LCTNode* x);
    // Función para hacer raíz un nodo
    void makeRoot(LCTNode* x);
    // Función para enlazar dos nodos
    void link(LCTNode* u, LCTNode* v);
    // Función para cortar un nodo
    void cut(LCTNode* u);
    // Función para encontrar la raíz de un nodo
    LCTNode* findRoot(LCTNode* u);
    // Función para verificar si dos nodos están conectados
    bool connected(LCTNode* u, LCTNode* v);
};
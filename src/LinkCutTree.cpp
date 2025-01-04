#include "../headers/LinkCutTree.h"

// Función para propagar la inversión
void LinkCutTree::pushDown(LCTNode* x) {
    // Si el nodo no existe, no se hace nada
    if (!x) return;
    // Se propaga la inversión
    x->push();
}

// Función para actualizar el nodo
void LinkCutTree::updateNode(LCTNode* x) {
    if (!x) return;
    // Se actualiza el nodo
    x->update();
}

// Rotar un nodo
void LinkCutTree::rotate(LCTNode* x) {

    // Se obtienen los nodos padre y abuelo
    LCTNode* p = x->parent;
    LCTNode* g = p->parent;

    // Se actualizan los nodos
    if (!p->isRoot()) {
        // Si el abuelo no es raíz, se actualiza
        if (g->left == p) g->left = x;

        // Si no, se actualiza el nodo derecho
        else g->right = x;
    }
    
    // Guardar el hijo que será transferido
    LCTNode* m;
    
    // Si el nodo izquierdo es el nodo x
    if (p->left == x) {
        // Cambiar el hijo derecho del nodo x
        m = x->right;
        // Se actualiza el nodo derecho del nodo x
        x->right = p;
        // Al igual que el hijo izquierdo del nodo padre
        p->left = m;
    } else {
        // Cambiar el hijo izquierdo del nodo x
        m = x->left;
        x->left = p;
        p->right = m;
    }
    
    // Actualizar padres
    x->parent = g;
    p->parent = x;

    // Si el nodo m existe, se actualiza el padre
    if (m) m->parent = p;
    p->update();
    x->update();
}

// Splay en español es "desplegar", "abrir"
// En el fondo se hace un zig-zig o zag-zag
void LinkCutTree::splay(LCTNode* u) {

    // Si no existe, no ahce nada
    if (!u) return;
    
    // Mientras no sea raíz
    while (!u->isRoot()) {
        // Se obtienen los nodos padre y abuelo
        LCTNode* p = u->parent;
        LCTNode* g = p->parent;
        
        // Si no es raíz, se hace push
        if (!p->isRoot()) pushDown(g);
        pushDown(p);
        pushDown(u);
        
        if (!p->isRoot()) {
            // Zig-zig o zag-zag
            if ((g->left == p) == (p->left == u)) 
                rotate(p);
            // Zig-zag
            else 
                rotate(u);
        }
        // Rotar el nodo u
        rotate(u);
    }
    pushDown(u);
}

// Acceder a un nodo
LCTNode* LinkCutTree::access(LCTNode* x) {
    LCTNode* last = nullptr;
    LCTNode* y = x;
    
    // Mientras exista un nodo
    while (y) {
        // Desplegar el nodo
        splay(y);
        // Se actualiza el nodo derecho
        y->right = last;
        y->update();
        last = y;
        y = y->parent;
    }
    
    splay(x);
    return last;
}

// Hacer raíz un nodo
void LinkCutTree::makeRoot(LCTNode* x) {
    access(x);
    // Se invierte el nodo
    x->reversed ^= true;
}

// Enlazar dos nodos
void LinkCutTree::link(LCTNode* u, LCTNode* v) {
    makeRoot(u);
    u->parent = v;
}

// Cortar un nodo
void LinkCutTree::cut(LCTNode* u) {
    access(u);
    if (u->left) {
        u->left->parent = nullptr;
        u->left = nullptr;
        u->update();
    }
}

// Encontrar la raíz de un nodo
LCTNode* LinkCutTree::findRoot(LCTNode* u) {
    access(u);
    while (u->left) {
        pushDown(u);
        u = u->left;
    }
    access(u);
    return u;
}

// Verificar si dos nodos están conectados
bool LinkCutTree::connected(LCTNode* u, LCTNode* v) {
    // SI son iguales, estan conectados
    if (u == v) return true;
    // Se accede a los nodos
    access(u); access(v);
    // Se verifica si el nodo u tiene padre
    return u->parent != nullptr;
}
#include "LinkCutTree.h"

void LinkCutTree::rotate(LCTNode* x) {
    LCTNode* p = x->parent;
    LCTNode* g = p ? p->parent : nullptr;
    if(p->left == x) {
        p->left = x->right;
        if(x->right) x->right->parent = p;
        x->right = p;
    } else {
        p->right = x->left;
        if(x->left) x->left->parent = p;
        x->left = p;
    }
    p->parent = x;
    if(g) {
        if(g->left == p) g->left = x; else g->right = x;
    }
    x->parent = g;
}

// Expose: bring node u to root
void LinkCutTree::splay(LCTNode* u) {
    while(u->parent) {
        LCTNode* p = u->parent;
        LCTNode* g = p->parent;
        if(g) rotate((g->left == p) == (p->left == u) ? p : u);
        rotate(u);
    }
}

// Example method to link and cut in your flow algorithm
void LinkCutTree::link(LCTNode* u, LCTNode* v) {
    // Make v parent of u, adjusting structure
    splay(u);
    splay(v);
    u->parent = v;
}

// Cut operation
void LinkCutTree::cut(LCTNode* u) {
    // Splay and separate from parent
    splay(u);
    if(u->left) {
        u->left->parent = nullptr;
        u->left = nullptr;
    }
}
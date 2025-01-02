#include <bits/stdc++.h>
using namespace std;

struct LCTNode {
    LCTNode *left, *right, *parent;
    bool reversed;
    int flowData; // store edge capacity/flow info

    LCTNode(int f) : left(nullptr), right(nullptr), parent(nullptr), reversed(false), flowData(f) {}
};

class LinkCutTree{
    public:
        void rotate(LCTNode* x);
        void splay(LCTNode* u);
        void link(LCTNode* u, LCTNode* v);
        void cut(LCTNode* u);
};
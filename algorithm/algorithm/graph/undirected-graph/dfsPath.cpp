#include "dfsPath.h"

DfsPaths::DfsPaths(UndirectedGraphWithoutWeight G, int s): marked(G.V(), false), edgeTo(G.V(), -1), source(s) {
    if (s < 0 || s >= G.V()) return;
    dfs(G, s);
}

bool DfsPaths::HasPathTo(int v) const {
    if(v < 0 || v >= (int)this->marked.size()) return false;
    return this->marked[v];
}

std::vector<int> DfsPaths::PathTo(int v) const {
    std::vector<int> path;
    if(!HasPathTo(v)) return path;

    for(int x = v; x != this->source; x = this->edgeTo[x]) {
        path.push_back(x);
    }
    path.push_back(this->source);
    return path;
}

void DfsPaths::dfs(UndirectedGraphWithoutWeight G, int v) {
    this->marked[v] = true;
    for (const Edge& w : G.Adj(v)) {
        if (!this->marked[w.Dest()]) {
            this->edgeTo[w.Dest()] = v;
            dfs(G, w.Dest());
        }
    }
}
#include <algorithm>
#include "dfs_path.h"

DfsPaths::DfsPaths(const UndirectedGraph& G, int s): marked_(G.V(), false), edge_to_(G.V(), -1), source_(s) {
    if (s < 0 || s >= G.V()) return;
    dfs(G, s);
}

bool DfsPaths::HasPathTo(int v) const {
    if(v < 0 || v >= (int)this->marked_.size()) return false;
    return this->marked_[v];
}

std::vector<int> DfsPaths::PathTo(int v) const {
    std::vector<int> path;
    if(!HasPathTo(v)) return path;

    for(int x = v; x != this->source_; x = this->edge_to_[x]) {
        path.push_back(x);
    }
    path.push_back(this->source_);
    return path;
}

void DfsPaths::dfs(const UndirectedGraph& G, int v) {
    this->marked_[v] = true;
    auto pair = G.Adj(v);
    std::for_each(pair.first, pair.second, [&, v](const Edge& w){
        if (!marked_[w.Dest()]) {
            edge_to_[w.Dest()] = v;
            dfs(G, w.Dest());
        }
    });
}
#include <algorithm>
#include "dfs_search.h"

DfsSearch::DfsSearch(const UndirectedGraph& graph, int s): marked_(graph.V(), false), count_(0), source_(s) {
    dfs(graph, s);
}

bool DfsSearch::Marked(int v) const {
    return this->marked_[v];
}

int DfsSearch::Count() const {
    return this->count_;
}

void DfsSearch::dfs(const UndirectedGraph& G, int v) {
    this->marked_[v]=true;
    this->count_++;
    auto pair = G.Adj(v);
    std::for_each(pair.first, pair.second, [&](const Edge& w){
        if (!marked_[w.Dest()]) {
            dfs(G, w.Dest());
        }
    });
}
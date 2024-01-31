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

void DfsSearch::dfs(const UndirectedGraph& graph, int v) {
    this->marked_[v]=true;
    this->count_++;
    for (const Edge& w : graph.Adj(v)) {
        if (!this->marked_[w.Dest()]) {
            dfs(graph, w.Dest());
        }
    }
}
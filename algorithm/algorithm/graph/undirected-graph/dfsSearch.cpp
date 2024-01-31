#include "dfsSearch.h"

DfsSearch::DfsSearch(const UndirectedGraphWithoutWeight& graph, int s): marked(graph.V(), false), count(0), source(s) {
    dfs(graph, s);
}

bool DfsSearch::Marked(int v) const {
    return this->marked[v];
}

int DfsSearch::Count() const {
    return this->count;
}

void DfsSearch::dfs(const UndirectedGraphWithoutWeight& graph, int v) {
    this->marked[v]=true;
    this->count++;
    for (const Edge& w : graph.Adj(v)) {
        if (!this->marked[w.Dest()]) {
            dfs(graph, w.Dest());
        }
    }
}
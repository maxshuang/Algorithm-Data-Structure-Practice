#pragma once
#include <vector>
#include "undirected_graph.h"

class DfsSearch {
//
// behavior
//
public:
    DfsSearch(const UndirectedGraph& graph, int s);
    bool Marked(int v) const;
    int Count() const;
private:
    void dfs(const UndirectedGraph& graph, int v);

//
//  implementation
//
private:
    std::vector<bool> marked_;
    int count_;
    const int source_;
};
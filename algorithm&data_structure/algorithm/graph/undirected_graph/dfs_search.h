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
    // Time Complexity: O(V+E)
    // Space Complexity: O(V)
    void dfs(const UndirectedGraph& graph, int v);
//
//  implementation
//
private:
    std::vector<bool> marked_;
    int count_;
    const int source_;
};
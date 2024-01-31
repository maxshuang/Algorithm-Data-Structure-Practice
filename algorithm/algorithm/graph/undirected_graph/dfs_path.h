#pragma once
#include <vector>
#include "undirected_graph.h"

class DfsPaths{
public:
    DfsPaths(const UndirectedGraph& G, int s);
    bool HasPathTo(int v) const;
    std::vector<int> PathTo(int v) const;
private:
    void dfs(const UndirectedGraph& G, int v);
private:
    std::vector<bool> marked_;
    std::vector<int> edge_to_;
    int source_;
};
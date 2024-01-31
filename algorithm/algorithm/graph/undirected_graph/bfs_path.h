#pragma once
#include <vector>
#include "undirected_graph.h"


class BfsPaths{
public: 
    BfsPaths(const UndirectedGraph& G, int s);
    bool HasPathTo(int v) const;
    std::vector<int> PathTo(int v) const;
private:
    void bfs(const UndirectedGraph& G, int v);
private:
    std::vector<bool> marked_;
    std::vector<int> edge_to_;
    int source_;
};
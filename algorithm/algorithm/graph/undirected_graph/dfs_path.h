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
    // 所有点都被访问一次，这里就是一个 spanning tree，edge_to_ 存储的是指向该节点的源节点
    // 本质上是一个树状树组
    std::vector<int> edge_to_;
    int source_;
};
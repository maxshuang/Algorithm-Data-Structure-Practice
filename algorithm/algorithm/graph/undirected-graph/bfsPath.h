#pragma once
#include <vector>
#include "undirectGraphWithoutWeight.h"


class BfsPaths{
public: 
    BfsPaths(UndirectedGraphWithoutWeight G, int s);
    bool HasPathTo(int v) const;
    std::vector<int> PathTo(int v) const;
private:
    void bfs(UndirectedGraphWithoutWeight G, int v);
    std::vector<bool> marked;
    std::vector<int> edgeTo;
    int source;
};
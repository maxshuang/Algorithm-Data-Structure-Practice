#pragma once
#include <vector>
#include "undirectGraphWithoutWeight.h"

class DfsSearch {
//
// behavior
//
public:
    DfsSearch(const UndirectedGraphWithoutWeight& graph, int s);
    bool Marked(int v) const;
    int Count() const;
private:
    void dfs(const UndirectedGraphWithoutWeight& graph, int v);

//
//  implementation
//
private:
    std::vector<bool> marked;
    int count;
    const int source;
};
#include <algorithm>
#include "undirected_graph.h"

class ConnectedComponent
{
public:
    ConnectedComponent(const UndirectedGraph &G) : marked_(G.V(), false), index_(G.V(), -1), count_(0) { dfs(G); }
    bool Connected(int v, int w) const { return index_[v] == index_[w]; }
    int Count() const { return count_; }
    int Id(int v) const { return index_[v]; }

private:
    // Time Complexity: O(V+E)
    // Space Complexity: O(V)
    // Union-Find can also find the connected component, and it's faster since it doesn't need to construct the Graph first
    // DFS can also solve the problems of "Is the graph acyclic?" and "Is the graph bipartite?"
    void dfs(const UndirectedGraph &G);
    void dfs_recur(const UndirectedGraph &G, int v);

private:
    std::vector<bool> marked_;
    std::vector<int> index_;
    int count_;
};

void ConnectedComponent::dfs(const UndirectedGraph &G)
{
    for (int i = 0; i < G.V(); ++i)
    {
        if (!marked_[i])
        {
            ++count_;
            dfs_recur(G, i);
        }
    }
}

void ConnectedComponent::dfs_recur(const UndirectedGraph &G, int v)
{
    marked_[v] = true;
    index_[v] = count_;

    auto pair = G.Adj(v);
    std::for_each(pair.first, pair.second, [&](const Edge &w)
                  {
        if(!marked_[w.Dest()]) {
            dfs_recur(G, w.Dest());
        } });
}
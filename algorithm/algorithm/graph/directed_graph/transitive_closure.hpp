#include "digraph.hpp"
#include "direct_DFS.hpp"

// All-pairs reachability. Given a digraph, support queries of the form Is there a
// directed path from a given vertex v to another given vertex w?

// Problem abstraction:
// Definition. The transitive closure of a digraph
// G is another digraph with the same set of vertices, but with an edge from v to w in the transitive closure if and only if w is reachable from
// v in G.
// 简单说就是所以可达节点对都会拥有一条直连边的图
// Time Complexity: O(V*(V+E)), Space Complexity: O(V*V)

class TransitiveClosure
{
public:
    TransitiveClosure(const Digraph &g)
    {
        for (int i = 0; i < g.V(); ++i)
            dfs_.push_back(DirectDFS(g, i));
    }
    bool Reachable(int v, int w) const
    {
        return dfs_[v].Connected(w);
    }

private:
    std::vector<DirectDFS> dfs_;
};
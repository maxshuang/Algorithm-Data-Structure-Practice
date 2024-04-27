#include <algorithm>
#include "digraph.hpp"

class DirectDFS {
public:
    DirectDFS(const Digraph& g, int v): marked_(g.V(), false) { dfs(g, v); } 
    bool Connected(int w) const { return marked_[w]; }

private:
    void dfs(const Digraph& g, int v) {
        marked_[v]=true;
        auto pair=g.Adj(v);
        std::for_each(pair.first, pair.second, [&](const Edge& e){
            if(!marked_[e.Dest()]) {
                dfs(g, e.Dest());
            }
        });
    }

private:
    std::vector<bool> marked_;
};
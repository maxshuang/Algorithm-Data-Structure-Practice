#include <vector>
#include "undirected_graph.h"

class Cycle
{
public:
    Cycle(const UndirectedGraph &graph) : marked_(graph.V(), false), edge_to_(graph.V(), -1), has_cycle_(false) { dfs(graph); }
    bool HasCycle() const { return has_cycle_; }
    std::vector<int> GetCycle() const { return cycle_; }

private:
    void dfs(const UndirectedGraph &g)
    {
        for (int i = 0; i < g.V(); ++i)
        {
            if (!has_cycle_ && !marked_[i])
            {
                // source and destination is itself
                dfs_recur(g, i, i);
            }
        }
    }
    void dfs_recur(const UndirectedGraph &g, int v, int from)
    {
        if (has_cycle_)
            return;

        // add v to path
        edge_to_[v] = from;
        marked_[v] = true;

        auto pair = g.Adj(v);
        std::for_each(pair.first, pair.second, [&](const Edge &e)
                      {
            if(has_cycle_) return;

            if(!marked_[e.Dest()]) { 
                dfs_recur(g, e.Dest(), e.Src());
            }else if(from != e.Dest()){
                // because edge of undirected graph is bidirected, 
                // so if we find out this edge is not the original edge, 
                // we know it has a cycle.
                // [NOTE]: tricky here, it's better to use the edge_to_ to judge the cycle for more clear intention
                // since it's the undirected graph, from != e.Dest() is enough here
                has_cycle_=true;
                // construct a cycle
                edge_to_[e.Dest()]=e.Src();
                get_cycle(e.Src());
            } });

        // revert back
        edge_to_[v] = -1;
    }

    void get_cycle(int v)
    {
        cycle_.push_back(v);
        int w = v;
        while (edge_to_[w] != v)
        {
            cycle_.push_back(edge_to_[w]);
            w = edge_to_[w];
        }
    }

private:
    // for dfs
    std::vector<int> marked_;
    std::vector<int> edge_to_;
    std::vector<int> cycle_;
    bool has_cycle_;
};

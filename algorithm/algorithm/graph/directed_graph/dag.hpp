#ifndef DIRECT_GRAPH_DAG_
#define DIRECT_GRAPH_DAG_

#include <vector>
#include <algorithm>
#include "digraph.hpp"

class DAG
{
public:
    explicit DAG(const Digraph &G);
    bool HasCycle() const;
    std::vector<int> Cycle() const;

private:
    void dfs(const Digraph &G);
    void dfs_recur(const Digraph &G, int v);
    void get_cycle(int v);

private:
    std::vector<int> cycle_;
    // edge_to is for the cycle detection
    std::vector<int> edge_to_;
    // marked_ is for the dfs traversal
    std::vector<bool> marked_;
    bool has_cycle_;
};

DAG::DAG(const Digraph &G) : edge_to_(G.V(), -1), marked_(G.V(), false), has_cycle_(false) { dfs(G); }

bool DAG::HasCycle() const { return has_cycle_; }

std::vector<int> DAG::Cycle() const { return cycle_; }

void DAG::dfs(const Digraph &G)
{
    for (int i = 0; i < G.V(); ++i)
    {
        if (!marked_[i])
        {
            dfs_recur(G, i);
        }
    }
}

void DAG::dfs_recur(const Digraph &G, int v)
{
    marked_[v] = true;
    auto pair = G.Adj(v);
    std::for_each(pair.first, pair.second, [&](const Edge &e)
                  {
        if(!marked_[e.Dest()]) {
            // put it into the cycle path
            edge_to_[e.Dest()]=e.Src();
            dfs_recur(G, e.Dest());
            // reverse back
            edge_to_[e.Dest()]=-1;
        }else if(edge_to_[e.Dest()]!=-1){
            // hit the cycle
            has_cycle_=true;
            // construct the cycle
            edge_to_[e.Dest()]=e.Src();
            get_cycle(e.Src());
        } });
}

void DAG::get_cycle(int v)
{
    cycle_.push_back(v);
    int w = v;
    while (edge_to_[w] != v)
    {
        cycle_.push_back(edge_to_[w]);
        w = edge_to_[w];
    }
}

#endif
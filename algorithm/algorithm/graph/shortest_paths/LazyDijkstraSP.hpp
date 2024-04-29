#pragma once
#include <queue>
#include <climits>
#include <algorithm>
#include "directed_graph/digraph.hpp"
#include "edge_comp.hpp"

// Lazy Dijkstra shortest path will relax every edge untill there are no eligible edges

class LazyDijkstraSP
{
public:
    LazyDijkstraSP(const Digraph &g, int s) : src_(s), edge_to_(g.V()), dist_to_(g.V(), std::numeric_limits<double>::infinity())
    {
        dist_to_[s] = 0.0;
        visit(g, s);

        while (!pq_.empty())
        {
            auto e = pq_.top();
            pq_.pop();
            relax(g, e);
        }
    }

    double DistTo(int v) const { return dist_to_[v]; }

    bool HasPathTo(int v) const { return !std::isinf(dist_to_[v]); }

    std::vector<Edge> PathTo(int v) const
    {
        std::vector<Edge> res;
        while (v != src_)
        {
            res.push_back(edge_to_[v]);
            v = edge_to_[v].Src();
        }

        return res;
    }

private:
    void visit(const Digraph &g, int v)
    {
        auto pair = g.Adj(v);
        std::for_each(pair.first, pair.second, [&](const Edge &e)
                      { pq_.push(e); });
    }

    void relax(const Digraph &g, const Edge &e)
    {
        double dist = dist_to_[e.Src()] + e.Weight();
        if (dist < dist_to_[e.Dest()])
        {
            dist_to_[e.Dest()] = dist;
            edge_to_[e.Dest()] = e;
            visit(g, e.Dest());
        }
    }

private:
    int src_;
    std::priority_queue<Edge, std::vector<Edge>, EdgeComp> pq_;
    // shortest path tree
    std::vector<Edge> edge_to_;
    std::vector<double> dist_to_;
};
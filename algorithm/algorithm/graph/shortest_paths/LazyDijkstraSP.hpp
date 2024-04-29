#pragma once
#include <priority_queue>
#include <climits>
#include <algorithm>
#include "directed_graph/digraph.hpp"
#include "edge_comp.hpp"

// Lazy Dijkstra shortest path will relax every edge untill there are no eligible edges

#if 0

class LazyDijkstraSP
{
public:
    ShortestPath(const Digraph &g, int s) : edge_to(g.V()), dist_to_(g.V(), std::numeric_limits<double>::infinity())
    {
        visit(0);

        // ??? When will it stop? Why we need the edge with smallest edge??
        while (!pq_.empty())
        {
            auto e = pq_.top();
            pq_.pop();
            double dist = dist_to_[e.Src()] + e.Weight();
            if (dist < dist_to_[e.Dest()])
            {
                relax(e);
                visit(g, e.Dest());
            }
        }
    }

    double DistTo(int v) const {}
    bool hasPathTo(int v) const {}
    std::vector<Edge> PathTo(int v) const {}

private:
    void visit(const Digraph &g, int v)
    {
        auto pair = g.Adj(v);
        std::for_each(pair.first, pair.second, [&](const Edge &e)
                      { pq_.push(e); });
    }

    void relax(const Edge &e)
    {
        dist_to_[e.Dest()] = dist;
        edge_to_[e.Dest()] = e.Src();
    }

private:
    std::priority_queue<Edge, EdgeComp> pq_;
    // shortest path tree
    std::vector<Edge> edge_to_;
    std::vector<double> dist_to_;
};

#endif
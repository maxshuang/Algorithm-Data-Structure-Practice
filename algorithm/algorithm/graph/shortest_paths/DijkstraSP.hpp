#pragma once
#include <algorithm>
#include <limits>
#include "directed_graph/digraph.hpp"
#include "index_priority_queue.hpp"
#include "edge_comp.hpp"

// Assume:
// 1. All edges' weight is non-negative
// 2. graph has circles or not
// => for a shortest path of <s, t>, all subpaths are shortest path or it can't be the shortest path

// Core Problem: Why it will converges to the shortest path?
// Because the weight is non-negative and all subpaths are also the shortest paths,
// so we can use greedy algorithm to select the vertice with shortest path from source at each round.
// 这种 greedy algorithm 成立的前提是： 权值非负，所以一个路径上的权值是单调递增的，可以一直选择最小的 dist_to_[v]

class DijkstraSP
{
public:
    DijkstraSP(const Digraph &g, int s) : src_(s), edge_to_(g.V()), dist_to_(g.V(), std::numeric_limits<double>::infinity()), pq_(g.V())
    {
        dist_to_[s] = 0.0;
        pq_.Insert(s, 0.0);

        while (!pq_.IsEmpty())
        {
            auto i = pq_.Pop();
            visit(g, i);
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
                      { relax(e); });
    }

    void relax(const Edge &e)
    {
        double dist = dist_to_[e.Src()] + e.Weight();
        if (dist < dist_to_[e.Dest()])
        {
            edge_to_[e.Dest()] = e;
            dist_to_[e.Dest()] = dist;
            if (pq_.ContainsIndex(e.Dest()))
                pq_.Change(e.Dest(), dist);
            else
                pq_.Insert(e.Dest(), dist);
        }
    }

private:
    int src_;
    std::vector<Edge> edge_to_;
    std::vector<double> dist_to_;
    // non-tree vertice -> shortest path from source to non-tree vertice
    IndexPriorityQueue<double, std::greater<double>> pq_;
};
#pragma once
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
#include "directed_graph/digraph.hpp"

// Bellman ford is an algorithm for finding the shortest path tree in a digraph without negative cycle.
// The digraph may have negative edge weight and positive cycles.
// 1. unreachable vertices from source: infinity
// 2. reachable vertices on negative cycles: -infinity
// 3. simple shortest path: spt

// The algorithm itself is interesting, for any simple shortest path [s->v1->v2,...,->t]
// the relax operation in any round can relax at least one vertice in spt because the subpath in shortest path is also the shortest path no matter the weight is positive or negative
// or it's not the shortest path
// Time Complexity: O(V*E), Space Complexity: O(V)

class LazyBellmanFordSP
{
public:
    LazyBellmanFordSP(const Digraph &g, int s) : src_(s), edge_to_(g.V()), dist_to_(g.V(), std::numeric_limits<double>::infinity())
    {
        dist_to_[s] = 0.0;
        // for any digraph without negative cycles, it will converge to spt after V round
        for (int r = 0; r < g.V(); ++r)
        {
            for (int v = 0; v < g.V(); ++v)
            {
                auto pair = g.Adj(v);
                std::for_each(pair.first, pair.second, [&](const Edge &e)
                              {
                     if(e.Weight()+dist_to_[e.Src()] < dist_to_[e.Dest()]) {
                        edge_to_[e.Dest()]=e;
                        dist_to_[e.Dest()]=e.Weight()+dist_to_[e.Src()];
                     } });
            }
        }

        findNegativeCycle();
    }

    bool HasNegativeCycle() const { return has_negative_cycle_; }

    double DistTo(int v) const
    {
        if (!has_negative_cycle_ || !isNegativeCycleVertice(v))
            return dist_to_[v];
        else
            return -std::numeric_limits<double>::infinity();
    }

    bool HasPathTo(int v) const
    {
        if (!has_negative_cycle_ || !isNegativeCycleVertice(v))
            return !std::isinf(dist_to_[v]);

        return false;
    }

    std::vector<Edge> PathTo(int v) const
    {
        if (HasPathTo(v))
        {
            std::vector<Edge> res;
            while (v != src_)
            {
                res.push_back(edge_to_[v]);
                v = edge_to_[v].Src();
            }
            return res;
        }

        return std::vector<Edge>{};
    }

private:
    void findNegativeCycle()
    {
        std::vector<bool> marked(edge_to_.size(), false);
        int negative_cycle_vertice = -1;
        for (int i = 0; i < (int)edge_to_.size() && !has_negative_cycle_; ++i)
        {
            if (marked[i])
                continue;
            int w = i;
            while (w != -1)
            {
                marked[w] = true;
                w = edge_to_[w].Src();
                if (w == i)
                {
                    has_negative_cycle_ = true;
                    negative_cycle_vertice = i;
                    break;
                }
            }
        }

        if (has_negative_cycle_)
        {
            // get negative cycle
            int w = negative_cycle_vertice;
            while (edge_to_[w].Src() != negative_cycle_vertice)
            {
                negative_cycle_.push_back(edge_to_[w]);
                w = edge_to_[w].Src();
            }
            negative_cycle_.push_back(edge_to_[w]);
        }
    }

    // [NOTE]: O(N) implementation here
    bool isNegativeCycleVertice(int v) const
    {
        for (const auto &e : negative_cycle_)
        {
            if (e.Src() == v)
                return true;
        }
        return false;
    }

private:
    int src_;
    std::vector<Edge> edge_to_;
    std::vector<double> dist_to_;
    bool has_negative_cycle_;
    std::vector<Edge> negative_cycle_;
};
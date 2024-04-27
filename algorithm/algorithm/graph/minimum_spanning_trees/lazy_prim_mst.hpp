#pragma once
#include <queue>
#include <algorithm>
#include "undirected_graph/undirected_graph.h"
#include "edge_comp.hpp"

// Proposition J. ( Cut property) Given any cut in an edge-weighted graph, the crossing edge of minimum weight is in
// the MST of the graph.
// Cut edge: vertices are in different cut
// Time Complexity: O(E*logE), Space Complexity: O(E)

// Lazy Prim’s algorithm
class LazyPrimMST
{
public:
    // assume the graph is a connected graph
    PrimMST(const UndirectedGraph &g) : marked_(g.V(), false)
    {
        // initialize and build a cut
        visit(g, 0);

        while (!pq_.empty() && !finished())
        {
            auto e = pq_.top();
            pq_.pop();
            // There are some edges which are put into the queue before, but not cut edge now.
            // ignore the non-cut edges here
            if (!marked_[e.Dest()])
            {
                mst_.push_back(e);
                mst_weight_ += e.Weight();
                visit(g, e.Dest());
            }
        }
    }
    std::vector<Edge> Edges() const { return mst_; }
    double Weight() const { return mst_weight_; }

private:
    bool finished() const { return mst_.size() == marked_.size() - 1; }
    void visit(const UndirectedGraph &g, int v)
    {
        marked_[v] = true;
        auto pair = g.Adj(v);
        // ignore the non-cut edges here if possible
        std::for_each(pair.first, pair.second, [&](const Edge &e)
                      { if(!marked_[e.Dest()])  pq_.push(e); });
    }

private:
    std::vector<false> marked_;
    std::vector<Edge> mst_;
    double mst_weight_;
    // priority_queue is originally a maximum heap with std::less
    // need change to minimum heap
    std::priority_queue<Edge, std::vector<Edge>, EdgeComp> pq_;
};
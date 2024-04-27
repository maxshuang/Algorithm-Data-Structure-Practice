#pragma once
#include <queue>
#include <algorithm>
#include <limits>
#include <cmath>
#include "undirected_graph/undirected_graph.h"
#include "edge_comp.hpp"
#include "index_priority_queue.hpp"

// Proposition J. ( Cut property) Given any cut in an edge-weighted graph, the crossing edge of minimum weight is in
// the MST of the graph.
// Cut edge: vertices are in different cut
// Time Complexity: O(V*logE), Space Complexity: O(V)

// The key idea of PrimMST compared to LazyPrimMST is that it only maintains shortest edge of mst's vertices

// Prim’s algorithm
class PrimMST
{
public:
    // assume the graph is a connected graph
    PrimMST(const UndirectedGraph &g) : edge_to_(g.V(), -1), weight_to_(g.V(), std::numeric_limits<double>::infinity()), mst_weight_(0.0), pq_(g.V())
    {
        // initialize and build a cut
        edge_to_[0] = 0;
        visit(g, 0);

        while (!pq_.IsEmpty())
        {
            auto e = pq_.Top();
            pq_.Pop();
            mst_.push_back(e);
            mst_weight_ += e.Weight();
            edge_to_[e.Dest()] = e.Src();
            visit(g, e.Dest());
        }
    }
    std::vector<Edge> Edges() const { return mst_; }
    double Weight() const { return mst_weight_; }

private:
    void visit(const UndirectedGraph &g, int v)
    {
        auto pair = g.Adj(v);
        std::for_each(pair.first, pair.second, [&](const Edge &e)
                      {
                        // crossing edge
                        if(edge_to_[e.Dest()] == -1) {
                            // find a shorter edge to the mst nodes
                            if(weight_to_[e.Dest()] > e.Weight()) {
                                if(std::isinf(weight_to_[e.Dest()])) {
                                    pq_.Insert(e.Dest(), e);
                                }else {
                                    pq_.Change(e.Dest(), e);
                                }
                                weight_to_[e.Dest()]=e.Weight();
                            }
                        } });
    }

private:
    // minimum spanning tree
    std::vector<int> edge_to_;
    // non-tree vertices's smallest weight to mst nodes
    std::vector<double> weight_to_;
    std::vector<Edge> mst_;
    double mst_weight_;
    // keep the shortest edge from non-mst nodes to mst nodes
    // All are crossing edge
    IndexPriorityQueue<Edge, EdgeComp> pq_;
};
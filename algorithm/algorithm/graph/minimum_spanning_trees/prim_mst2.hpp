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
class PrimMST2
{
public:
    // assume the graph is a connected graph
    PrimMST2(const UndirectedGraph &g) : edge_to_(g.V()), marked_(g.V(), false),
                                         weight_to_(g.V(), std::numeric_limits<double>::infinity()), mst_weight_(0.0), pq_(g.V())
    {
        // the distance of initial vertice 0 to the mst is 0
        weight_to_[0] = 0.0;
        pq_.Insert(0, 0.0);

        while (!pq_.IsEmpty())
        {
            mst_weight_ += pq_.Top();
            auto i = pq_.Pop();
            // visit the new mst vertices
            visit(g, i);
        }

        make_mst();
    }
    std::vector<Edge> Edges() const { return edge_to_; }
    double Weight() const { return mst_weight_; }

private:
    void visit(const UndirectedGraph &g, int v)
    {
        marked_[v] = true;
        auto pair = g.Adj(v);
        std::for_each(pair.first, pair.second, [&](const Edge &e)
                      {
                        // ignore all non-crossing edges
                        if(!marked_[e.Dest()]) {
                            // update non-tree vertice if the new-added vertice can update some weight_to_ elements
                            if(e.Weight() < weight_to_[e.Dest()]) {
                                weight_to_[e.Dest()]=e.Weight();
                                // edge_to_ will converge to the mst
                                edge_to_[e.Dest()] = e;
                                
                                if(pq_.ContainsIndex(e.Dest())) pq_.Change(e.Dest(), e.Weight());
                                else pq_.Insert(e.Dest(), e.Weight());
                            }
                        } });
    }

    void make_mst() {
        // remove [0]
        edge_to_.erase(edge_to_.begin());
    }

private:
    // minimum spanning tree
    // [NOTE]: if you need to store the vertice in pq, then you need marked_ array to indicate the mst vertices
    std::vector<Edge> edge_to_;
    std::vector<bool> marked_;
    // non-tree vertices's smallest weight to mst nodes
    std::vector<double> weight_to_;
    double mst_weight_;
    // keep the shortest edge from non-mst nodes to mst nodes
    // All are crossing edge
    // non-tree-vertice <=> minimum distance to mst
    // 其实这里存的也是 crossing edge, Space Complexity: O(V)
    IndexPriorityQueue<double, std::greater<double>> pq_;
};
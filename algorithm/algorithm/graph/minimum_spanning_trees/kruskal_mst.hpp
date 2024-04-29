#pragma once
#include <priority_queue>
#include "undirected_graph/undirected_graph.h"
#include "union_find/union_find.h"
#include "edge_comp.hpp"

// kruskal algorithm is based on the idea that an edge with smallest weight is a mst edge if it doesn't form a circle

class KruskalMST {
public:
    KruskalMST(const UndirectedGraph& g): pq_(g.Edges().first, g.Edges().second), uf_(g.V()), mst_weight_(0.0) {
        while(!pq_.empty() && mst_edges_.size() < g.V()-1) {
            auto e = pq_.top();
            pq_.pop();
            if(!uf_.Connected(e.Dest(), e.Src())) {
                mst_edges_.push_back(e);
                uf_.Union(e.Dest(), e.Src());
            }
        }
    }
    std::vector<Edge> Edges() const { return mst_edges_; }
    double Weight() const { return mst_weight_; }
private:
    std::priority_queue<Edge, EdgeComp> pq_;
    // uf_ is for circle detection
    UnionFind uf_;
    std::vector<Edge> mst_edges_;
    double mst_weight_;
};


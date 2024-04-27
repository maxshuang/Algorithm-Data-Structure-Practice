#include <queue>
#include <algorithm>
#include "undirected_graph/undirected_graph.h"

// Proposition J. ( Cut property) Given any cut in an edge-weighted graph, the crossing edge of minimum weight is in
// the MST of the graph.

struct EdgeComp
{
    bool operator()(const Edge &l, const Edge &r) const { return l.Weight() > r.Weight(); }
};

// Prim’s algorithm
class MST
{
public:
    // assume the graph is a connected graph
    MST(const UndirectedGraph &g) : marked_(g.V(), false)
    {
        // initialize and build a cut
        auto pair = g.Adj(0);
        std::for_each(pair.first, pair.second, [&](const Edge &e)
                      { pq_.push(e); });
        marked_[0] = true;

        while (!pq_.empty() && !finished())
        {
            auto e = pq_.top();
            pq_.pop();
            if (!marked_[e.Dest()])
            {
                mst_.push_back(e);
                mst_weight_ += e.Weight();
                marked_[e.Dest()] = true;
                auto pair = g.Adj(e.Dest());
                std::for_each(pair.first, pair.second, [&](const Edge &e)
                              { if(!marked_[e.Dest()]) pq_.push(e); });
            }
        }
    }
    std::vector<Edge> Edges() const { return mst_; }
    double Weight() const { return mst_weight_; }

private:
    bool finished() const { return mst_.size() == marked_.size() - 1; }

private:
    std::vector<int> marked_;
    std::vector<Edge> mst_;
    double mst_weight_;
    // priority_queue is originally a maximum heap with std::less
    // need change to minimum heap
    std::priority_queue<Edge, std::vector<Edge>, EdgeComp> pq_;
};
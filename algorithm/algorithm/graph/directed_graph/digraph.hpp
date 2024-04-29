#ifndef DIRECT_GRAPH_
#define DIRECT_GRAPH_

#include <string>
#include <vector>
#include <forward_list>
#include "iterator2.hpp"

/**
 * @struct Edge
 * @brief Represents an edge in the graph.
 */
struct Edge
{
    Edge() : src(-1), dest(-1), weight(0.0) {}
    Edge(int s, int d, double w = 0) : src(s), dest(d), weight(w) {}
    int Src() const { return this->src; }
    int Dest() const { return this->dest; }
    double Weight() const { return this->weight; }

    bool operator==(const Edge &other) const
    {
        return src == other.src && dest == other.dest && (weight - other.weight) < 0.0001;
    }

private:
    int src;  /**< The index of the source vertex. */
    int dest; /**< The index of the destination vertex. */
    double weight;
};

class Digraph
{
public:
    typedef ConstIterator2<Edge> const_iterator;

    Digraph(int V) : edge_lists_(V), v_(V), e_(0) {}
    int V() const { return v_; }
    int E() const { return e_; }

    void AddEdge(int s, int t, double w = 0)
    {
        edge_lists_[s].push_front(Edge(s, t, w));
        ++e_;
    }

    std::pair<const_iterator, const_iterator> Adj(int v) const
    {
        return std::make_pair<Digraph::const_iterator, Digraph::const_iterator>(
            Digraph::const_iterator(edge_lists_[v].begin()), Digraph::const_iterator(edge_lists_[v].end()));
    }

    std::pair<const_iterator, const_iterator> Edges()
    {
        if (edges_.empty())
        {
            for (auto &ls : edge_lists_)
            {
                for (auto &e : ls)
                {
                    edges_.push_front(e);
                }
            }
        }

        return std::make_pair<Digraph::const_iterator, Digraph::const_iterator>(
            Digraph::const_iterator(edges_.begin()), Digraph::const_iterator(edges_.end()));
    }

    Digraph Reverse() const
    {
        Digraph other(this->V());
        for (auto &es : edge_lists_)
        {
            for (auto &e : es)
            {
                other.AddEdge(e.Dest(), e.Src(), e.Weight());
            }
        }

        return other;
    }

    std::string ToString() const
    {
        std::string graph_str;
        for (int i = 0; i < this->v_; i++)
        {
            graph_str.append(std::to_string(i)).append(":");
            for (const Edge &edge : this->edge_lists_[i])
            {
                graph_str.append(std::to_string(edge.Dest())).append(",");
            }
            graph_str.append("\n");
        }
        return graph_str;
    }
    // int InDegree(int v) const;
    // int OutDegree(int v) const;

private:
    std::vector<std::forward_list<Edge>> edge_lists_;
    std::forward_list<Edge> edges_;
    // std::vector<int> in_degree_;
    // std::vector<int> out_degree;
    int v_;
    int e_;
};
#endif
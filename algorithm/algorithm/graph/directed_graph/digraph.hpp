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
    Edge(int s, int d) : src(s), dest(d) {}
    int Src() const { return this->src; }
    int Dest() const { return this->dest; }

private:
    const int src;  /**< The index of the source vertex. */
    const int dest; /**< The index of the destination vertex. */
};

class Digraph
{
public:
    typedef ConstIterator2<Edge> const_iterator;
    Digraph(int V);
    int V() const;
    int E() const;
    void AddEdge(int v, int w);
    std::pair<const_iterator, const_iterator> Adj(int v) const;
    Digraph Reverse() const;
    std::string ToString() const;
    // int InDegree(int v) const;
    // int OutDegree(int v) const;

private:
    std::vector<std::forward_list<Edge>> edges_;
    // std::vector<int> in_degree_;
    // std::vector<int> out_degree;
    int v_;
    int e_;
};

Digraph::Digraph(int V) : edges_(V), v_(V), e_(0) {}

int Digraph::V() const { return v_; }

int Digraph::E() const { return e_; }

// int Digraph::InDegree(int v) const { return }

void Digraph::AddEdge(int v, int w)
{
    edges_[v].push_front(Edge(v, w));
    ++e_;
}

std::pair<Digraph::const_iterator, Digraph::const_iterator> Digraph::Adj(int v) const
{
    return std::make_pair<Digraph::const_iterator, Digraph::const_iterator>(
        Digraph::const_iterator(edges_[v].begin()), Digraph::const_iterator(edges_[v].end()));
}

Digraph Digraph::Reverse() const
{
    Digraph other(this->V());
    for (auto &es : edges_)
    {
        for (auto &e : es)
        {
            other.AddEdge(e.Dest(), e.Src());
        }
    }

    return other;
}

std::string Digraph::ToString() const
{
    std::string graph_str;
    for (int i = 0; i < this->v_; i++)
    {
        graph_str.append(std::to_string(i)).append(":");
        for (const Edge &edge : this->edges_[i])
        {
            graph_str.append(std::to_string(edge.Dest())).append(",");
        }
        graph_str.append("\n");
    }
    return graph_str;
}

#endif
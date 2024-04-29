#pragma once
/**
 * @file undirected_graph.h
 * @brief Header file for an undirected graph without edge weights.
 */
#include <vector>
#include <forward_list>
#include "iterator2.hpp"

/**
 * @struct Edge
 * @brief Represents an edge in the graph.
 */
struct Edge
{
    // [FIXME](maxshuang)
    Edge(): src(-1), dest(-1), weight(0) {}
    Edge(int s, int d, double w=0.0) : src(s), dest(d), weight(w) {}
    int Src() const { return this->src; }
    int Dest() const { return this->dest; }
    double Weight() const { return this->weight; }

    bool operator==(const Edge& other) const {
        return src == other.src && dest == other.dest && (weight-other.weight)<0.0001;
    }

private:
    int src;  /**< The index of the source vertex. */
    int dest; /**< The index of the destination vertex. */
    double weight;
};

/**
 * @struct UndirectedGraph
 * @brief Represents an undirected graph without edge weights.
 */
class UndirectedGraph
{
    //
    // behavior
    //
public:
    typedef ConstIterator2<Edge> const_iterator;
    UndirectedGraph(int V);
    ~UndirectedGraph();
    void AddEdge(int s, int t, double w = 0);
    int V() const;
    int E() const;
    // [FIXME]
    std::pair<const_iterator, const_iterator> Adj(int v) const;
    // [FIXME]
    std::pair<const_iterator, const_iterator> Edges();
    int Degree(int v) const;
    int MaxDegree() const;
    float AvgDegree() const;
    int NumberOfSelfLoops() const;
    void Show() const;

private:
    void addEdge(int s, int t, double w);
    //
    //  implementation
    //
private:
    const int v_; /**< The number of vertices in the graph. */
    int e_;       /**< The number of edges in the graph. */
    // 其实对于不关注路径权重的场景下，这里可以用点集即可，不用边集
    std::vector<std::forward_list<Edge>> edge_lists_; /**< Array of linked lists to store the edges for each vertex. */
    std::forward_list<Edge> edges_;
};
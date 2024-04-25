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
    Edge(int s, int d) : src(s), dest(d) {}
    int Src() const { return this->src; }
    int Dest() const { return this->dest; }

private:
    const int src;  /**< The index of the source vertex. */
    const int dest; /**< The index of the destination vertex. */
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
    void AddEdge(int v, int w);
    int V() const;
    int E() const;
    std::pair<const_iterator, const_iterator> Adj(int v) const;
    int Degree(int v) const;
    int MaxDegree() const;
    float AvgDegree() const;
    int NumberOfSelfLoops() const;
    void Show() const;

private:
    void addEdge(int v, int w);
    //
    //  implementation
    //
private:
    const int v_;                                    /**< The number of vertices in the graph. */
    int e_;                                          /**< The number of edges in the graph. */
    // 其实对于不关注路径权重的场景下，这里可以用点集即可，不用边集
    std::vector<std::forward_list<Edge>> edge_lists; /**< Array of linked lists to store the edges for each vertex. */
};
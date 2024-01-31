#pragma once
/**
 * @file undirectGraphWithoutWeight.h
 * @brief Header file for an undirected graph without edge weights.
 */
#include <vector>
#include <forward_list>


/**
 * @struct Edge
 * @brief Represents an edge in the graph.
 */
struct Edge {
    Edge(int s, int d) : src(s), dest(d) {}
    int Src() const { return this->src; }
    int Dest() const { return this->dest; }
private:
    const int src;            /**< The index of the source vertex. */
    const int dest;           /**< The index of the destination vertex. */
};

/**
 * @struct UndirectedGraphWithoutWeight
 * @brief Represents an undirected graph without edge weights.
 */
class UndirectedGraphWithoutWeight {
//
// behavior
//
public:
    UndirectedGraphWithoutWeight(int V);
    ~UndirectedGraphWithoutWeight();
    void AddEdge(int v, int w);
    int V() const;
    int E() const;
    // [TODO] make it implementation-free
    std::forward_list<Edge> Adj(int v) const;
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
    const int v;                /**< The number of vertices in the graph. */
    int e;                      /**< The number of edges in the graph. */
    std::vector<std::forward_list<Edge>> edgeLists;  /**< Array of linked lists to store the edges for each vertex. */
};
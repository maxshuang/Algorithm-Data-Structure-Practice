/**
 * @file basic.c
 * @brief Implementation of basic operations for an undirected graph without edge weights.
 */

#include <stdio.h>
#include <stdlib.h>
#include "undirected_graph.h"

UndirectedGraph::UndirectedGraph(int V) : v_(V), e_(0)
{
    if (V <= 0)
    {
        printf("Invalid number of vertices\n");
        return;
    }
    this->edge_lists_.resize(V);
}

UndirectedGraph::~UndirectedGraph()
{
}

/**
 * @brief Adds an edge to the given edge list.
 *
 * @param edgeList The edge list to add the edge to.
 * @param v The index of the first vertex.
 * @param w The index of the second vertex.
 * @return void
 */
void UndirectedGraph::addEdge(int v, int w, double weight)
{
    this->edge_lists_[v].push_front(Edge(v, w, weight));
}

/**
 * @brief Adds an edge between two vertices in the graph.
 *
 * @param graph The graph to add the edge to.
 * @param v The index of the first vertex.
 * @param w The index of the second vertex.
 * @return void
 */
void UndirectedGraph::AddEdge(int v, int w, double weight)
{
    if (v < 0 || v >= this->v_ || w < 0 || w >= this->v_)
    {
        printf("Invalid vertex\n");
        return;
    }
    addEdge(v, w, weight);
    addEdge(w, v, weight);
    this->e_++;
}

/**
 * @brief Returns the number of vertices in the graph.
 *
 * @param graph The graph.
 * @return The number of vertices.
 */
int UndirectedGraph::V() const
{
    return this->v_;
}

/**
 * @brief Returns the number of edges in the graph.
 *
 * @param graph The graph.
 * @return The number of edges.
 */
int UndirectedGraph::E() const
{
    return this->e_;
}

/**
 * @brief Returns the first edge connected to the given vertex.
 *
 * @param graph The graph.
 * @param v The index of the vertex.
 * @return A const reference to the first edge connected to the vertex.
 */
std::pair<UndirectedGraph::const_iterator, UndirectedGraph::const_iterator> UndirectedGraph::Adj(int v) const
{
    return std::make_pair(UndirectedGraph::const_iterator(this->edge_lists_[v].begin()), UndirectedGraph::const_iterator(this->edge_lists_[v].end()));
}

std::pair<UndirectedGraph::const_iterator, UndirectedGraph::const_iterator> UndirectedGraph::Edges()
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
    return std::make_pair(UndirectedGraph::const_iterator(this->edges_.begin()), UndirectedGraph::const_iterator(this->edges_.end()));
}

/**
 * @brief Prints the adjacency list representation of the graph.
 *
 * @return void
 */
void UndirectedGraph::Show() const
{
    for (int i = 0; i < this->v_; i++)
    {
        printf("%d: ", i);
        for (const Edge &edge : this->edge_lists_[i])
        {
            printf("%d ", edge.Dest());
        }
        printf("\n");
    }
}

/**
 * @brief Returns the degree of the given vertex.
 *
 * @param v The index of the vertex.
 * @return The degree of the vertex.
 */
int UndirectedGraph::Degree(int v) const
{
    if (v < 0 || v >= this->v_)
    {
        printf("Invalid vertex\n");
        return -1;
    }
    int deg = 0;
    for (const Edge & e: this->edge_lists_[v])
    {
        deg++;
    }
    return deg;
}

/**
 * @brief Returns the maximum degree of any vertex in the graph.
 *
 * @return The maximum degree.
 */
int UndirectedGraph::MaxDegree() const
{
    int max = 0;
    for (int i = 0; i < this->v_; i++)
    {
        int deg = this->Degree(i);
        if (deg > max)
        {
            max = deg;
        }
    }
    return max;
}

/**
 * @brief Returns the average degree of the vertices in the graph.
 *
 * @return The average degree.
 */
float UndirectedGraph::AvgDegree() const
{
    return 2 * (float)this->e_ / this->v_;
}

/**
 * @brief Returns the number of self-loops in the graph.
 *
 * @param graph The graph.
 * @return The number of self-loops../
 */
int UndirectedGraph::NumberOfSelfLoops() const
{
    int count = 0;
    for (int i = 0; i < this->v_; i++)
    {
        for (const Edge &edge : this->edge_lists_[i])
        {
            if (edge.Dest() == i)
            {
                count++;
            }
        }
    }

    // Each edge is counted twice since the graph is undirected
    // see the implementation of addEdge()
    return count / 2;
}
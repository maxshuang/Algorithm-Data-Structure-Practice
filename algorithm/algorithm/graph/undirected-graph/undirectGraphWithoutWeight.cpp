
/**
 * @file basic.c
 * @brief Implementation of basic operations for an undirected graph without edge weights.
 */

#include <stdio.h>
#include <stdlib.h>
#include "undirectGraphWithoutWeight.h"

UndirectedGraphWithoutWeight::UndirectedGraphWithoutWeight(int V): v(V), e(0){
    if (V <= 0) {
        printf("Invalid number of vertices\n");
        return;
    }
    this->edgeLists.resize(V);
}

UndirectedGraphWithoutWeight::~UndirectedGraphWithoutWeight(){
    for (int i = 0; i < this->v; i++) {
        this->edgeLists[i].clear();
    }
}

/**
 * @brief Adds an edge to the given edge list.
 * 
 * @param edgeList The edge list to add the edge to.
 * @param v The index of the first vertex.
 * @param w The index of the second vertex.
 * @return void
 */
void UndirectedGraphWithoutWeight::addEdge(int v, int w) {
    this->edgeLists[v].push_front(Edge(v,w));
}

/**
 * @brief Adds an edge between two vertices in the graph.
 * 
 * @param graph The graph to add the edge to.
 * @param v The index of the first vertex.
 * @param w The index of the second vertex.
 * @return void
 */
void UndirectedGraphWithoutWeight::AddEdge(int v, int w) {
    if (v < 0 || v >= this->v || w < 0 || w >= this->v) {
        printf("Invalid vertex\n");
        return;
    }
    addEdge(v, w);
    addEdge(w, v);
    this->e++;
}

/**
 * @brief Returns the number of vertices in the graph.
 * 
 * @param graph The graph.
 * @return The number of vertices.
 */
int UndirectedGraphWithoutWeight::V() const{
    return this->v;
}

/**
 * @brief Returns the number of edges in the graph.
 * 
 * @param graph The graph.
 * @return The number of edges.
 */
int UndirectedGraphWithoutWeight::E() const{
    return this->e;
}

/**
 * @brief Returns the first edge connected to the given vertex.
 * 
 * @param graph The graph.
 * @param v The index of the vertex.
 * @return A const reference to the first edge connected to the vertex.
 */
std::forward_list<Edge> UndirectedGraphWithoutWeight::Adj(int v) const {
    if (v < 0 || v >= this->v) {
        printf("Invalid vertex\n");
        return std::forward_list<Edge>();
    }
    return this->edgeLists[v];
}

/**
 * @brief Prints the adjacency list representation of the graph.
 * 
 * @return void
 */
void UndirectedGraphWithoutWeight::Show() const {
    for (int i = 0; i < this->v; i++) {
        printf("%d: ", i);
        for (const Edge& edge : this->edgeLists[i]) {
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
int UndirectedGraphWithoutWeight::Degree(int v) const{
    if (v < 0 || v >= this->v) {
        printf("Invalid vertex\n");
        return -1;
    }
    int deg = 0;
    for (const Edge& edge : this->edgeLists[v]) {
        deg++;
    }
    return deg;
}

/**
 * @brief Returns the maximum degree of any vertex in the graph.
 * 
 * @return The maximum degree.
 */
int UndirectedGraphWithoutWeight::MaxDegree() const{
    int max = 0;
    for (int i = 0; i < this->v; i++) {
        int deg = this->Degree(i);
        if (deg > max) {
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
float UndirectedGraphWithoutWeight::AvgDegree() const{
    return 2 * (float)this->e / this->v;
}

/**
 * @brief Returns the number of self-loops in the graph.
 * 
 * @param graph The graph.
 * @return The number of self-loops.
 */
int UndirectedGraphWithoutWeight::NumberOfSelfLoops() const {
    int count = 0;
    for (int i = 0; i < this->v; i++) {
        for (const Edge& edge : this->edgeLists[v]) {
            if (edge.Dest() == i) {
                count++;
            }
        }
    }

    // Each edge is counted twice since the graph is undirected
    // see the implementation of addEdge()
    return count / 2;
}
#include <stdio.h>
#include <stdlib.h>
#include "undirectGraphWithoutWeight.h"

int main() {
    // Create a graph with 5 vertices
    UndirectedGraphWithoutWeight graph(5);

    // Add edges between vertices
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(2, 3);
    graph.AddEdge(3, 4);

    // Print the adjacency list representation of the graph
    graph.Show();

    // Get the number of vertices and edges
    int numVertices = graph.V();
    int numEdges = graph.E();
    printf("Number of vertices: %d\n", numVertices);
    printf("Number of edges: %d\n", numEdges);

    // Get the degree of a vertex
    int vertexDegree = graph.Degree(3);
    printf("Degree of vertex 3: %d\n", vertexDegree);

    // Get the maximum degree in the graph
    int maxDegreeValue =  graph.MaxDegree();
    printf("Maximum degree: %d\n", maxDegreeValue);

    // Get the average degree in the graph
    int avgDegreeValue = graph.AvgDegree();
    printf("Average degree: %d\n", avgDegreeValue);

    // Get the number of self-loops in the graph
    int numSelfLoops = graph.NumberOfSelfLoops();
    printf("Number of self-loops: %d\n", numSelfLoops);
    return 0;
}
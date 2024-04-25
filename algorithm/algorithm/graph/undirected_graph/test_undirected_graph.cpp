#include <stdio.h>
#include <stdlib.h>
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "undirected_graph.h"

 TEST_CASE("Test UndirectedGraph basic attributes", "[graph]"){
    // Create a graph with 5 vertices
    UndirectedGraph graph(5);

    // Add edges between vertices
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(2, 3);
    graph.AddEdge(3, 4);

    // Print the adjacency list representation of the graph
    graph.Show();

    // Get the number of vertices and edges
    REQUIRE(graph.V()==5);
    REQUIRE(graph.E()==5);

    // Get the degree of a vertex
    REQUIRE(graph.Degree(3)==3);

    // Get the maximum degree in the graph
    REQUIRE(graph.MaxDegree()==3);

    // Get the average degree in the graph
    REQUIRE(int(graph.AvgDegree())==2);

    // Get the number of self-loops in the graph
    REQUIRE(graph.NumberOfSelfLoops()==0);
}


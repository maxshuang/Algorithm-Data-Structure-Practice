#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "digraph.hpp"
#include "catch.hpp"

TEST_CASE("Test DiGraph basic attributes", "[graph]")
{
    // Create a graph with 5 vertices
    Digraph graph(5);

    // Add edges between vertices
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(2, 3);
    graph.AddEdge(3, 4);

    // Print the adjacency list representation of the graph
    std::string graph_str("0:2,1,\n1:3,\n2:3,\n3:4,\n4:\n");
    REQUIRE(graph.ToString() == graph_str);

    // Get the number of vertices and edges
    REQUIRE(graph.V() == 5);
    REQUIRE(graph.E() == 5);

    auto pair = graph.Adj(0);
    int index = 2;
    for (auto iter = pair.first; iter != pair.second; ++iter, index--)
    {
        REQUIRE(iter->Dest() == index);
    }

    pair = graph.Adj(1);
    std::for_each(pair.first, pair.second, [](const Edge &e)
                  { REQUIRE(e.Dest() == 3); });

    pair = graph.Adj(2);
    std::for_each(pair.first, pair.second, [](const Edge &e)
                  { REQUIRE(e.Dest() == 3); });

    pair = graph.Adj(3);
    std::for_each(pair.first, pair.second, [](const Edge &e)
                  { REQUIRE(e.Dest() == 4); });

    pair = graph.Adj(4);
    REQUIRE(std::distance(pair.first, pair.second) == 0);
}

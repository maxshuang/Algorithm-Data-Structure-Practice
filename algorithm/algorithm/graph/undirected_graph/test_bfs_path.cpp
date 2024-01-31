#include <iostream>
#include "bfs_path.h"
#include "string.hpp"
#include "catch.hpp"

TEST_CASE("Test BfsPaths", "[bfs]") {
    UndirectedGraph graph(6); // Create a graph with 6 vertices
    graph.AddEdge(0, 1); // Add edges
    graph.AddEdge(0, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(2, 4);
    graph.AddEdge(3, 4);
    graph.AddEdge(3, 5);

    BfsPaths bfsPaths(graph, 0);

    // Check the path from source to destination
    REQUIRE(bfsPaths.HasPathTo(5) == true);
    REQUIRE(bfsPaths.HasPathTo(2) == true);
    REQUIRE(bfsPaths.HasPathTo(4) == true);
    REQUIRE(bfsPaths.HasPathTo(1) == true);
    REQUIRE(bfsPaths.HasPathTo(3) == true);
    REQUIRE(bfsPaths.HasPathTo(0) == true);

    // Check the path from source to unreachable vertices
    REQUIRE(bfsPaths.HasPathTo(6) == false);
    REQUIRE(bfsPaths.HasPathTo(7) == false);

    // Check the path from destination to source
    //std::cout << "path to 5:" << toString(bfsPaths.PathTo(5)) << std::endl;
    REQUIRE((bfsPaths.PathTo(5) == std::vector<int>{5, 3, 1, 0}));
    REQUIRE((bfsPaths.PathTo(2) == std::vector<int>{2, 0}));
    REQUIRE((bfsPaths.PathTo(4) == std::vector<int>{4, 2, 0}));
    REQUIRE((bfsPaths.PathTo(1) == std::vector<int>{1, 0}));
    REQUIRE((bfsPaths.PathTo(3) == std::vector<int>{3, 1, 0}));
    REQUIRE((bfsPaths.PathTo(0) == std::vector<int>{0}));
}
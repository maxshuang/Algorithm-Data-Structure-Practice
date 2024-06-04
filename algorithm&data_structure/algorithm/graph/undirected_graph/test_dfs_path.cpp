#include <iostream>
#include <string>
#include "dfs_path.h"
#include "string.hpp"
#include "catch.hpp"

TEST_CASE("Test DfsPaths", "[dfs]") {
    UndirectedGraph graph(6); // Create a graph with 6 vertices
    graph.AddEdge(0, 1); // Add edges
    graph.AddEdge(0, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(2, 4);
    graph.AddEdge(3, 4);
    graph.AddEdge(3, 5);

    DfsPaths dfsPaths(graph, 0);

    // Test if there is a path from 0 to 5
    REQUIRE(dfsPaths.HasPathTo(5) == true);

    // Test if there is a path from 0 to 2
    REQUIRE(dfsPaths.HasPathTo(2) == true);

    // Test if there is a path from 0 to 6 (non-existent vertex)
    REQUIRE(dfsPaths.HasPathTo(6) == false);

    // Test the path from 0 to 5
    std::vector<int> pathTo5 = dfsPaths.PathTo(5);
    //std::cout << "path to 5：" << toString(pathTo5) << std::endl;
    REQUIRE((pathTo5 == std::vector<int>{5, 3, 4, 2, 0}));

    // Test the path from 0 to 2
    std::vector<int> pathTo2 = dfsPaths.PathTo(2);
    //std::cout << "path to 2：" << toString(pathTo2) << std::endl;
    REQUIRE((pathTo2 == std::vector<int>{2, 0}));

    // Test the path from 0 to 6 (non-existent vertex)
    std::vector<int> pathTo6 = dfsPaths.PathTo(6);
    REQUIRE(pathTo6.empty() == true);
}
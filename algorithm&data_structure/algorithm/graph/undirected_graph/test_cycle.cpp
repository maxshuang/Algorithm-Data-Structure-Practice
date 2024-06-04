#include "catch.hpp"
#include "cycle.hpp"

TEST_CASE("Test Cycle", "[graph]")
{
    UndirectedGraph g(9);
    g.AddEdge(1, 2);
    g.AddEdge(2, 3);
    g.AddEdge(3, 4);
    g.AddEdge(3, 5);
    g.AddEdge(5, 6);

    SECTION("test no cycle")
    {
        Cycle dag(g);
        REQUIRE(!dag.HasCycle());
        REQUIRE(dag.GetCycle().empty());
    }

    SECTION("test has cycle")
    {
        g.AddEdge(6, 2);
        Cycle dag(g);
        REQUIRE(dag.HasCycle());
        REQUIRE(dag.GetCycle() == std::vector<int>{3, 5, 6, 2});
    }

    SECTION("test has two cycles")
    {
        g.AddEdge(6, 2);
        g.AddEdge(0, 7);
        g.AddEdge(7, 8);
        g.AddEdge(8, 0);
        Cycle dag(g);
        REQUIRE(dag.HasCycle());
        REQUIRE(dag.GetCycle() == std::vector<int>{7, 8, 0});
    }
}
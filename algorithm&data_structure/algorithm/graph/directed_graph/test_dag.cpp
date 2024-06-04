#include "dag.hpp"
#include "catch.hpp"

TEST_CASE("Test DAG", "[graph]")
{
    Digraph g(9);
    g.AddEdge(1, 2);
    g.AddEdge(2, 3);
    g.AddEdge(3, 4);
    g.AddEdge(3, 5);
    g.AddEdge(5, 6);

    SECTION("test no cycle") {
        DAG dag(g);
        REQUIRE(!dag.HasCycle());
        REQUIRE(dag.Cycle().empty());
    }

    SECTION("test has cycle") {
        g.AddEdge(6, 2);
        DAG dag(g);
        REQUIRE(dag.HasCycle());
        REQUIRE(dag.Cycle()==std::vector<int>{6, 5, 3, 2});
    }

    SECTION("test has cycle")
    {
        g.AddEdge(6, 5);
        DAG dag(g);
        REQUIRE(dag.HasCycle());
        REQUIRE(dag.Cycle() == std::vector<int>{6, 5});
    }

    SECTION("test has two cycles") {
        g.AddEdge(6, 2);
        g.AddEdge(0, 7);
        g.AddEdge(7, 8);
        g.AddEdge(8, 0);
        DAG dag(g);
        REQUIRE(dag.HasCycle());
        REQUIRE(dag.Cycle()==std::vector<int>{8, 7, 0});
    }
}

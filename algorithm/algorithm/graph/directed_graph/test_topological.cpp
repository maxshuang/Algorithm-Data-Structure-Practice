#include "topological.hpp"
#include "catch.hpp"

TEST_CASE("TEST topological sort", "[graph]")
{
    Digraph g(9);
    g.AddEdge(1, 2);
    g.AddEdge(2, 3);
    g.AddEdge(3, 4);
    g.AddEdge(3, 5);
    g.AddEdge(5, 6);

    SECTION("test no cycle")
    {
        Topological tp(g);
        REQUIRE(tp.IsDAG());
        REQUIRE(tp.Order() == std::vector<int>{8, 7, 1, 2, 3, 4, 5, 6, 0});
    }

    SECTION("test has cycle")
    {
        g.AddEdge(6, 2);
        Topological tp(g);
        REQUIRE(!tp.IsDAG());
        REQUIRE(tp.Order() == std::vector<int>{});
    }

    SECTION("test has two cycles")
    {
        g.AddEdge(6, 2);
        g.AddEdge(0, 7);
        g.AddEdge(7, 8);
        g.AddEdge(8, 0);
        Topological tp(g);
        REQUIRE(!tp.IsDAG());
        REQUIRE(tp.Order() == std::vector<int>{});
    }
}
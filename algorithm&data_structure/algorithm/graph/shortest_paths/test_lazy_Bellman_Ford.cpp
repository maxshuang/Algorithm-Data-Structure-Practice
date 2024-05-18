#include "lazy_Bellman_Ford.hpp"
#include "catch.hpp"

TEST_CASE("Test lazy_bellman_ford", "[DAG]")
{
    Digraph g(11);
    g.AddEdge(0, 1, 1);
    g.AddEdge(1, 2, -2);
    g.AddEdge(1, 3, 5);
    g.AddEdge(1, 4, 4);
    g.AddEdge(3, 6, -6);
    g.AddEdge(4, 5, 1);
    g.AddEdge(5, 6, 1);

    SECTION("DAG")
    {
        LazyBellmanFordSP sp(g, 0);
        REQUIRE(!sp.HasNegativeCycle());
        REQUIRE(sp.DistTo(1) == 1);
        REQUIRE(sp.DistTo(2) == -1);
        REQUIRE(sp.DistTo(3) == 6);
        REQUIRE(sp.DistTo(4) == 5);
        REQUIRE(sp.DistTo(5) == 6);
        REQUIRE(sp.DistTo(6) == 0);
        REQUIRE(std::isinf(sp.DistTo(7)));
        REQUIRE(!sp.HasPathTo(7));
        REQUIRE(sp.HasPathTo(6));
        REQUIRE(sp.HasPathTo(5));
        REQUIRE(sp.HasPathTo(4));
        REQUIRE(sp.HasPathTo(3));
        REQUIRE(sp.HasPathTo(2));
        REQUIRE(sp.HasPathTo(1));
        REQUIRE(sp.PathTo(6) == std::vector<Edge>{Edge{3, 6, -6}, Edge{1, 3, 5}, Edge{0, 1, 1}});
        REQUIRE(sp.PathTo(3) == std::vector<Edge>{Edge{1, 3, 5}, Edge{0, 1, 1}});
    }

    SECTION("positive cycle")
    {
        g.AddEdge(0, 8, -1);
        g.AddEdge(8, 9, 2);
        g.AddEdge(9, 0, 3);

        LazyBellmanFordSP sp(g, 0);
        REQUIRE(!sp.HasNegativeCycle());
        REQUIRE(sp.DistTo(8) == -1);
        REQUIRE(sp.DistTo(9) == 1);
        REQUIRE(std::isinf(sp.DistTo(10)));
        REQUIRE(!sp.HasPathTo(10));
        REQUIRE(sp.HasPathTo(2));
        REQUIRE(sp.PathTo(6) == std::vector<Edge>{Edge{3, 6, -6}, Edge{1, 3, 5}, Edge{0, 1, 1}});
        REQUIRE(sp.PathTo(9) == std::vector<Edge>{Edge{8, 9, 2}, Edge{0, 8, -1}});
    }

   
    SECTION("reachable negative cycle")
    {
        g.AddEdge(0, 8, -3);
        g.AddEdge(8, 9, 1);
        g.AddEdge(9, 0, 1);

        LazyBellmanFordSP sp(g, 0);
        REQUIRE(sp.HasNegativeCycle());
        REQUIRE(std::isinf(sp.DistTo(8)));
        REQUIRE(std::isinf(sp.DistTo(9)));
        REQUIRE(!sp.HasPathTo(8));
        REQUIRE(!sp.HasPathTo(9));
        REQUIRE(sp.PathTo(9) == std::vector<Edge>{});
        REQUIRE(sp.PathTo(8) == std::vector<Edge>{});
    }

    SECTION("unreachable negative cycle")
    {
        g.AddEdge(8, 9, -3);
        g.AddEdge(9, 10, 1);
        g.AddEdge(10, 8, 1);

        LazyBellmanFordSP sp(g, 0);
        REQUIRE(!sp.HasNegativeCycle());
        REQUIRE(std::isinf(sp.DistTo(8)));
        REQUIRE(std::isinf(sp.DistTo(9)));
        REQUIRE(std::isinf(sp.DistTo(10)));
        REQUIRE(!sp.HasPathTo(8));
        REQUIRE(!sp.HasPathTo(9));
        REQUIRE(!sp.HasPathTo(10));
        REQUIRE(sp.PathTo(9) == std::vector<Edge>{});
        REQUIRE(sp.PathTo(8) == std::vector<Edge>{});
        REQUIRE(sp.PathTo(10) == std::vector<Edge>{});
    }
}
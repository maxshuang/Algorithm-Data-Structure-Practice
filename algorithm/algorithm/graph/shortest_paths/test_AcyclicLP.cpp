#include <limits>
#include <cmath>
#include <functional>
#include "acyclicLP.hpp"
#include "directed_graph/digraph.hpp"
#include "catch.hpp"
#include "helper/float.hpp"

TEST_CASE("Test numeric limits", "[infinity]") {
    REQUIRE(std::isinf(std::numeric_limits<double>::infinity()));
    REQUIRE(std::isinf(-std::numeric_limits<double>::infinity()));
}


TEST_CASE("Test AcyclicLP", "[shortest path]")
{
    Digraph g(7);
    g.AddEdge(4, 6, 0.62);
    g.AddEdge(5, 6, 0.88);
    g.AddEdge(1, 5, 0.02);
    g.AddEdge(0, 4, 0.64);
    g.AddEdge(1, 6, 0.90);
    g.AddEdge(1, 2, 0.50);
    g.AddEdge(0, 2, 0.22);
    g.AddEdge(1, 3, 0.97);
    g.AddEdge(2, 6, 0.17);

    SECTION("start from 0")
    {
        AcyclicLP lp(g, 0);
        REQUIRE(!(lp.HasPathTo(1)));
        REQUIRE(!(lp.HasPathTo(3)));
        REQUIRE(!(lp.HasPathTo(5)));
        REQUIRE(std::isinf(lp.DistTo(1)));
        REQUIRE(std::isinf(lp.DistTo(3)));
        REQUIRE(std::isinf(lp.DistTo(5)));
        REQUIRE(DoubleEqual(lp.DistTo(0), 0.0));
        REQUIRE(DoubleEqual(lp.DistTo(2), 0.22));
        REQUIRE(DoubleEqual(lp.DistTo(4), 0.64));
        REQUIRE(DoubleEqual(lp.DistTo(6), 1.26));

        REQUIRE(lp.PathTo(2) == std::vector<Edge>{Edge{0, 2, 0.22}});
        REQUIRE(lp.PathTo(6) == std::vector<Edge>{Edge{4, 6, 0.62}, Edge{0, 4, 0.64}});
    }

    SECTION("start from 1")
    {
        AcyclicLP lp(g, 1);
        REQUIRE(std::isinf(lp.DistTo(0)));
        REQUIRE(std::isinf(lp.DistTo(4)));
        REQUIRE(DoubleEqual(lp.DistTo(1), 0.0));
        REQUIRE(DoubleEqual(lp.DistTo(2), 0.50));
        REQUIRE(DoubleEqual(lp.DistTo(3), 0.97));
        REQUIRE(DoubleEqual(lp.DistTo(5), 0.02));
        REQUIRE(DoubleEqual(lp.DistTo(6), 0.90));
    }

    SECTION("start from 2")
    {
        AcyclicLP lp(g, 2);
        REQUIRE(std::isinf(lp.DistTo(0)));
        REQUIRE(std::isinf(lp.DistTo(4)));
        REQUIRE(std::isinf(lp.DistTo(1)));
        REQUIRE(std::isinf(lp.DistTo(3)));
        REQUIRE(std::isinf(lp.DistTo(5)));
        REQUIRE(DoubleEqual(lp.DistTo(2), 0.0));
        REQUIRE(DoubleEqual(lp.DistTo(6), 0.17));
    }

    SECTION("start from 3")
    {
        AcyclicLP lp(g, 3);
        REQUIRE(std::isinf(lp.DistTo(0)));
        REQUIRE(std::isinf(lp.DistTo(4)));
        REQUIRE(std::isinf(lp.DistTo(1)));
        REQUIRE(std::isinf(lp.DistTo(2)));
        REQUIRE(std::isinf(lp.DistTo(5)));
        REQUIRE(std::isinf(lp.DistTo(6)));
        REQUIRE(DoubleEqual(lp.DistTo(3), 0.0));
    }

    SECTION("start from 4")
    {
        AcyclicLP lp(g, 4);
        REQUIRE(std::isinf(lp.DistTo(0)));
        REQUIRE(std::isinf(lp.DistTo(3)));
        REQUIRE(std::isinf(lp.DistTo(1)));
        REQUIRE(std::isinf(lp.DistTo(2)));
        REQUIRE(std::isinf(lp.DistTo(5)));
        REQUIRE(DoubleEqual(lp.DistTo(4), 0.0));
        REQUIRE(DoubleEqual(lp.DistTo(6), 0.62));
    }

    SECTION("start from 5")
    {
        AcyclicLP lp(g, 5);
        REQUIRE(std::isinf(lp.DistTo(0)));
        REQUIRE(std::isinf(lp.DistTo(3)));
        REQUIRE(std::isinf(lp.DistTo(1)));
        REQUIRE(std::isinf(lp.DistTo(2)));
        REQUIRE(std::isinf(lp.DistTo(4)));
        REQUIRE(DoubleEqual(lp.DistTo(5), 0.0));
        REQUIRE(DoubleEqual(lp.DistTo(6), 0.88));
    }

    SECTION("start from 6")
    {
        AcyclicLP lp(g, 6);
        REQUIRE(!(lp.HasPathTo(0)));
        REQUIRE(!(lp.HasPathTo(3)));
        REQUIRE(!(lp.HasPathTo(5)));
        REQUIRE(std::isinf(lp.DistTo(0)));
        REQUIRE(std::isinf(lp.DistTo(3)));
        REQUIRE(std::isinf(lp.DistTo(1)));
        REQUIRE(std::isinf(lp.DistTo(2)));
        REQUIRE(std::isinf(lp.DistTo(4)));
        REQUIRE(std::isinf(lp.DistTo(5)));
        REQUIRE(DoubleEqual(lp.DistTo(6), 0.0));
    }
}
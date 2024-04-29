#define CATCH_CONFIG_MAIN
#include <limits>
#include <cmath>
#include "DijkstraSP.hpp"
#include "directed_graph/digraph.hpp"
#include "catch.hpp"

bool DoubleEqual(double t, double o)
{
    return std::fabs(t - o) <= std::numeric_limits<double>::epsilon();
}

TEST_CASE("Test DijkstraSP", "[shortest path]")
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
        DijkstraSP sp(g, 0);
        REQUIRE(!(sp.HasPathTo(1)));
        REQUIRE(!(sp.HasPathTo(3)));
        REQUIRE(!(sp.HasPathTo(5)));
        REQUIRE(std::isinf(sp.DistTo(1)));
        REQUIRE(std::isinf(sp.DistTo(3)));
        REQUIRE(std::isinf(sp.DistTo(5)));
        REQUIRE(DoubleEqual(sp.DistTo(0), 0.0));
        REQUIRE(DoubleEqual(sp.DistTo(2), 0.22));
        REQUIRE(DoubleEqual(sp.DistTo(4), 0.64));
        REQUIRE(DoubleEqual(sp.DistTo(6), 0.39));
    }

    SECTION("start from 1")
    {
        DijkstraSP sp(g, 1);
        REQUIRE(std::isinf(sp.DistTo(0)));
        REQUIRE(std::isinf(sp.DistTo(4)));
        REQUIRE(DoubleEqual(sp.DistTo(1), 0.0));
        REQUIRE(DoubleEqual(sp.DistTo(2), 0.50));
        REQUIRE(DoubleEqual(sp.DistTo(3), 0.97));
        REQUIRE(DoubleEqual(sp.DistTo(5), 0.02));
        REQUIRE(DoubleEqual(sp.DistTo(6), 0.67));
    }

    SECTION("start from 2")
    {
        DijkstraSP sp(g, 2);
        REQUIRE(std::isinf(sp.DistTo(0)));
        REQUIRE(std::isinf(sp.DistTo(4)));
        REQUIRE(std::isinf(sp.DistTo(1)));
        REQUIRE(std::isinf(sp.DistTo(3)));
        REQUIRE(std::isinf(sp.DistTo(5)));
        REQUIRE(DoubleEqual(sp.DistTo(2), 0.0));
        REQUIRE(DoubleEqual(sp.DistTo(6), 0.17));
    }

    SECTION("start from 3")
    {
        DijkstraSP sp(g, 3);
        REQUIRE(std::isinf(sp.DistTo(0)));
        REQUIRE(std::isinf(sp.DistTo(4)));
        REQUIRE(std::isinf(sp.DistTo(1)));
        REQUIRE(std::isinf(sp.DistTo(2)));
        REQUIRE(std::isinf(sp.DistTo(5)));
        REQUIRE(std::isinf(sp.DistTo(6)));
        REQUIRE(DoubleEqual(sp.DistTo(3), 0.0));
    }

    SECTION("start from 4")
    {
        DijkstraSP sp(g, 4);
        REQUIRE(std::isinf(sp.DistTo(0)));
        REQUIRE(std::isinf(sp.DistTo(3)));
        REQUIRE(std::isinf(sp.DistTo(1)));
        REQUIRE(std::isinf(sp.DistTo(2)));
        REQUIRE(std::isinf(sp.DistTo(5)));
        REQUIRE(DoubleEqual(sp.DistTo(4), 0.0));
        REQUIRE(DoubleEqual(sp.DistTo(6), 0.62));
    }

    SECTION("start from 5")
    {
        DijkstraSP sp(g, 5);
        REQUIRE(std::isinf(sp.DistTo(0)));
        REQUIRE(std::isinf(sp.DistTo(3)));
        REQUIRE(std::isinf(sp.DistTo(1)));
        REQUIRE(std::isinf(sp.DistTo(2)));
        REQUIRE(std::isinf(sp.DistTo(4)));
        REQUIRE(DoubleEqual(sp.DistTo(5), 0.0));
        REQUIRE(DoubleEqual(sp.DistTo(6), 0.88));
    }

    SECTION("start from 6")
    {
        DijkstraSP sp(g, 6);
        REQUIRE(std::isinf(sp.DistTo(0)));
        REQUIRE(std::isinf(sp.DistTo(3)));
        REQUIRE(std::isinf(sp.DistTo(1)));
        REQUIRE(std::isinf(sp.DistTo(2)));
        REQUIRE(std::isinf(sp.DistTo(4)));
        REQUIRE(std::isinf(sp.DistTo(5)));
        REQUIRE(DoubleEqual(sp.DistTo(6), 0.0));
    }
}
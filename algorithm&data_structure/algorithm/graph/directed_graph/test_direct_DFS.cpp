#include "direct_DFS.hpp"
#include "catch.hpp"

TEST_CASE("Test direct DFS", "[graph]")
{
    Digraph g(9);
    g.AddEdge(1, 2);
    g.AddEdge(2, 3);
    g.AddEdge(3, 4);
    g.AddEdge(3, 5);
    g.AddEdge(5, 6);

    SECTION("test disconnected")
    {
        DirectDFS df(g, 0);
        REQUIRE(!df.Connected(1));
        REQUIRE(!df.Connected(2));
        REQUIRE(!df.Connected(3));
        REQUIRE(!df.Connected(4));
        REQUIRE(!df.Connected(5));
        REQUIRE(!df.Connected(6));
    }

    SECTION("test connected")
    {
        DirectDFS df(g, 1);
        REQUIRE(df.Connected(1));
        REQUIRE(df.Connected(2));
        REQUIRE(df.Connected(3));
        REQUIRE(df.Connected(4));
        REQUIRE(df.Connected(5));
        REQUIRE(df.Connected(6));
    }

    SECTION("test disconnected2")
    {
        DirectDFS df(g, 7);
        REQUIRE(df.Connected(7));
        REQUIRE(!df.Connected(0));
        REQUIRE(!df.Connected(1));
        REQUIRE(!df.Connected(2));
        REQUIRE(!df.Connected(8));
    }

    SECTION("test disconnected3")
    {
        DirectDFS df(g, 8);
        REQUIRE(!df.Connected(7));
        REQUIRE(!df.Connected(0));
        REQUIRE(!df.Connected(1));
        REQUIRE(!df.Connected(2));
        REQUIRE(df.Connected(8));
    }
}

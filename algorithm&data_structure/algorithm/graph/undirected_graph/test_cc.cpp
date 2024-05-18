#include "connected_component.hpp"
#include "catch.hpp"

TEST_CASE("Test Connected Component", "[graph]")
{
    UndirectedGraph G(10);
    G.AddEdge(1, 2);
    G.AddEdge(2, 5);
    G.AddEdge(2, 7);
    G.AddEdge(3, 9);
    G.AddEdge(6, 9);
    G.AddEdge(4, 8);
    ConnectedComponent cc(G);

    SECTION("Test Connected")
    {
        REQUIRE(cc.Connected(1, 2));
        REQUIRE(cc.Connected(1, 5));
        REQUIRE(cc.Connected(7, 5));

        REQUIRE(cc.Connected(3, 9));
        REQUIRE(cc.Connected(3, 6));
        REQUIRE(cc.Connected(9, 6));

        REQUIRE(cc.Connected(4, 8));

        REQUIRE(!cc.Connected(1, 3));
        REQUIRE(!cc.Connected(4, 5));
        REQUIRE(!cc.Connected(9, 2));
        REQUIRE(!cc.Connected(0, 2));
    }

    SECTION("Test Count")
    {
        REQUIRE(cc.Count() == 4);
    }

    SECTION("Test Id")
    {
        int index=1;
        REQUIRE(cc.Id(0) == index);

        ++index;
        REQUIRE(cc.Id(1) == index);
        REQUIRE(cc.Id(2) == index);
        REQUIRE(cc.Id(5) == index);
        REQUIRE(cc.Id(7) == index);

        ++index;
        REQUIRE(cc.Id(3) == index);
        REQUIRE(cc.Id(9) == index);
        REQUIRE(cc.Id(6) == index);

        ++index;
        REQUIRE(cc.Id(4) == index);
        REQUIRE(cc.Id(8) == index);
    }
}
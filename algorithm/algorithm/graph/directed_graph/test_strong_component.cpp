#include "strongly_connected_components.hpp"
#include "catch.hpp"

TEST_CASE("Test SCC", "[graph]")
{
    Digraph g(10);
    g.AddEdge(1, 2);
    // scc
    g.AddEdge(2, 3);
    g.AddEdge(3, 4);
    g.AddEdge(4, 2);

    g.AddEdge(1, 6);
    // scc
    g.AddEdge(6, 7);
    g.AddEdge(7, 8);
    g.AddEdge(8, 9);
    g.AddEdge(9, 6);

    g.AddEdge(3, 5);

    StronglyComponent scc(g);

    REQUIRE(!scc.StronglyConnected(1, 2));
    REQUIRE(!scc.StronglyConnected(1, 6));
    REQUIRE(!scc.StronglyConnected(1, 3));
    REQUIRE(!scc.StronglyConnected(1, 4));
    REQUIRE(!scc.StronglyConnected(1, 5));
    REQUIRE(!scc.StronglyConnected(1, 6));
    REQUIRE(!scc.StronglyConnected(1, 7));
    REQUIRE(!scc.StronglyConnected(1, 8));
    REQUIRE(!scc.StronglyConnected(2, 6));
    REQUIRE(!scc.StronglyConnected(3, 7));

    REQUIRE(scc.StronglyConnected(2, 3));
    REQUIRE(scc.StronglyConnected(2, 4));
    REQUIRE(scc.StronglyConnected(3, 4));

    REQUIRE(scc.StronglyConnected(6, 7));
    REQUIRE(scc.StronglyConnected(7, 8));
    REQUIRE(scc.StronglyConnected(6, 8));
    REQUIRE(scc.StronglyConnected(6, 9));
    REQUIRE(scc.StronglyConnected(7, 9));
    REQUIRE(scc.StronglyConnected(8, 9));

    REQUIRE(scc.Count() == 5);

    REQUIRE(scc.ID(6) == 1);
    REQUIRE(scc.ID(7) == 1);
    REQUIRE(scc.ID(8) == 1);
    REQUIRE(scc.ID(9) == 1);
    REQUIRE(scc.ID(5) == 2);
    REQUIRE(scc.ID(2) == 3);
    REQUIRE(scc.ID(3) == 3);
    REQUIRE(scc.ID(4) == 3);
    REQUIRE(scc.ID(1) == 4);
    REQUIRE(scc.ID(0) == 5);
}
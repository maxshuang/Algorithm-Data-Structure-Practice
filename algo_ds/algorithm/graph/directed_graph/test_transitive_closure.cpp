#include "transitive_closure.hpp"
#include "catch.hpp"

TEST_CASE("Test transitive closure", "[graph]")
{
    Digraph g(9);
    g.AddEdge(1, 2);
    g.AddEdge(2, 3);
    g.AddEdge(3, 4);
    g.AddEdge(3, 5);
    g.AddEdge(5, 6);

    TransitiveClosure tc(g);
    REQUIRE(!tc.Reachable(0, 1));
    REQUIRE(tc.Reachable(1, 2));
    REQUIRE(tc.Reachable(1, 3));
    REQUIRE(tc.Reachable(2, 4));
    REQUIRE(tc.Reachable(2, 5));
    REQUIRE(tc.Reachable(1, 6));

    REQUIRE(!tc.Reachable(0, 7));
    REQUIRE(!tc.Reachable(0, 8));
    REQUIRE(!tc.Reachable(2, 7));
    REQUIRE(!tc.Reachable(3, 8));
    REQUIRE(!tc.Reachable(5, 8));
}
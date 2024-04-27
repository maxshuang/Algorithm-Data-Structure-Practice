#include <cmath>
#include "prim_mst.hpp"
#include "catch.hpp"

TEST_CASE("Test PrimMST", "[graph]")
{
    UndirectedGraph g(7);
    g.AddEdge(4, 6, 0.62);
    g.AddEdge(5, 6, 0.88);
    g.AddEdge(1, 5, 0.02);
    g.AddEdge(0, 4, 0.64);
    g.AddEdge(1, 6, 0.90);
    g.AddEdge(1, 2, 0.50);
    g.AddEdge(0, 2, 0.22);
    g.AddEdge(1, 3, 0.97);
    g.AddEdge(2, 6, 0.17);

    PrimMST mst(g);
    REQUIRE(std::abs(mst.Weight() - 2.50) < 0.0001);
    REQUIRE(mst.Edges() == std::vector<Edge>{Edge{0, 2, 0.22}, Edge{2, 6, 0.17}, Edge{2, 1, 0.5}, Edge{1, 5, 0.02}, Edge{6, 4, 0.62}, Edge{1, 3, 0.97}});
}
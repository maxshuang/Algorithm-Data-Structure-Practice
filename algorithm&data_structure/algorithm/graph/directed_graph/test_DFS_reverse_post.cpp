#include "DFS_reverse_post.hpp"
#include "catch.hpp"

TEST_CASE("Test DFS reverse post order", "[graph]")
{
    Digraph g(13);
    g.AddEdge(0, 5);
    g.AddEdge(0, 1);
    g.AddEdge(0, 6);
    g.AddEdge(2, 0);
    g.AddEdge(2, 3);
    g.AddEdge(3, 5);
    g.AddEdge(5, 4);
    g.AddEdge(6, 4);
    g.AddEdge(7, 6);
    g.AddEdge(8, 7);
    g.AddEdge(6, 9);
    g.AddEdge(9, 10);
    g.AddEdge(9, 11);
    g.AddEdge(9, 12);
    g.AddEdge(11, 12);

    DirectReversePost rp(g);
    REQUIRE(rp.PostOrder()==std::vector<int>{12, 11, 10, 9, 4, 6, 1, 5, 0, 3, 2, 7, 8});
    REQUIRE(rp.ReversePostOrder()==std::vector<int>{8, 7, 2, 3, 0, 5, 1, 6, 4, 9, 10, 11, 12});
}

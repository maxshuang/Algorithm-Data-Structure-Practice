#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "union_find.h"

TEST_CASE("Test UnionFind::Find", "[union find]")
{
    SECTION("Test with single element")
    {
        UnionFind uf(1);
        REQUIRE(uf.Find(0) == 0);
    }

    SECTION("Test with two elements")
    {
        UnionFind uf(2);
        REQUIRE(uf.Find(0) == 0);
        REQUIRE(uf.Find(1) == 1);
    }

    SECTION("Test with three elements")
    {
        UnionFind uf(3);
        REQUIRE(uf.Find(0) == 0);
        REQUIRE(uf.Find(1) == 1);
        REQUIRE(uf.Find(2) == 2);
    }

    SECTION("Test with larger set")
    {
        UnionFind uf(10);
        REQUIRE(uf.Find(0) == 0);
        REQUIRE(uf.Find(1) == 1);
        REQUIRE(uf.Find(2) == 2);
        REQUIRE(uf.Find(3) == 3);
        REQUIRE(uf.Find(4) == 4);
        REQUIRE(uf.Find(5) == 5);
        REQUIRE(uf.Find(6) == 6);
        REQUIRE(uf.Find(7) == 7);
        REQUIRE(uf.Find(8) == 8);
        REQUIRE(uf.Find(9) == 9);
    }
}

TEST_CASE("Test UnionFind::Union", "[union find]")
{
    SECTION("Test with two elements")
    {
        UnionFind uf(2);
        uf.Union(0, 1);
        REQUIRE(uf.Find(0) == uf.Find(1));
        REQUIRE(uf.Connected(0,1));
    }

    SECTION("Test with three elements")
    {
        UnionFind uf(3);
        uf.Union(0, 1);
        uf.Union(1, 2);
        REQUIRE(uf.Find(0) == uf.Find(2));
        REQUIRE(uf.Find(1) == uf.Find(2));
        REQUIRE(uf.Connected(0,1));
        REQUIRE(uf.Connected(0,2));
        REQUIRE(uf.Connected(2,1));
    }

    SECTION("Test with larger set")
    {
        UnionFind uf(10);
        uf.Union(0, 1);
        uf.Union(2, 3);
        uf.Union(4, 5);
        uf.Union(6, 7);
        uf.Union(8, 9);
        REQUIRE(uf.Find(0) == uf.Find(1));
        REQUIRE(uf.Find(2) == uf.Find(3));
        REQUIRE(uf.Find(4) == uf.Find(5));
        REQUIRE(uf.Find(6) == uf.Find(7));
        REQUIRE(uf.Find(8) == uf.Find(9));
        REQUIRE(uf.Connected(0,1));
        REQUIRE(uf.Connected(3,2));
        REQUIRE(uf.Connected(4,5));
        REQUIRE(uf.Connected(6,7));
        REQUIRE(uf.Connected(8,9));
        REQUIRE(!uf.Connected(0,2));
        REQUIRE(!uf.Connected(4,2));
        REQUIRE(!uf.Connected(4,6));
        REQUIRE(!uf.Connected(6,8));
    }
}

TEST_CASE("Test UnionFind::MaxDepth", "[union find]")
{
    SECTION("Test with single element")
    {
        UnionFind uf(1);
        REQUIRE(uf.MaxDepth() == 0);
    }

    SECTION("Test with two elements")
    {
        UnionFind uf(2);
        REQUIRE(uf.MaxDepth() == 0);
        uf.Union(0, 1);
        REQUIRE(uf.MaxDepth() == 1);
    }

    SECTION("Test with three elements")
    {
        UnionFind uf(3);
        REQUIRE(uf.MaxDepth() == 0);
        uf.Union(0, 1);
        REQUIRE(uf.MaxDepth() == 1);
        uf.Union(1, 2);
        REQUIRE(uf.MaxDepth() == 1);
    }

    SECTION("Test with larger set")
    {
        UnionFind uf(10);
        REQUIRE(uf.MaxDepth() == 0);
        uf.Union(0, 1);
        uf.Union(2, 3);
        uf.Union(4, 5);
        uf.Union(6, 7);
        uf.Union(8, 9);
        REQUIRE(uf.MaxDepth() == 1);
        uf.Union(1, 9);
        REQUIRE(uf.MaxDepth() == 2);
    }
}


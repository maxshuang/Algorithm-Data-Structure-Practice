// #define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "index_priority_queue.hpp"

TEST_CASE("Test MAX IndexPriorityQueue", "[MAX]")
{
    SECTION("Test Insert and MAX")
    {
        IndexPriorityQueue<int> pq(5);
        pq.Insert(0, 5);
        pq.Insert(1, 3);
        pq.Insert(2, 7);
        pq.Insert(3, 1);
        REQUIRE(pq.Top() == 7);      // top (2, 7)
        REQUIRE(pq.TopIndex() == 2); // top (2, 7)
    }

    SECTION("Test Pop")
    {
        IndexPriorityQueue<int> pq(5);
        pq.Insert(0, 5);
        pq.Insert(1, 3);
        pq.Insert(2, 7);
        pq.Insert(3, 1);
        REQUIRE(pq.Pop() == 2); // pop (2, 7)
        REQUIRE(pq.Top() == 5); // top (0, 5)
        REQUIRE(pq.Pop() == 0); // pop (0, 5)
        REQUIRE(pq.Top() == 3); // top (1, 3)
        REQUIRE(pq.Pop() == 1); // pop (1, 3)
        REQUIRE(pq.Top() == 1); // top (3, 1)
        REQUIRE(pq.Size() == 1);
        REQUIRE(pq.Pop() == 3);  // pop (3, 1)
        REQUIRE(pq.Pop() == -1); // invalid
    }

    SECTION("Test Size")
    {
        IndexPriorityQueue<int> pq(5);
        pq.Insert(0, 5);
        pq.Insert(1, 3);
        pq.Insert(2, 7);
        pq.Insert(3, 1);
        REQUIRE(pq.Size() == 4);
    }

    SECTION("Test Empty")
    {
        IndexPriorityQueue<int> pq(5);
        REQUIRE(pq.IsEmpty());

        pq.Insert(0, 5);
        REQUIRE_FALSE(pq.IsEmpty());
    }

    SECTION("Test Change")
    {
        IndexPriorityQueue<int> pq(5);
        pq.Insert(0, 5);
        pq.Insert(1, 3);
        pq.Insert(2, 7);
        pq.Insert(3, 1);
        pq.Change(3, 10);
        REQUIRE(pq.Top() == 10); // top (3, 10)
        REQUIRE(pq.Pop() == 3);  // pop (3, 10)
        REQUIRE(pq.Pop() == 2);  // pop (2, 7)
        REQUIRE(pq.Pop() == 0);  // pop (0, 5)
        REQUIRE(pq.Pop() == 1);  // pop (1, 3)
    }

    SECTION("Test ContainsIndex")
    {
        IndexPriorityQueue<int> pq(5);
        pq.Insert(0, 5);
        pq.Insert(1, 3);
        pq.Insert(2, 7);
        pq.Insert(3, 1);
        REQUIRE(pq.ContainsIndex(0));
        REQUIRE(pq.ContainsIndex(1));
        REQUIRE(pq.ContainsIndex(2));
        REQUIRE(pq.ContainsIndex(3));
        REQUIRE_FALSE(pq.ContainsIndex(4));
    }

    SECTION("Test Delete")
    {
        IndexPriorityQueue<int> pq(5);
        pq.Insert(0, 5);
        pq.Insert(1, 3);
        pq.Insert(2, 7);
        pq.Insert(3, 1);
        pq.DeleteIndex(3);
        REQUIRE(pq.Top() == 7);  // top (2, 7)
        REQUIRE(pq.Pop() == 2);  // pop (2, 7)
        REQUIRE(pq.Pop() == 0);  // pop (0, 5)
        REQUIRE(pq.Pop() == 1);  // pop (1, 3)
        REQUIRE(pq.Pop() == -1); // invalid
    }
}

TEST_CASE("Test MIN IndexPriorityQueue", "[MIN]")
{
    SECTION("Test Insert and MIN")
    {
        IndexPriorityQueue<int, std::greater<int>> pq(5);
        pq.Insert(0, 5);
        pq.Insert(1, 3);
        pq.Insert(2, 7);
        pq.Insert(3, 1);
        REQUIRE(pq.Top() == 1);      // top (3, 1)
        REQUIRE(pq.TopIndex() == 3); // top (3, 1)
    }

    SECTION("Test Pop")
    {
        IndexPriorityQueue<int, std::greater<int>> pq(5);
        pq.Insert(0, 5);
        pq.Insert(1, 3);
        pq.Insert(2, 7);
        pq.Insert(3, 1);
        REQUIRE(pq.Pop() == 3); // pop (3, 1)
        REQUIRE(pq.Top() == 3); // top (1, 3)
        REQUIRE(pq.Pop() == 1); // pop (1, 3)
        REQUIRE(pq.Top() == 5); // top (0, 5)
        REQUIRE(pq.Pop() == 0); // pop (0, 5)
        REQUIRE(pq.Top() == 7); // top (2, 7)
        REQUIRE(pq.Size() == 1);
        REQUIRE(pq.Pop() == 2);  // pop (2, 7)
        REQUIRE(pq.Pop() == -1); // invalid
    }

    SECTION("Test Size")
    {
        IndexPriorityQueue<int, std::greater<int>> pq(5);
        pq.Insert(0, 5);
        pq.Insert(1, 3);
        pq.Insert(2, 7);
        pq.Insert(3, 1);
        REQUIRE(pq.Size() == 4);
    }

    SECTION("Test Empty")
    {
        IndexPriorityQueue<int, std::greater<int>> pq(5);
        REQUIRE(pq.IsEmpty());

        pq.Insert(0, 5);
        REQUIRE_FALSE(pq.IsEmpty());
    }

    SECTION("Test Change")
    {
        IndexPriorityQueue<int, std::greater<int>> pq(5);
        pq.Insert(0, 5);
        pq.Insert(1, 3);
        pq.Insert(2, 7);
        pq.Insert(3, 1);
        pq.Change(3, 10);
        REQUIRE(pq.Top() == 3); // top (1, 3)
        REQUIRE(pq.Pop() == 1); // pop (1, 3)
        REQUIRE(pq.Pop() == 0); // pop (0, 5)
        REQUIRE(pq.Pop() == 2); // pop (2, 7)
        REQUIRE(pq.Pop() == 3); // pop (3, 10)
    }

    SECTION("Test ContainsIndex")
    {
        IndexPriorityQueue<int, std::greater<int>> pq(5);
        pq.Insert(0, 5);
        pq.Insert(1, 3);
        pq.Insert(2, 7);
        pq.Insert(3, 1);
        REQUIRE(pq.ContainsIndex(0));
        REQUIRE(pq.ContainsIndex(1));
        REQUIRE(pq.ContainsIndex(2));
        REQUIRE(pq.ContainsIndex(3));
        REQUIRE_FALSE(pq.ContainsIndex(4));
    }

    SECTION("Test Delete")
    {
        IndexPriorityQueue<int, std::greater<int>> pq(5);
        pq.Insert(0, 5);
        pq.Insert(1, 3);
        pq.Insert(2, 7);
        pq.Insert(3, 1);
        pq.DeleteIndex(3);
        REQUIRE(pq.Top() == 3);  // top (1, 3)
        REQUIRE(pq.Pop() == 1);  // pop (1, 3)
        REQUIRE(pq.Pop() == 0);  // pop (0, 5)
        REQUIRE(pq.Pop() == 2);  // pop (2, 7)
        REQUIRE(pq.Pop() == -1); // invalid
    }
}
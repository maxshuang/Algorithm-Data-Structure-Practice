//#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "index_priority_queue.h"

TEST_CASE("Test IndexPriorityMinQueue", "[IndexPriorityMinQueue]")
{
    SECTION("Test Insert and Min")
    {
        IndexPriorityMinQueue pq(5);
        pq.Insert(0, 5);
        pq.Insert(1, 3);
        pq.Insert(2, 7);
        pq.Insert(3, 1);
        REQUIRE(pq.Min() == 1);
    }

    SECTION("Test delMin")
    {
        IndexPriorityMinQueue pq(5);
        pq.Insert(0, 5);
        pq.Insert(1, 3);
        pq.Insert(2, 7);
        pq.Insert(3, 1);
        REQUIRE(pq.DelMin() == 3);
        REQUIRE(pq.Min() == 3);
        REQUIRE(pq.DelMin() == 1);
        REQUIRE(pq.Min() == 5);
        REQUIRE(pq.DelMin() == 0);
        REQUIRE(pq.Min() == 7);
        REQUIRE(pq.Size() == 1);
        REQUIRE(pq.DelMin() == 2);
        REQUIRE(pq.DelMin() == -1);
    }

    SECTION("Test Size")
    {
        IndexPriorityMinQueue pq(5);
        pq.Insert(0, 5);
        pq.Insert(1, 3);
        pq.Insert(2, 7);
        pq.Insert(3, 1);
        REQUIRE(pq.Size() == 4);
    }

    SECTION("Test Empty")
    {
        IndexPriorityMinQueue pq(5);
        REQUIRE(pq.IsEmpty());

        pq.Insert(0, 5);
        REQUIRE_FALSE(pq.IsEmpty());
    }

    SECTION("Test Change")
    {
        IndexPriorityMinQueue pq(5);
        pq.Insert(0, 5);
        pq.Insert(1, 3);
        pq.Insert(2, 7);
        pq.Insert(3, 1);
        pq.Change(3, 10);
        REQUIRE(pq.Min() == 3);
        REQUIRE(pq.DelMin() == 1);
        REQUIRE(pq.DelMin() == 0);
        REQUIRE(pq.DelMin() == 2);
        REQUIRE(pq.DelMin() == 3);
    }

    SECTION("Test Contains")
    {
        IndexPriorityMinQueue pq(5);
        pq.Insert(0, 5);
        pq.Insert(1, 3);
        pq.Insert(2, 7);
        pq.Insert(3, 1);
        REQUIRE(pq.Contains(0));
        REQUIRE(pq.Contains(1));
        REQUIRE(pq.Contains(2));
        REQUIRE(pq.Contains(3));
        REQUIRE_FALSE(pq.Contains(4));
    }

    SECTION("Test Delete")
    {
        IndexPriorityMinQueue pq(5);
        pq.Insert(0, 5);
        pq.Insert(1, 3);
        pq.Insert(2, 7);
        pq.Insert(3, 1);
        pq.Delete(3);
        REQUIRE(pq.Min() == 3);
        REQUIRE(pq.DelMin() == 1);
        REQUIRE(pq.DelMin() == 0);
        REQUIRE(pq.DelMin() == 2);
        REQUIRE(pq.DelMin() == -1);
    }
}
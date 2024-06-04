
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "priority_queue.h"

TEST_CASE("Test PriorityMinQueue", "[PriorityMinQueue]")
{
    SECTION("Test Insert and Min")
    {
        PriorityMinQueue pq;
        pq.Insert(5);
        pq.Insert(3);
        pq.Insert(7);
        pq.Insert(1);
        REQUIRE(pq.Min() == 1);
    }

    SECTION("Test delMin")
    {
        PriorityMinQueue pq;
        pq.Insert(5);
        pq.Insert(3);
        pq.Insert(7);
        pq.Insert(1);
        REQUIRE(pq.DelMin() == 1);
        REQUIRE(pq.Min() == 3);
        REQUIRE(pq.DelMin() == 3);
        REQUIRE(pq.Min() == 5);
        REQUIRE(pq.DelMin() == 5);
        REQUIRE(pq.Min() == 7);
        REQUIRE(pq.Size() == 1);
        REQUIRE(pq.DelMin() == 7);
        REQUIRE(pq.DelMin() == -1);
    }

    SECTION("Test Size")
    {
        PriorityMinQueue pq;
        pq.Insert(5);
        pq.Insert(3);
        pq.Insert(7);
        pq.Insert(1);
        REQUIRE(pq.Size() == 4);
    }

    SECTION("Test Empty")
    {
        PriorityMinQueue pq;
        REQUIRE(pq.IsEmpty());

        pq.Insert(5);
        REQUIRE_FALSE(pq.IsEmpty());
    }
}
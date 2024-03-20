#define CATCH_CONFIG_MAIN
#include <map>
#include "catch.hpp"
#include "skip_list.hpp"
#include "skip_list2.hpp"

TEST_CASE("Test SkipList Insertion and Retrieval", "[skip_list]")
{
    SkipList skipList(0.5);

    SECTION("Test inserting and retrieving a single element")
    {
        skipList.Insert(1, 10);
        REQUIRE(skipList.Get(1) == 10);
    }

    SECTION("Test inserting and retrieving multiple elements")
    {
        skipList.Insert(1, 10);
        skipList.Insert(2, 20);
        skipList.Insert(3, 30);

        REQUIRE(skipList.Get(1) == 10);
        REQUIRE(skipList.Get(2) == 20);
        REQUIRE(skipList.Get(3) == 30);
    }

    SECTION("Test inserting and retrieving elements with the same key")
    {
        skipList.Insert(1, 10);
        skipList.Insert(1, 20);
        skipList.Insert(1, 30);

        REQUIRE(skipList.Get(1) == 30);
    }
}

TEST_CASE("Test SkipList Deletion", "[skip_list]")
{
    SkipList skipList(0.5);

    SECTION("Test deleting an existing element")
    {
        skipList.Insert(1, 10);
        skipList.Delete(1);

        REQUIRE_THROWS_AS(skipList.Get(1), std::out_of_range);
    }

    SECTION("Test deleting a non-existing element")
    {
        skipList.Insert(1, 10);
        skipList.Delete(2);

        REQUIRE(skipList.Get(1) == 10);
    }
}

/////////

TEST_CASE("Test SkipList2 Insertion and Retrieval", "[skip_list2]")
{
    SkipList2<int, int> skipList(0.5);

    SECTION("Test inserting and retrieving a single element")
    {
        skipList.Insert(1, 10);
        REQUIRE(skipList.Get(1) == 10);
    }

    SECTION("Test inserting and retrieving multiple elements")
    {
        skipList.Insert(1, 10);
        skipList.Insert(2, 20);
        skipList.Insert(3, 30);

        REQUIRE(skipList.Get(1) == 10);
        REQUIRE(skipList.Get(2) == 20);
        REQUIRE(skipList.Get(3) == 30);
    }

    SECTION("Test inserting and retrieving elements with the same key")
    {
        skipList.Insert(1, 10);
        skipList.Insert(1, 20);
        skipList.Insert(1, 30);

        REQUIRE(skipList.Get(1) == 30);
    }
}

TEST_CASE("Test SkipList2 Deletion", "[skip_list2]")
{
    SkipList2<int, int> skipList(0.5);

    SECTION("Test deleting an existing element")
    {
        skipList.Insert(1, 10);
        skipList.Delete(1);

        REQUIRE_THROWS_AS(skipList.Get(1), std::out_of_range);
    }

    SECTION("Test deleting a non-existing element")
    {
        skipList.Insert(1, 10);
        skipList.Delete(2);

        REQUIRE(skipList.Get(1) == 10);
    }
}

int randomLevel()
{
    int level = 1;
    while (level < 21 && (rand() & 0x7FFF) < 0x7FFF*0.5)
        level++;
    return level;
}

TEST_CASE("Test random level", "[random level]")
{
    srand(time(NULL));
    int N=100000;
    std::map<int, int> cnt;
    while(N) {
        ++cnt[randomLevel()];
        --N;
    }

    REQUIRE(cnt.size()>10);
}

TEST_CASE("Test GetRank with valid rank", "[skip_list2]")
{
    SkipList2<int, int> skipList(0.5);
    skipList.Insert(1, 10);
    skipList.Insert(2, 20);
    skipList.Insert(3, 30);

    SECTION("Test GetRank with rank 1")
    {
        REQUIRE(skipList.GetRank(1).key == 1);
        REQUIRE(skipList.GetRank(1).value == 10);
    }

    SECTION("Test GetRank with rank 2")
    {
        REQUIRE(skipList.GetRank(2).key == 2);
        REQUIRE(skipList.GetRank(2).value == 20);
    }

    SECTION("Test GetRank with rank 3")
    {
        REQUIRE(skipList.GetRank(3).key == 3);
        REQUIRE(skipList.GetRank(3).value == 30);
    }
}

TEST_CASE("Test GetRank with invalid rank", "[skip_list2]")
{
    SkipList2<int, int> skipList(0.5);
    skipList.Insert(1, 10);
    skipList.Insert(2, 20);
    skipList.Insert(3, 30);

    SECTION("Test GetRank with rank greater than list length")
    {
        REQUIRE_THROWS_AS(skipList.GetRank(4), std::out_of_range);
    }

    SECTION("Test GetRank with negative rank")
    {
        REQUIRE_THROWS_AS(skipList.GetRank(-1), std::out_of_range);
    }
}
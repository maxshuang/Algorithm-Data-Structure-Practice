#include <stdio.h>
#include <stdlib.h>
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"
#include "trie.h"

TEST_CASE("Test cascadingRemove function in Trie", "[trie]")
{
    Trie trie;

    // Add some words to the trie
    trie.Insert("apple");
    trie.Insert("banana");
    trie.Insert("cherry");

    SECTION("Remove existing word")
    {
        REQUIRE(trie.Remove("banana"));
        REQUIRE_FALSE(trie.Search("banana"));
    }

    SECTION("Remove non-existing word")
    {
        REQUIRE_FALSE(trie.Remove("grape"));
        REQUIRE_FALSE(trie.Search("grape"));
    }

    SECTION("Remove word with common prefix")
    {
        trie.Insert("app");
        REQUIRE(trie.Remove("apple"));
        REQUIRE_FALSE(trie.Search("apple"));
        REQUIRE(trie.Search("app"));
    }

    SECTION("Remove word with no cascading removal")
    {
        trie.Insert("car");
        REQUIRE(trie.Remove("cherry"));
        REQUIRE_FALSE(trie.Search("cherry"));
        REQUIRE(trie.Search("car"));
    }
}

TEST_CASE("Benchmark Insert", "[benchmark Insert]")
{
    BENCHMARK_ADVANCED("Insert Trie")
    (Catch::Benchmark::Chronometer meter)
    {
        Trie trie;

        meter.measure([&trie]
                      {
            trie.Insert("apple");
            trie.Insert("banana");
            trie.Insert("cherry"); });
    };
}

TEST_CASE("Benchmark Remove", "[benchmark Remove]")
{
    BENCHMARK_ADVANCED("Remove Trie")
    (Catch::Benchmark::Chronometer meter)
    {
        Trie trie;
        trie.Insert("app");
        trie.Insert("apple");
        trie.Insert("banana");
        trie.Insert("car");
        trie.Insert("cherry");

        meter.measure([&trie]
                      {
            trie.Remove("appl");
            trie.Remove("banana");
            trie.Remove("cherry"); });
    };
}

//////////////////////////////////////////////////////////////
// Test Trie2

TEST_CASE("Test Trie2", "[trie2]")
{
    Trie2 trie;

    // Add some words to the trie
    trie.Insert("apple");
    trie.Insert("banana");
    trie.Insert("cherry");

    SECTION("Search word")
    {
        REQUIRE_FALSE(trie.Search("banan"));
        REQUIRE(trie.Search("banana"));
    }
}

TEST_CASE("Benchmark Insert Trie2", "[benchmark Insert Trie2]")
{
    BENCHMARK_ADVANCED("Insert Trie2")
    (Catch::Benchmark::Chronometer meter)
    {
        Trie2 trie; // Setup: create a new Trie2 instance.

        // Run the benchmark.
        meter.measure([&trie]
                      {
            trie.Insert("apple");
            trie.Insert("banana");
            trie.Insert("cherry"); });

        // Teardown: Clear the Trie2 instance.
        // If your Trie2 class has a clear or reset method, you can call it here.
        // If not, the trie will be cleared automatically when it goes out of scope.
    };
}
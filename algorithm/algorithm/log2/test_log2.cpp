#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "log2.h"

TEST_CASE("Test all log2", "[log2]")
{
    SECTION("Test with 0")
    {
        int value = 0;
        int expected = -1;
        REQUIRE(log2_fun2(value) == expected);
        // REQUIRE(log2_fun1(value) == expected);
        REQUIRE(log2(value) == expected);
        REQUIRE(log2_O1(value) == expected);
        REQUIRE(log2_Olg(value) == expected);
        REQUIRE(log2_Olglg(value) == expected);
        REQUIRE(log2_binary(value) == expected);
    }

    SECTION("Test with 1")
    {
        int value = 1;
        int expected = 0;
        REQUIRE(log2_fun2(value) == expected);
        // REQUIRE(log2_fun1(value) == expected);
        REQUIRE(log2(value) == expected);
        REQUIRE(log2_O1(value) == expected);
        REQUIRE(log2_Olg(value) == expected);
        REQUIRE(log2_Olglg(value) == expected);
        REQUIRE(log2_binary(value) == expected);
    }

    SECTION("Test with 2")
    {
        int value = 2;
        int expected = 1;
        REQUIRE(log2_fun2(value) == expected);
        // REQUIRE(log2_fun1(value) == expected);
        REQUIRE(log2(value) == expected);
        REQUIRE(log2_O1(value) == expected);
        REQUIRE(log2_Olg(value) == expected);
        REQUIRE(log2_Olglg(value) == expected);
        REQUIRE(log2_binary(value) == expected);
    }

    SECTION("Test with 8")
    {
        int value = 8;
        int expected = 3;
        REQUIRE(log2_fun2(value) == expected);
        // REQUIRE(log2_fun1(value) == expected);
        REQUIRE(log2(value) == expected);
        REQUIRE(log2_O1(value) == expected);
        REQUIRE(log2_Olg(value) == expected);
        REQUIRE(log2_Olglg(value) == expected);
        REQUIRE(log2_binary(value) == expected);
    }

    SECTION("Test with huge")
    {
        int value = std::pow(2, 29) - 1;
        int expected = 28;
        REQUIRE(log2_fun2(value) == expected);
        // REQUIRE(log2_fun1(value) == expected);
        REQUIRE(log2(value) == expected);
        REQUIRE(log2_O1(value) == expected);
        REQUIRE(log2_Olg(value) == expected);
        REQUIRE(log2_Olglg(value) == expected);
        REQUIRE(log2_binary(value) == expected);
    }

    // Add more test cases here...
}

TEST_CASE("Test std log2", "[log2]")
{
    // precion, eps
    long long value = std::pow(2, 59) - 1;
    int expected = 59;
    REQUIRE(std::log2(value) == expected);
}

TEST_CASE("Test lsb3", "[log2]")
{
    SECTION("Test with 0")
    {
        int value = 0;
        int expected = -1;
        REQUIRE(lsb3(value) == expected);
        REQUIRE(lsb2(value) == expected);
        REQUIRE(lsb(value) == expected);
    }

    SECTION("Test with 1")
    {
        int value = 1;
        int expected = 0;
        REQUIRE(lsb3(value) == expected);
        REQUIRE(lsb2(value) == expected);
        REQUIRE(lsb(value) == expected);
    }

    SECTION("Test with 2")
    {
        int value = 2;
        int expected = 1;
        REQUIRE(lsb3(value) == expected);
        REQUIRE(lsb2(value) == expected);
        REQUIRE(lsb(value) == expected);
    }

    SECTION("Test with 8")
    {
        int value = 8;
        int expected = 3;
        REQUIRE(lsb3(value) == expected);
        REQUIRE(lsb2(value) == expected);
        REQUIRE(lsb(value) == expected);
    }

    SECTION("Test with huge")
    {
        int value = std::pow(2, 29);
        int expected = 29;
        REQUIRE(lsb3(value) == expected);
    }

    // Add more test cases here...
}
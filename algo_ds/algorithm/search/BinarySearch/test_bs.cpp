#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "bs.hpp"

TEST_CASE("Test binary search", "")
{
    std::vector<int> vec{1, 2, 3, 4, 6};
    
    SECTION("existed") {
        REQUIRE(binary_search(vec, 3)==2);
        REQUIRE(binary_search(vec, 6)==4);
    }

    SECTION("non-existed") {
        REQUIRE(binary_search(vec, 5)==-1);
    }
}

TEST_CASE("Test upper_bound", "")
{
    std::vector<int> vec{1, 2, 3, 3, 4, 6};
    
    SECTION("existed in the middle") {
        REQUIRE(upper_bound(vec, 3)==4);
        REQUIRE(upper_bound(vec, 2)==2);
        REQUIRE(upper_bound(vec, 5)==5);
    }

    SECTION("all larger") {
        REQUIRE(upper_bound(vec, -1)==0);
        REQUIRE(upper_bound(vec, -2)==0);
    }

    SECTION("all smaller") {
        REQUIRE(upper_bound(vec, 7)==-1);
        REQUIRE(upper_bound(vec, 9)==-1);
    }
}

TEST_CASE("Test lower_bound", "")
{
    std::vector<int> vec{1, 2, 3, 3, 4, 6};
    
    SECTION("existed in the middle") {
        REQUIRE(lower_bound(vec, 3)==2);
        REQUIRE(lower_bound(vec, 2)==1);
        REQUIRE(lower_bound(vec, 5)==5);
    }

    SECTION("all larger") {
        REQUIRE(lower_bound(vec, -1)==0);
        REQUIRE(lower_bound(vec, -2)==0);
    }

    SECTION("all smaller") {
        REQUIRE(lower_bound(vec, 7)==-1);
        REQUIRE(lower_bound(vec, 9)==-1);
    }
}

TEST_CASE("Test floor", "")
{
    std::vector<int> vec{1, 2, 3, 3, 4, 6};
    
    SECTION("existed in the middle") {
        REQUIRE(floor(vec, 3)==2);
        REQUIRE(floor(vec, 2)==1);
        REQUIRE(floor(vec, 5)==5);
    }

    SECTION("all larger") {
        REQUIRE(floor(vec, -1)==0);
        REQUIRE(floor(vec, -2)==0);
    }

    SECTION("all smaller") {
        REQUIRE(floor(vec, 7)==-1);
        REQUIRE(floor(vec, 9)==-1);
    }
}

TEST_CASE("Test ceilling", "")
{
    std::vector<int> vec{1, 2, 3, 3, 4, 6};
    
    SECTION("existed in the middle") {
        REQUIRE(ceilling(vec, 3)==3);
        REQUIRE(ceilling(vec, 2)==1);
        REQUIRE(ceilling(vec, 5)==4);
    }

    SECTION("all larger") {
        REQUIRE(ceilling(vec, -1)==-1);
        REQUIRE(ceilling(vec, -2)==-1);
    }

    SECTION("all smaller") {
        REQUIRE(ceilling(vec, 7)==vec.size()-1);
        REQUIRE(ceilling(vec, 9)==vec.size()-1);
    }
}
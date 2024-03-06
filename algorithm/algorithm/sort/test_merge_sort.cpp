// #define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "merge_sort.h"

TEST_CASE("Test merge_sort", "[sort]")
{
    SECTION("Test with empty array")
    {
        int arr[] = {};
        int expected[] = {};
        int size = sizeof(arr) / sizeof(arr[0]);

        merge_sort(arr, size);

        REQUIRE(std::equal(arr, arr + size, expected));
    }

    SECTION("Test with sorted array")
    {
        int arr[] = {1, 2, 3, 4, 5};
        int expected[] = {1, 2, 3, 4, 5};
        int size = sizeof(arr) / sizeof(arr[0]);

        merge_sort(arr, size);

        REQUIRE(std::equal(arr, arr + size, expected));
    }

    SECTION("Test with reverse sorted array")
    {
        int arr[] = {5, 4, 3, 2, 1};
        int expected[] = {1, 2, 3, 4, 5};
        int size = sizeof(arr) / sizeof(arr[0]);

        merge_sort(arr, size);

        REQUIRE(std::equal(arr, arr + size, expected));
    }

    SECTION("Test with unsorted array")
    {
        int arr[] = {3, 1, 4, 2, 5, 7, 10, 9, 8, 6};
        int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int size = sizeof(arr) / sizeof(arr[0]);

        merge_sort(arr, size);

        REQUIRE(std::equal(arr, arr + size, expected));
    }
}
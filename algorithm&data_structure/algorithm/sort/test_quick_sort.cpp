// #define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "quick_sort.h"
#include "common.h"

TEST_CASE("Test quick_sort", "[sort]")
{
    SECTION("Test with empty array")
    {
        int arr[] = {};
        int expected[] = {};
        int size = sizeof(arr) / sizeof(arr[0]);

        quick_sort(arr, size);

        REQUIRE(std::equal(arr, arr + size, expected));
    }

    SECTION("Test with sorted array")
    {
        int arr[] = {1, 2, 3, 4, 5};
        int expected[] = {1, 2, 3, 4, 5};
        int size = sizeof(arr) / sizeof(arr[0]);

        quick_sort(arr, size);
        //print(arr, size);

        REQUIRE(std::equal(arr, arr + size, expected));
    }

    SECTION("Test with reverse sorted array")
    {
        int arr[] = {5, 4, 3, 2, 1};
        int expected[] = {1, 2, 3, 4, 5};
        int size = sizeof(arr) / sizeof(arr[0]);

        quick_sort(arr, size);

        REQUIRE(std::equal(arr, arr + size, expected));
    }

    SECTION("Test with unsorted array")
    {
        int arr[] = {3, 1, 4, 2, 5, 7, 10, 9, 8, 6};
        int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int size = sizeof(arr) / sizeof(arr[0]);

        quick_sort(arr, size);

        REQUIRE(std::equal(arr, arr + size, expected));
    }

    SECTION("Test with duplicated elements")
    {
        int arr[] = {3, 1, 4, 2, 5, 7, 10, 9, 8, 6, 8, 8, 7, 6, 4, 6, 5};
        int expected[] = {1, 2, 3, 4, 4, 5, 5, 6, 6, 6, 7, 7, 8, 8, 8, 9, 10};
        int size = sizeof(arr) / sizeof(arr[0]);

        quick_sort(arr, size);
        //print(arr, size);

        REQUIRE(std::equal(arr, arr + size, expected));
    }
}

TEST_CASE("Test find_median", "[median]")
{
    SECTION("Test with array")
    {
        int arr[] = {1, 2, 3};
        int size = sizeof(arr) / sizeof(arr[0]);

        int median = find_median(arr, 0, (size - 1) / 2, size - 1);
        REQUIRE(median == 1);
    }

    SECTION("Test with array2")
    {
        int arr[] = {2, 1, 3};
        int size = sizeof(arr) / sizeof(arr[0]);

        int median = find_median(arr, 0, (size - 1) / 2, size - 1);
        REQUIRE(median == 0);
    }

    SECTION("Test with array3")
    {
        int arr[] = {1, 2, 2};
        int size = sizeof(arr) / sizeof(arr[0]);

        int median = find_median(arr, 0, (size - 1) / 2, size - 1);
        REQUIRE(median == 2);
    }

    SECTION("Test with array4")
    {
        int arr[] = {5, 1, 4, 2, 3};
        int size = sizeof(arr) / sizeof(arr[0]);

        int median = find_median(arr, 0, (size - 1) / 2, size - 1);
        REQUIRE(median == 2);
    }
}

TEST_CASE("Test quick_3way", "[sort]")
{
    SECTION("Test with empty array")
    {
        int arr[] = {};
        int expected[] = {};
        int size = sizeof(arr) / sizeof(arr[0]);

        quick_3way(arr, size);

        REQUIRE(std::equal(arr, arr + size, expected));
    }

    SECTION("Test with sorted array")
    {
        int arr[] = {1, 2, 3, 4, 5};
        int expected[] = {1, 2, 3, 4, 5};
        int size = sizeof(arr) / sizeof(arr[0]);

        quick_3way(arr, size);

        REQUIRE(std::equal(arr, arr + size, expected));
    }

    SECTION("Test with reverse sorted array")
    {
        int arr[] = {5, 4, 3, 2, 1};
        int expected[] = {1, 2, 3, 4, 5};
        int size = sizeof(arr) / sizeof(arr[0]);

        quick_3way(arr, size);

        REQUIRE(std::equal(arr, arr + size, expected));
    }

    SECTION("Test with unsorted array")
    {
        int arr[] = {3, 1, 4, 2, 5, 7, 10, 9, 8, 6};
        int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int size = sizeof(arr) / sizeof(arr[0]);

        quick_3way(arr, size);

        REQUIRE(std::equal(arr, arr + size, expected));
    }

    SECTION("Test with duplicated elements")
    {
        int arr[] = {3, 1, 4, 2, 5, 7, 10, 9, 8, 6, 8, 8, 7, 6, 4, 6, 5};
        int expected[] = {1, 2, 3, 4, 4, 5, 5, 6, 6, 6, 7, 7, 8, 8, 8, 9, 10};
        int size = sizeof(arr) / sizeof(arr[0]);

        quick_3way(arr, size);

        REQUIRE(std::equal(arr, arr + size, expected));
    }
}
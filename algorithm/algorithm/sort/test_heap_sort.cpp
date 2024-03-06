#include "catch.hpp"
#include "heap_sort.h"

TEST_CASE("Test heap_sort", "[heap sort]")
{
    SECTION("Test with empty element")
    {
        int arr[] = {};
        int expected[] = {};
        int size = sizeof(arr) / sizeof(arr[0]);

        heap_sort(arr, size);

        REQUIRE(std::equal(arr, arr + size, expected));
    }

    SECTION("Test with single element")
    {
        int arr[] = {5};
        int expected[] = {5};
        int size = sizeof(arr) / sizeof(arr[0]);

        heap_sort(arr, size);

        REQUIRE(std::equal(arr, arr + size, expected));
    }

    SECTION("Test with two elements")
    {
        int arr[] = {5, 3};
        int expected[] = {3, 5};
        int size = sizeof(arr) / sizeof(arr[0]);

        heap_sort(arr, size);

        REQUIRE(std::equal(arr, arr + size, expected));
    }

    SECTION("Test with three elements")
    {
        int arr[] = {5, 3, 7};
        int expected[] = {3, 5, 7};
        int size = sizeof(arr) / sizeof(arr[0]);

        heap_sort(arr, size);

        REQUIRE(std::equal(arr, arr + size, expected));
    }

    SECTION("Test with larger array")
    {
        int arr[] = {9, 7, 5, 3, 1};
        int expected[] = {1, 3, 5, 7, 9};
        int size = sizeof(arr) / sizeof(arr[0]);

        heap_sort(arr, size);

        REQUIRE(std::equal(arr, arr + size, expected));
    }
}
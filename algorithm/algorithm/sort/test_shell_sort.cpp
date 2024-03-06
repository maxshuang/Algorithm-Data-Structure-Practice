#include "catch.hpp"
#include "shell_sort.h"

TEST_CASE("Test shellsort", "[sort]") {
    SECTION("Test with empty array") {
        int arr[] = {};
        int expected[] = {};
        int size = sizeof(arr) / sizeof(arr[0]);
        int factor = 2;

        shellsort(arr, size, factor);

        REQUIRE(std::equal(arr, arr + size, expected));
    }

    SECTION("Test with sorted array") {
        int arr[] = {1, 2, 3, 4, 5};
        int expected[] = {1, 2, 3, 4, 5};
        int size = sizeof(arr) / sizeof(arr[0]);
        int factor = 2;

        shellsort(arr, size, factor);

        REQUIRE(std::equal(arr, arr + size, expected));
    }

    SECTION("Test with reverse sorted array") {
        int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int size = sizeof(arr) / sizeof(arr[0]);
        int factor = 2;

        shellsort(arr, size, factor);

        REQUIRE(std::equal(arr, arr + size, expected));
    }

    SECTION("Test with unsorted array") {
        int arr[] = {3, 1, 4, 2, 5, 6, 10, 7, 8, 9};
        int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int size = sizeof(arr) / sizeof(arr[0]);
        int factor = 3;

        shellsort(arr, size, factor);

        REQUIRE(std::equal(arr, arr + size, expected));
    }
}
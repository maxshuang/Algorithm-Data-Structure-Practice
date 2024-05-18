#include "catch.hpp"
#include "counting_sort.h"

TEST_CASE("Test counting_sort", "[counting_sort]")
{
    SECTION("Test sorting positive integers")
    {
        int arr[] = {4, 2, 1, 3, 5};
        int expected[] = {1, 2, 3, 4, 5};
        int size = sizeof(arr) / sizeof(arr[0]);
        counting_sort(arr, size, 5);

        std::equal(arr, arr + size, expected);
    }

    SECTION("Test sorting with duplicate elements")
    {
        int arr[] = {4, 2, 1, 3, 5, 2, 4, 1, 1};
        int expected[] = {1, 1, 1, 2, 2, 3, 4, 4, 5};
        int size = sizeof(arr) / sizeof(arr[0]);
        counting_sort(arr, size, 5);

        std::equal(arr, arr + size, expected);
    }
}
#include "catch.hpp"
#include "common.h"

TEST_CASE("Test upper_bound", "[upper_bound]")
{
    SECTION("Test with empty array")
    {
        int arr[] = {};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 5;
        REQUIRE(upper_bound(arr, 0, size - 1, target) == -1);
    }

    SECTION("Test with array of size 1")
    {
        int arr[] = {3};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 5;
        REQUIRE(upper_bound(arr, 0, size - 1, target) == -1);
    }

    SECTION("Test with array of size 5")
    {
        int arr[] = {1, 3, 5, 7, 9};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 5;
        REQUIRE(upper_bound(arr, 0, size - 1, target) == 3);
    }

    SECTION("Test with array of size 5 and target not found")
    {
        int arr[] = {1, 3, 5, 7, 9};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 6;
        REQUIRE(upper_bound(arr, 0, size - 1, target) == 3);
    }

    SECTION("Test with array of size 5 and target at the end")
    {
        int arr[] = {1, 3, 5, 7, 9};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 9;
        REQUIRE(upper_bound(arr, 0, size - 1, target) == -1);
    }

    SECTION("Test with array of size 5 and target not found")
    {
        int arr[] = {10, 11, 12, 13, 14};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 9;
        REQUIRE(lower_bound(arr, 0, size - 1, target) == 0);
    }

    SECTION("Test with array of size 5 and target at the first")
    {
        int arr[] = {9, 11, 12, 13, 14};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 9;
        REQUIRE(lower_bound(arr, 0, size - 1, target) == 0);
    }
}
TEST_CASE("Test lower_bound", "[lower_bound]")
{
    SECTION("Test with empty array")
    {
        int arr[] = {};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 5;
        REQUIRE(lower_bound(arr, 0, size - 1, target) == -1);
    }

    SECTION("Test with array of size 1")
    {
        int arr[] = {3};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 5;
        REQUIRE(lower_bound(arr, 0, size - 1, target) == -1);
    }

    SECTION("Test with array of size 5")
    {
        int arr[] = {1, 3, 5, 7, 9};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 5;
        REQUIRE(lower_bound(arr, 0, size - 1, target) == 2);
    }

    SECTION("Test with array of size 5 and target not found")
    {
        int arr[] = {1, 3, 5, 7, 9};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 6;
        REQUIRE(lower_bound(arr, 0, size - 1, target) == 3);
    }

    SECTION("Test with array of size 5 and target at the end")
    {
        int arr[] = {1, 3, 5, 7, 9};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 9;
        REQUIRE(lower_bound(arr, 0, size - 1, target) == 4);
    }

    SECTION("Test with array of size 5 and target not found")
    {
        int arr[] = {10, 11, 12, 13, 14};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 9;
        REQUIRE(lower_bound(arr, 0, size - 1, target) == 0);
    }

    SECTION("Test with array of size 5 and target at the first")
    {
        int arr[] = {9, 11, 12, 13, 14};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 9;
        REQUIRE(lower_bound(arr, 0, size - 1, target) == 0);
    }
}

TEST_CASE("Test left_bound", "[left_bound]")
{
    SECTION("Test with empty array")
    {
        int arr[] = {};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 5;
        REQUIRE(left_bound(arr, 0, size - 1, target) == -1);
    }

    SECTION("Test with array of size 1")
    {
        int arr[] = {3};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 5;
        REQUIRE(left_bound(arr, 0, size - 1, target) == -1);
    }

    SECTION("Test with array of size 5")
    {
        int arr[] = {1, 3, 5, 7, 9};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 5;
        REQUIRE(left_bound(arr, 0, size - 1, target) == 2);
    }

    SECTION("Test with array of size 5 and target not found")
    {
        int arr[] = {1, 3, 5, 7, 9};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 6;
        REQUIRE(left_bound(arr, 0, size - 1, target) == -1);
    }

    SECTION("Test with array of size 5 and target at the end")
    {
        int arr[] = {1, 3, 5, 7, 9};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 9;
        REQUIRE(left_bound(arr, 0, size - 1, target) == 4);
    }

    SECTION("Test with array of size 5 and target not found")
    {
        int arr[] = {10, 11, 12, 13, 14};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 9;
        REQUIRE(left_bound(arr, 0, size - 1, target) == -1);
    }

    SECTION("Test with array of size 5 and target at the first")
    {
        int arr[] = {9, 11, 12, 13, 14};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 9;
        REQUIRE(left_bound(arr, 0, size - 1, target) == 0);
    }

    SECTION("Test with array of size 7 and target at the middle")
    {
        int arr[] = {9, 11, 12, 12, 12, 13, 14};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 12;
        REQUIRE(left_bound(arr, 0, size - 1, target) == 2);
    }
}

TEST_CASE("Test right_bound", "[right_bound]")
{
    SECTION("Test with empty array")
    {
        int arr[] = {};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 5;
        REQUIRE(right_bound(arr, 0, size - 1, target) == -1);
    }

    SECTION("Test with array of size 1")
    {
        int arr[] = {3};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 5;
        REQUIRE(right_bound(arr, 0, size - 1, target) == -1);
    }

    SECTION("Test with array of size 5")
    {
        int arr[] = {1, 3, 5, 7, 9};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 5;
        REQUIRE(right_bound(arr, 0, size - 1, target) == 2);
    }

    SECTION("Test with array of size 5 and target not found")
    {
        int arr[] = {1, 3, 5, 7, 9};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 6;
        REQUIRE(right_bound(arr, 0, size - 1, target) == -1);
    }

    SECTION("Test with array of size 5 and target at the end")
    {
        int arr[] = {1, 3, 5, 7, 9};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 9;
        REQUIRE(right_bound(arr, 0, size - 1, target) == 4);
    }

    SECTION("Test with array of size 5 and target not found")
    {
        int arr[] = {10, 11, 12, 13, 14};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 9;
        REQUIRE(right_bound(arr, 0, size - 1, target) == -1);
    }

    SECTION("Test with array of size 5 and target at the first")
    {
        int arr[] = {9, 11, 12, 13, 14};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 9;
        REQUIRE(right_bound(arr, 0, size - 1, target) == 0);
    }

    SECTION("Test with array of size 7 and target at the middle")
    {
        int arr[] = {9, 11, 12, 12, 12, 13, 14};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 12;
        REQUIRE(right_bound(arr, 0, size - 1, target) == 4);
    }
}

TEST_CASE("Test last_smaller_bound", "[last_smaller_bound]")
{
    SECTION("Test with empty array")
    {
        int arr[] = {};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 5;
        REQUIRE(last_smaller_bound(arr, 0, size - 1, target) == -1);
    }

    SECTION("Test with array of size 1")
    {
        int arr[] = {3};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 5;
        REQUIRE(last_smaller_bound(arr, 0, size - 1, target) == 0);
    }

    SECTION("Test with array of size 5")
    {
        int arr[] = {1, 3, 5, 7, 9};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 5;
        REQUIRE(last_smaller_bound(arr, 0, size - 1, target) == 1);
    }

    SECTION("Test with array of size 5 and target not found")
    {
        int arr[] = {1, 3, 5, 7, 9};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 6;
        REQUIRE(last_smaller_bound(arr, 0, size - 1, target) == 2);
    }

    SECTION("Test with array of size 5 and target at the end")
    {
        int arr[] = {1, 3, 5, 7, 9};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 9;
        REQUIRE(last_smaller_bound(arr, 0, size - 1, target) == 3);
    }

    SECTION("Test with array of size 5 and target not found")
    {
        int arr[] = {10, 11, 12, 13, 14};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 9;
        REQUIRE(last_smaller_bound(arr, 0, size - 1, target) == -1);
    }

    SECTION("Test with array of size 5 and target at the first")
    {
        int arr[] = {9, 11, 12, 13, 14};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 9;
        REQUIRE(last_smaller_bound(arr, 0, size - 1, target) == -1);
    }

    SECTION("Test with array of size 7 and target at the middle")
    {
        int arr[] = {9, 11, 12, 12, 12, 13, 14};
        int size = sizeof(arr) / sizeof(arr[0]);
        int target = 12;
        REQUIRE(last_smaller_bound(arr, 0, size - 1, target) == 1);
    }
}

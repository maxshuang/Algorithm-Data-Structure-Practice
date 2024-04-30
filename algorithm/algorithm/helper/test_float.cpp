#include "catch.hpp"
#include "float.hpp"

TEST_CASE("Test std::equal", "")
{
    double a = 1.1;
    a += 2.33;

    REQUIRE(DoubleEqual2(a, 3.43));
}
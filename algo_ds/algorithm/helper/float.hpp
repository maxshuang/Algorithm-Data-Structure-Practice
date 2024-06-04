#pragma once
#include <cmath>
#include <limits>
#include <functional>

inline bool DoubleEqual(double t, double o)
{
    return std::fabs(t - o) <= std::numeric_limits<double>::epsilon();
}

inline bool DoubleEqual2(double t, double o)
{
    return std::equal_to<double>()(t, o);
}
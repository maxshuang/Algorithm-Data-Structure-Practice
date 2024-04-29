#pragma once
#include <cmath>
#include <limits>

inline bool DoubleEqual(double t, double o)
{
    return std::fabs(t - o) <= std::numeric_limits<double>::epsilon();
}
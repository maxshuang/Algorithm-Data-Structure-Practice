#pragma once
#include <iostream>

inline void exchange(int *vec, int m, int n)
{
    int tmp = vec[m];
    vec[m] = vec[n];
    vec[n] = tmp;
}

inline void print(int *vec, int l, int r)
{
    std::cout << "l:" << l << " r:" << r << std::endl;
    std::cout << "[";
    for (int i = l; i < r; ++i)
    {
        std::cout << vec[i] << ",";
    }
    std::cout << "]" << std::endl;
}

inline void print(int *vec, int num)
{
    print(vec, 0, num);
}

// upper_bound: first one larger than target
// lower_bound: first one not less than target
//
// right_bound: the last one equal to target
// left_bound: the first one equal to target
//
// last_smaller_bound: the last one smaller than target

//  a bit difficult to implement
inline int upper_bound(int *vec, int l, int r, int target)
{
    int i = l, j = r;
    while (i <= j)
    {
        int m = i + (j - i) / 2;
        if (vec[m] <= target)
        {
            i = m + 1;
        }
        else
        {
            j = m - 1;
        }
    }

    // not found
    if (i == r + 1)
        return -1;

    // only one condition: j+1=i
    return i;
}

inline int lower_bound(int *vec, int l, int r, int target)
{
    int i = l, j = r;
    while (i <= j)
    {
        int m = i + (j - i) / 2;
        if (vec[m] < target)
        {
            i = m + 1;
        }
        else
        {
            j = m - 1;
        }
    }

    // not found
    if (i == r + 1)
        return -1;

    return i;
}

inline int left_bound(int *vec, int l, int r, int target)
{
    int ind = lower_bound(vec, l, r, target);
    if (ind == -1 || vec[ind] != target)
        return -1;

    return ind;
}

inline int right_bound(int *vec, int l, int r, int target)
{
    int ind = upper_bound(vec, l, r, target);
    if (ind == -1 && vec[r] == target)
        return r;
    if (vec[ind - 1] != target)
        return -1;

    return ind - 1;
}

inline int last_smaller_bound(int *vec, int l, int r, int target)
{
    int ind = lower_bound(vec, l, r, target);
    if (ind == -1)
        return r;
    if (ind == 0)
        return -1;

    return ind - 1;
}
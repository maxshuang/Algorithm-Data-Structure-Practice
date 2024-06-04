#pragma once
#include <iostream>
#include <vector>

inline void exchange(int *vec, int m, int n) {
    int tmp=vec[m];
    vec[m]=vec[n];
    vec[n]=tmp;
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

inline void print(const std::vector<int> &vec, int num)
{
    std::cout << "l:" << 0 << " r:" << num-1 << std::endl;
    std::cout << "[";
    for (int i = 0; i < num; ++i)
    {
        std::cout << vec[i] << ",";
    }
    std::cout << "]" << std::endl;
}
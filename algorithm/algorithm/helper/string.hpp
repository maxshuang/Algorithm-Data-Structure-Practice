#pragma once
#include <string>
#include <vector>


inline std::string toString(std::vector<int> v) {
    std::string s = "[";
    for (int i = 0; i < (int)v.size(); i++) {
        s += std::to_string(v[i]);
        if (i < (int)v.size() - 1) {
            s += ", ";
        }
    }
    s += "]";
    return s;
}
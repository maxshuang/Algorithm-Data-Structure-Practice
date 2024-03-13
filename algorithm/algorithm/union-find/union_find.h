#pragma once
#include <vector>

class UnionFind{
public:
    UnionFind(int n): parent_(n), size_(n,1), depth_(n, 0), connected_count_(n){
        for (int i = 0; i < n; ++i) {
            parent_[i] = i;
        }
    }
    int Find(int p);
    void Union(int p, int q);
    bool Connected(int p, int q);
    int ConnectedCount() { return connected_count_; }
    int MaxDepth();

private:
    std::vector<int> parent_;
    std::vector<int> size_;
    std::vector<int> depth_;
    // use connected_count_ to avoid O(N) time complexity
    int connected_count_;
};
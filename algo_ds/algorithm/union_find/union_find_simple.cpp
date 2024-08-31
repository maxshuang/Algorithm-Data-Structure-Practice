#include <vector>

class UnionFind {
private:
    std::vector<int> parent;

public:
    // Constructor: Initialize parent array.
    UnionFind(int size) {
        parent.resize(size);
        for (int i = 0; i < size; ++i) {
            parent[i] = i; // Initially, each node is its own parent
        }
    }

    // Find with path compression
    // recursion to find the root and set the root to all nodes along the path
    // compress the depth to 1
    int find(int node) {
        if (parent[node] != node) {
            parent[node] = find(parent[node]); // Path compression: point to the root
        }
        return parent[node];
    }

    // Union operation: Attach the root of one tree to the root of the other
    void unions(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV) {
            parent[rootU] = rootV; // Attach one tree's root under the other
        }
    }

    // Check if two elements are in the same set
    bool connected(int u, int v) {
        return find(u) == find(v);
    }
};

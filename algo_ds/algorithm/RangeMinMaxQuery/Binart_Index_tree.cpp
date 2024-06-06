#include <iostream>
#include <vector>
#include "catch.hpp"

using namespace std;

class BIT {
private:
    vector<int> tree;
    int n;

    int lowBit(int x) {
        return x & -x;
    }

    int getSum(int index) {
        int sum = 0;
        while (index > 0) {
            sum += tree[index];
            index -= lowBit(index);
        }
        return sum;
    }

    void updateTree(int index, int val) {
        while (index <= n) {
            tree[index] += val;
            index += lowBit(index);
        }
    }

public:
    BIT(int size) : n(size) {
        tree.resize(n + 1, 0);
    }

    void update(int i, int val) {
        updateTree(i + 1, val);
    }

    // for 1 to i
    int query(int i) {
        return getSum(i);
    }

    int queryRange(int l, int r) {
        return getSum(r) - getSum(l - 1);
    }
};

TEST_CASE("Test Binary Index Tree", "") {
    int arr[] = {3, 2, 5, 4, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    BIT bit(n);

    for (int i = 0; i < n; ++i) {
        bit.update(i, arr[i]);
    }

    REQUIRE(bit.queryRange(0, 2)==5);
    bit.update(2, 3);
    REQUIRE(bit.queryRange(0, 2)==5);
}
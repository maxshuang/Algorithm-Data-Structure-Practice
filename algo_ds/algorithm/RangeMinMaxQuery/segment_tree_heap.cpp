#include <vector>
#include <string.h>
#include "catch.hpp"

struct SegmentTreeHeap {
    struct TreeNode {
        int sum;
        int lazyTag; // for all next level nodes
    };

    const static int MAXNODE=100;
    // complete tree of MAXNODE leaf nodes has (4*MAXNODE-5) nodes
    TreeNode nodes[4*MAXNODE];    

    int size;

    SegmentTreeHeap(const std::vector<int>& arr) {
        size=arr.size();
        memset(nodes, 0, sizeof(nodes));
        build(arr, 0, arr.size()-1, 1); 
    }

    void build(const std::vector<int>& arr, int s, int t, int p) {
        if (s == t) {
            nodes[p].sum = arr[s];
            return;
        }
        int m = s + ((t - s) >> 1);
        build(arr, s, m, p * 2);
        build(arr, m + 1, t, p * 2 + 1);
        nodes[p].sum = nodes[p * 2].sum + nodes[(p * 2) + 1].sum;
    }

    int queryRange(int l, int r) {
        return queryRangeRecur(l, r, 0, size-1, 1);
    }

    // [l, r] is the query range, [s, t] is the current range
    int queryRangeRecur(int l, int r, int s, int t, int p) {
        if(l<=s && t<=r) {
            return nodes[p].sum;
        }

        int m = s + ((t - s) >> 1);
         // push down lazy tag to its children nodes
        if(nodes[p].lazyTag != 0) {
            nodes[2*p].sum=(m-s+1)*nodes[p].lazyTag, nodes[2*p].lazyTag+=nodes[p].lazyTag;
            nodes[2*p+1].sum=(t-m)*nodes[p].lazyTag, nodes[2*p+1].lazyTag+=nodes[p].lazyTag;
            nodes[p].lazyTag=0;
        }

        int sum=0;
        if(l<=m) sum+=queryRangeRecur(l, r, s, m, 2*p);
        if(m<r) sum+=queryRangeRecur(l, r, m+1, t, 2*p+1);
        return sum;
    }

    void updateRange(int l, int r, int v) {
        return updateRangeRecur(l, r, v, 0, size-1, 1);
    }

    // [l, r] is the update range, [s, t] is the current range
    void updateRangeRecur(int l, int r, int v, int s, int t, int p) {
        if(l<=s && t<=r) {
            // cover range
            nodes[p].sum+=(t-s+1)*v;
            nodes[p].lazyTag+=v;
            return;
        }

        // interval range
        // [NOTE]: take care of the priority of >>
        int m=s+((t-s)>>1);
        // push down lazy tag to its children nodes
        if(nodes[p].lazyTag != 0) {
            nodes[2*p].sum=(m-s+1)*nodes[p].lazyTag, nodes[2*p].lazyTag+=nodes[p].lazyTag;
            nodes[2*p+1].sum=(t-m)*nodes[p].lazyTag, nodes[2*p+1].lazyTag+=nodes[p].lazyTag;
            nodes[p].lazyTag=0;
        }

        // |___________|
        // s           t
        //    |____|
        //    l    r
        if(l<=m) updateRangeRecur(l, r, v, s, m, 2*p);
        if(m<r) updateRangeRecur(l, r, v, m+1, t, 2*p+1);
        // we need to update current node according to the aboved partial updates 
        nodes[p].sum=nodes[2*p].sum+nodes[2*p+1].sum;
        return;
    }
};

TEST_CASE("Test Segment Tree heap", "") {
    std::vector<int> arr{3, 2, 5, 4, 7};
    SegmentTreeHeap st(arr);

    REQUIRE(st.queryRange(0, 1)==5);
    st.updateRange(2, 3, 5);
    REQUIRE(st.queryRange(0, 3)==24);
}


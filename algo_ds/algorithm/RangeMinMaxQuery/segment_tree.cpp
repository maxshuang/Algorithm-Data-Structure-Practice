#include <vector>
#include "catch.hpp"

struct Range {
    int l;
    int r;

    Range(int l, int r): l(l), r(r){}
};

struct TreeNode {
    TreeNode* left;
    TreeNode* right;
    int sum;
    Range range;

    TreeNode(TreeNode* left, TreeNode* right, Range r): left(left), 
        right(right), sum(0), range(r){}
};

struct SegmentTree {
    TreeNode root;

    SegmentTree(const std::vector<int>& arr): root(nullptr, nullptr, Range{0, arr.size()-1}) {
        build_dfs(&root, arr, 0, arr.size()-1);
    }

    void build_dfs(TreeNode* root, const std::vector<int>& arr, int l, int r) {
        if(l==r) {
            root->sum=arr[l];
            return;
        }

        int m = l + ((r - l) >> 1);
        root->left=new TreeNode(nullptr, nullptr, Range{l, m});
        root->right=new TreeNode(nullptr, nullptr, Range{m+1, r});
        build_dfs(root->left, arr, l, m);
        build_dfs(root->right, arr, m+1, r);

        root->sum=root->left->sum + root->right->sum;
    } 
};

#if 0
TEST_CASE("Test Segment Tree", "") {
    std::vector<int> arr{3, 2, 5, 4, 7};
    SegmentTree st(arr);

    REQUIRE(st.queryRange(0, 2)==5);
    bit.update(2, 3);
    REQUIRE(bit.queryRange(0, 2)==5);
}
#endif
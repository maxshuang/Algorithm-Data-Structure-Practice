/*
给定一个二叉树，它的每个结点都存放着一个整数值。

找出路径和等于给定数值的路径总数。

路径不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。

二叉树不超过 1000 个节点，且节点数值范围是 [-1000000,1000000] 的整数。

示例：

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

返回 3。和等于 8 的路径有：

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11
*/

/*
Good Problem with some tricks and corner case.
Solution: 
1. DFS, Time Complexity: O(N^2), Space Complexity: O(1)

2. This is another range sum in tree, but it's the range sum problem essentially, we can use PrefixSum solution to solve it.
a single round of DFS can get the prefix-sum for all nodes. then for each node, to check whether there exists any path meets the target sum
it can transform this problem into a search problem because we only want to know whether it's existed.
Time Complexity: O(N)
Space Complexity: O(N)
*/

#include <unordered_map>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) return 0;
        return count(root, targetSum) + pathSum(root->left, targetSum) + pathSum(root->right, targetSum);
    }

    int count(struct TreeNode *root, long sum) {
        if(root==nullptr) return 0;
        return (root->val==sum) + count(root->left, sum-root->val) + count(root->right, sum-root->val);
    }
};

class Solution2 {
    // may exists same prefix-sum, only for the current path
    std::unordered_map<long long, int> preSum;
    long long pSum;
    int res;
public:
    int pathSum(TreeNode* root, int targetSum) {
        pSum=0;
        dfs(root, targetSum);
        return res;
    }

    // prefix-sum solution
    void dfs(TreeNode* root, int targetSum) {
        if(root==nullptr) return;

        pSum+=root->val;
        // check for the history path
        if(preSum.count(pSum-targetSum)) {
            res+=preSum[pSum-targetSum];
        }

        // we should check current path after checking the history path to avoid corner case: targetSum==0
        if(pSum==targetSum) ++res;
        // add to the path
        preSum[pSum]+=1;

        dfs(root->left, targetSum);
        dfs(root->right, targetSum);

        // backtrace the path
        preSum[pSum]-=1;
        pSum-=root->val;
    }
};
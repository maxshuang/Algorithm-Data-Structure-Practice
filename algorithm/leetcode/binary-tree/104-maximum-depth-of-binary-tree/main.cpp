/*
 Given the root of a binary tree, return its maximum depth.
A binary tree's maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

Constraints:
The number of nodes in the tree is in the range [0, 104].
-100 <= Node.val <= 100
 */

#include <algorithm>
#include "../tree.hpp"

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(root==nullptr){
            return 0;
        }

        // post-order DFS
        int maxLeft=maxDepth(root->left);
        int maxRight=maxDepth(root->right);
        return 1+std::max(maxLeft, maxRight);
    }
};

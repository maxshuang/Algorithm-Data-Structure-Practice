/*
 * Given the root of a binary tree, return the length of the diameter of the tree.
The diameter of a binary tree is the length of the longest path between any two nodes in a tree. 
This path may or may not pass through the root.
The length of a path between two nodes is represented by the number of edges between them.

Constraints:
The number of nodes in the tree is in the range [1, 104].
-100 <= Node.val <= 100
 */

#include <algorithm>
#include "../tree.hpp"

class Solution {
    // use node count here, -1 when we need length of path
    int max_diameter=1;
public:
    int diameterOfBinaryTree(TreeNode* root) {
        depth_dfs(root);
        // length of path=node count - 1
        return max_diameter-1;
    }

    int depth_dfs(TreeNode *root) {
        if(!root) return 0;

        int ld=depth_dfs(root->left);
        int rd=depth_dfs(root->right);
        
        // we use node count here, so add root node 
        max_diameter=std::max(max_diameter, ld+rd+1);

        // we calculate the node count here, so add root node
        return std::max(ld, rd)+1;
    }
};

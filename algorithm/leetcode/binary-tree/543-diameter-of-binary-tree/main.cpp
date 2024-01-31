/*
 * Given the root of a binary tree, return the length of the diameter of the tree.
The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.
The length of a path between two nodes is represented by the number of edges between them.

Constraints:
The number of nodes in the tree is in the range [1, 104].
-100 <= Node.val <= 100
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    int maxRes;
public:
    int diameterOfBinaryTree(TreeNode* root) {
        maxDeepest(root);
        return maxRes;
    }

    // postorder traversal
    int maxDeepest(TreeNode* root){
        if(root==nullptr){
            return 0;
        }

        int maxLeft=maxDeepest(root->left);
        int maxRight=maxDeepest(root->right);

        // update the diameter
        maxRes=max(maxRes, maxLeft+maxRight);

        // return the deepth of the root
        return 1+max(maxLeft, maxRight);
    }
};

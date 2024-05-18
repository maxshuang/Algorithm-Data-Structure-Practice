/*
 *Given the root of a binary tree, return the preorder traversal of its nodes' values.

 Constraints:
The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100
 */

#include <vector>
#include "../tree.hpp"
class Solution {
public:
    std::vector<int> preorderTraversal(TreeNode* root) {
        std::vector<int> res;
        traverse(root, res);
        return res;
    }

    void traverse(TreeNode* root, std::vector<int>& res) {
        if(root==nullptr){
            return;
        }

        res.push_back(root->val);
        traverse(root->left, res);
        traverse(root->right, res);
    }
};

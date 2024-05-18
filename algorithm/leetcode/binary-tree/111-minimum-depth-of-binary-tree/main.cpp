/*
 * Given a binary tree, find its minimum depth.
The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
Note: A leaf is a node with no children.

 Constraints:
The number of nodes in the tree is in the range [0, 105].
-1000 <= Node.val <= 1000
 */

#include <queue>
#include "../tree.hpp"

class Solution {
public:
    int minDepth(TreeNode* root) {
        if(root==nullptr) return 0;

        int depth=1;
        std::queue<TreeNode*> q;
        q.push(root);
        while(q.size()!=0) {
            // we scan a layer at one time
            int size=q.size();
            for(int i=0; i<size; ++i) {
                TreeNode* cur=q.front();
                q.pop();
                // check if leaf node
                if(cur->left==nullptr&&cur->right==nullptr){
                    return depth;
                }

                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
            ++depth;
        }

        return depth;
    }
};

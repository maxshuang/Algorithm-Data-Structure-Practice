#include <unordered_map>

/**
 * Single LCA Time Complexity is O(N), Space Complexity is O(N).
 * LCA is a key component for solving the shortest path between two nodes on the tree because the LCA must on the shortest path.
 * shortest_path(a, b)=h(a)+h(b)-2*h(lca)
 * For frequent LCA, we can use binary lifting to achieve O(logN) for each LCA operation.
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};  

class Solution {
public:
    TreeNode* LowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q) {
            return root;
        }
        TreeNode* left = LowestCommonAncestor(root->left, p, q);
        TreeNode* right = LowestCommonAncestor(root->right, p, q);
        if (left == nullptr) {
            return right;
        }
        if (right == nullptr) {
            return left;
        }
        return root;
    }
};

// This solution is more comprehensive.
class Solution2 {
public:
    // For saving the father node
    std::unordered_map<int, TreeNode*> fa;
    // marked the path from node to root
    std::unordered_map<int, bool> vis;
    void dfs(TreeNode* root){
        if (root->left != nullptr) {
            fa[root->left->val] = root;
            dfs(root->left);
        }
        if (root->right != nullptr) {
            fa[root->right->val] = root;
            dfs(root->right);
        }
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        fa[root->val] = nullptr;
        dfs(root);
        while (p != nullptr) {
            vis[p->val] = true;
            p = fa[p->val];
        }
        while (q != nullptr) {
            if (vis[q->val]) return q;
            q = fa[q->val];
        }
        return nullptr;
    }
};
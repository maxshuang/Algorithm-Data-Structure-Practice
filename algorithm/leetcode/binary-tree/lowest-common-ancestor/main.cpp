

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};  


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
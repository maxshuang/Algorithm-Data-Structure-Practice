#include <vector>
#include <map>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// Very interesting algorithm for lca

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    int depth;
};

const int MAXLEVEL = 10, MAX_NODE=1000;

// Father_X_I is the 2^i fathers of a node
typedef std::vector<TreeNode*> Father_X_I;
std::map<TreeNode*, Father_X_I> fathers;

// table for lg2
std::vector<int> lg2(MAX_NODE, 0);

void initLG2() {
    for(size_t i=2; i<lg2.size(); ++i) {
        lg2[i]=lg2[i/2]+1;
    }
}

void dfs(TreeNode* node, TreeNode* fa) {
    if(!node) return;

    // update depth
    if(fa) node->depth=fa->depth+1;

    // update father relationship
    if(fathers.count(node)==0) {
        fathers.insert(std::make_pair(node, Father_X_I(MAXLEVEL, nullptr)));
    }
    fathers[node][0]=fa;

    // all fathers have been set before
    for(int i=1; i<=lg2[node->depth]; ++i) {
        fathers[node][i]=fathers[fathers[node][i-1]][i-1];   // 2^i=2^(i-1)+2^(i-1)
    }

    dfs(node->left, node);
    dfs(node->right, node);
}

// O(NlogN) for preprocess, O(N) for DFS, O(logN) for building father relationship for each node
void init(TreeNode* root) {
    initLG2();
    // preprocess, get node's depth and father relationship
    dfs(root, nullptr);
}

// O(logN) for each search
TreeNode* findLCA(TreeNode *root, TreeNode *p, TreeNode *q) {
    // move p and q to the same level
    // let p be the lower one
    if(p->depth<q->depth) {
        std::swap(p, q);
    }

    // move p to the same depth with q
    while(p->depth != q->depth) {
        int diff = lg2[p->depth-q->depth];
        p=fathers[p][diff];
    }

    // p or q is the lca
    if(p==q) return p;

    // p and q jumps to the lca
    for(int k=lg2[p->depth-root->depth]; k>=0; --k) {
        // nodes precedent to lca will all be the same
        if(fathers[p][k]!=fathers[q][k]) {
            p=fathers[p][k];
            q=fathers[q][k];
        }
    }

    return fathers[p][0]; // father is the lca
}

/*
*  
# 构建示例树
#        1
#       / \
#      2   3
#     / \
#    4   5
*/
TEST_CASE("Test binary lifting", "tree")
{
    TreeNode nodes[100];
    nodes[1]=TreeNode{1, &nodes[2], &nodes[3], 0};
    nodes[2]=TreeNode{2, &nodes[4], &nodes[5], 0};
    nodes[3]=TreeNode{3, nullptr, nullptr, 0};
    nodes[4]=TreeNode{4, nullptr, nullptr, 0};
    nodes[5]=TreeNode{5, nullptr, nullptr, 0};

    init(&nodes[1]);
    REQUIRE(findLCA(&nodes[1], &nodes[4], &nodes[5])==&nodes[2]);
    REQUIRE(findLCA(&nodes[1], &nodes[4], &nodes[3])==&nodes[1]);
    REQUIRE(findLCA(&nodes[1], &nodes[2], &nodes[5])==&nodes[2]);
    REQUIRE(findLCA(&nodes[1], &nodes[3], &nodes[5])==&nodes[1]);
}
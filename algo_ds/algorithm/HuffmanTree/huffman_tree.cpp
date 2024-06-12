#include <queue>
#include <vector>
#include <functional>
#include <map>
#include <string>
#include "catch.hpp"

// HuffmanTree is for compression codec.
// The abstracted problem is "Weighted Path Length of Tree，WPL"

class HuffmanTree {
private:
    struct TreeNode {
        int weight;
        std::string str;
        TreeNode* left;
        TreeNode* right;

        TreeNode(): weight(0), str(), left(nullptr), right(nullptr){}

        bool operator()(const TreeNode& lf, const TreeNode& rh) const {
            return lf.weight < rh.weight;
        }
    };

    struct NodeGreater{
        bool operator()(const TreeNode* lf, const TreeNode* rh) const {
            return std::greater<TreeNode>(*lf, *rh)();
        }
    };

    // std::function<[](const TreeNode* lf, const TreeNode* rh){return std::greater<TreeNode>(*lf, *rh)();}>

    typedef std::priority_queue<TreeNode*, std::vector<TreeNode*>, NodeGreater> MINPQ;    
    
    static const int MAXNODE=100;
    int nodeIdx=-1;
    TreeNode nodes[MAXNODE];
    TreeNode* tree=nullptr;
    MINPQ pq;
    int minWPL=0;
    std::map<std::string, std::string> codecTable;

private:
    TreeNode* buildTree(const std::map<std::string, int>& table) {
        for (const auto& pair : table) {
            nodes[++nodeIdx].weight=pair.second;
            nodes[nodeIdx].str=pair.first;
            pq.push(&nodes[nodeIdx]);
        }

        int cn=table.size();
        while(--cn) {
            TreeNode* lf=pq.top();
            pq.pop();
            TreeNode* rh=pq.top();
            pq.pop();
            pq.push(mergeTree(lf, rh));
        }

        return pq.top();
    }

    TreeNode* mergeTree(TreeNode* lf, TreeNode* rh) {
        nodes[++nodeIdx].weight=lf->weight+rh->weight;
        nodes[nodeIdx].left=lf;
        nodes[nodeIdx].right=rh;
        return &nodes[nodeIdx];
    }

    void getWPL(const TreeNode* root) {
        if(!root) return;

        // dfs
        minWPL=dfsTree(root, 0);
    }

    int dfsTree(const TreeNode* root, int depth) {
        if(!root) return 0;
        // leave node
        if(!root->left && !root->right) return root->weight*depth;

        return dfsTree(root->left, depth+1)+dfsTree(root->right, depth+1);
    }

    void getCodecTable(const TreeNode* root) {
        std::string codec;
        dfsCodec(root, codec);
    }

    void dfsCodec(const TreeNode* root, std::string& codec) {
        if(!root) return;
        // leave node
        if(!root->left && !root->right) {
            codecTable[root->str]=codec;
            codec.pop_back();
            return;
        }

        dfsCodec(root->left, codec.push_back('0'));
        dfsCodec(root->right, codec.push_back('1'));

        // revert back
        codec.pop_back();
    }

public:
    HuffmanTree(const std::map<std::string, int>& table) {
        tree=buildTree(table);
        getWPL(tree);
        getCodecTable(tree);
    }

    int getMinWPL() const {
        return minWPL;
    }

    std::map<std::string, std::string> getCodecTable() const {
        return codecTable;
    }
};

// Quite impressive !!!
// the minWPL is the sum of all non-leave nodes, you can imagine that the $depth*leave node's weight=$ splits to every non-leave nodes
int getMinWPL(int arr[], int n) {
  std::priority_queue<int, std::vector<int>, std::greater<int>> huffman;
  for (int i = 0; i < n; i++) huffman.push(arr[i]);

  int res = 0;
  for (int i = 0; i < n - 1; i++) {
    int x = huffman.top();
    huffman.pop();
    int y = huffman.top();
    huffman.pop();
    int temp = x + y;
    res += temp;
    huffman.push(temp);
  }
  return res;
}

TEST_CASE("Test Huffman Tree", "") {
    std::map<std::string, int> table{{"A", 35}, {"B", 25}, {"C", 15}, {"D", 15}, {"E", 10}};
    HuffmanTree hfTree(table);

    REQUIRE(hfTree.getMinWPL()==225);
    REQUIRE(hfTree.getCodecTable()==std::map<std::string, int>{{"A", "11"}, {"B", "00"}, {"C", "01"}, {"D", "101"}, {"E", "100"}});
}
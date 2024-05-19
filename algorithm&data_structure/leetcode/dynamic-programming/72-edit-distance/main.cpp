/*
https://leetcode.cn/problems/edit-distance/description/
Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

You have the following three operations permitted on a word:

Insert a character
Delete a character
Replace a character
 

Example 1:

Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')
Example 2:

Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation: 
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')
 

Constraints:

0 <= word1.length, word2.length <= 500
word1 and word2 consist of lowercase English letters.
*/

/*
state: dp[i][j]
state transfer:  
// tricky here: add or delete a char can get a better result
if t1[i]==t2[j], dp[i][j]= max(dp[i-1][j-1], dp[i-1][j]+1, dp[i][j-1]+1)

// replace, insert, delete
// replace: dp[i][j]=1+dp[i-1][j-1]
// insert: dp[i][j]=1+max(dp[i][j-1], dp[i-1][j])
// delete: dp[i][j]=1+max(dp[i][j-1], dp[i-1][j])                
if t1[i]!=t2[j], dp[i][j]=1+max(dp[i-1, j-1], dp[i-1][j], dp[i][j-1])

tricky here:
dp[i][0]==i;  // delete all
dp[0][j]==j;  // delete all
*/

#include <vector>
#include <string>
#include <algorithm>
#include "catch.hpp"

std::string opStr(char op, char o, char n) {
    std::string res;
    if(op=='r') {
        res.append("r: ");
        res.push_back(o);
        res.append("->");
        res.push_back(n);
    }else if(op=='i') {
        res.append("i: ");
        res.push_back(o);
    }else if(op=='d') {
        res.append("d: ");
        res.push_back(o);
    }

    return res;
}

class Solution {
public:    
    int minDistance(std::string word1, std::string word2) {
        int n1=word1.size()+1;
        int n2=word2.size()+1;
        int dp[n1][n2];
        // init
        for(int i=0; i<n1; ++i) dp[i][0]=i;
        for(int j=0; j<n2; ++j) dp[0][j]=j;

        // dp
        for(size_t i=1; i<=word1.size(); ++i) {
            for(size_t j=1; j<=word2.size(); ++j) {
                if(word1[i-1]==word2[j-1]) dp[i][j]=std::min(dp[i-1][j-1], std::min(dp[i-1][j]+1, dp[i][j-1]+1));
                else dp[i][j]=1+std::min(dp[i-1][j-1], std::min(dp[i-1][j], dp[i][j-1]));
            }
        }

        return dp[word1.size()][word2.size()];
    }

    std::vector<std::string> minDistance2(std::string word1, std::string word2) {
        int n1=word1.size();
        int n2=word2.size();
        int dp[n1+1][n2+1];
        
        // init
        for(int i=0; i<=n1; ++i) dp[i][0]=i;
        for(int j=0; j<=n2; ++j) dp[0][j]=j;

        // dp
        for(size_t i=1; i<=n1; ++i) {
            for(size_t j=1; j<=n2; ++j) {
                if(word1[i-1]==word2[j-1]) {
                    dp[i][j]=std::min(dp[i-1][j-1], std::min(dp[i-1][j]+1, dp[i][j-1]+1));
                }
                else {
                    dp[i][j]=1+std::min(dp[i-1][j-1], std::min(dp[i-1][j], dp[i][j-1]));
                }
            }
        }

        // operation, original, new
        // r, h, e
        // i, h
        // d, e
        std::vector<std::string> res;
        // backtracing the dp to get the operations
        int i=n1, j=n2;
        while(i>=1 && j>=1) {
            bool eq=(word1[i-1]==word2[j-1]);
            int ni, nj;

            int min=dp[i-1][j];
            std::string op=opStr('d', word1[i-1], '\0');
            ni=i-1;
            nj=j;
            if(dp[i][j-1]<dp[i-1][j]) {
                min=dp[i][j-1];
                op=opStr('i', word2[j-1], '\0');
                ni=i;
                nj=j-1;
            }

            if(eq) {
                ++min;
            }

            if(min<dp[i-1][j-1]) {
                res.push_back(op);
                i=ni;
                j=nj;
            }else {
                if(!eq) {
                    res.push_back(opStr('r', word1[i-1], word2[j-1]));
                }
                --i;
                --j;
            }
        }

        std::reverse(res.begin(), res.end());
        return res;
    }
};


TEST_CASE("Test minDistance", "") {
    SECTION("") {
        Solution sl;
        REQUIRE(sl.minDistance("horse", "ros")==3);
        REQUIRE(sl.minDistance2("horse", "ros")==std::vector<std::string>{"r: h->r", "d: r", "d: e"});
    }
}
/*
*  Longest Common Sequence Problem:
Here are some applications that are more specifically related to the LCS problem:
1. Version Control Systems: LCS is used to determine the differences between versions of a document or code, 
as it can handle non-contiguous changes.
2. Sequence Alignment: In computational biology, LCS is used for global sequence alignment, where the goal is to align two biological sequences in their entirety.
3. Text Editors: Some text editors use LCS algorithms to compare different versions of a document and highlight the changes.
4. Optical Character Recognition (OCR): LCS can be used to determine the best match between the recognized text and the original text.
5. Music and Video Synchronization: LCS can be used to synchronize music or video tracks that may have been edited or altered.
*/

/*
https://leetcode.cn/problems/longest-common-subsequence/description/
Given two strings text1 and text2, return the length of their longest common subsequence. If there is no common subsequence, return 0.
A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
For example, "ace" is a subsequence of "abcde".
A common subsequence of two strings is a subsequence that is common to both strings.
Example 1:
Input: text1 = "abcde", text2 = "ace" 
Output: 3  
Explanation: The longest common subsequence is "ace" and its length is 3.
*/

/*
*  Why LCS problem can model as a dynamic programming problem?
*  Comes from observation.
* 
*  state:  dp[i][j] is lcs for the prefix i substring of string A and the prefix j substring of string B
*  state transfer: 
*  1. if A[i]==B[j], dp[i][j] = dp[i-1][j-1] + 1
*  2. if A[i]!=B[j], dp[i][j] = max(dp[i-1][j], dp[i][j-1])
*  
*  initial state: dp[0][0]=(A[0]==B[0])
*
*  Time Complexity: O(M*N), there exists algorithm O(M*N/w) !
*  Space Complexity: O(M*N)
*/

#include <string>
#include <algorithm>
#include <cstring>
#include "catch.hpp"

class Solution {
    static const int Max=1001;
    int dp[Max][Max];
public:
    int longestCommonSubsequence(const std::string& A, const std::string& B) {
            dp[0][0]=(A[0]==B[0]);
            for(size_t i=1; i<A.size(); ++i)
                dp[i][0]=std::max(int(B[0]==A[i]), dp[i-1][0]);
            for(size_t j=1; j<B.size(); ++j)
                dp[0][j]=std::max(int(A[0]==B[j]), dp[0][j-1]);

            for(size_t i=1; i<A.size(); ++i) {
                for(size_t j=1; j<B.size(); ++j) {
                    if(A[i]==B[j]) dp[i][j]=dp[i-1][j-1]+1;
                    else dp[i][j]=std::max(dp[i-1][j], dp[i][j-1]);
                }
            }

            return dp[A.size()-1][B.size()-1];
    }
};

// In order to deal with border, we define the dp[i][j] as the lcs for i prefix length of string A and j prefix length of string B
// so we can get the border dp[i][0] and dp[0][j] is all 0.
class Solution2 {
    static const int Max=1001;
    int dp[Max][Max];
public:
    int longestCommonSubsequence(const std::string& A, const std::string& B) {
            memset(dp, 0, sizeof(dp));
            for(size_t i=1; i<=A.size(); ++i) {
                for(size_t j=1; j<=B.size(); ++j) {
                    if(A[i-1]==B[j-1]) dp[i][j]=dp[i-1][j-1]+1;
                    else dp[i][j]=std::max(dp[i-1][j], dp[i][j-1]);
                }
            }

            return dp[A.size()][B.size()];
    }

    std::string longestCommonSubsequence2(const std::string& A, const std::string& B) {
            memset(dp, 0, sizeof(dp));
            for(size_t i=1; i<=A.size(); ++i) {
                for(size_t j=1; j<=B.size(); ++j) {
                    if(A[i-1]==B[j-1]) dp[i][j]=dp[i-1][j-1]+1;
                    else dp[i][j]=std::max(dp[i-1][j], dp[i][j-1]);
                }
            }

            std::string res;
            // backtracking the dp to find every A[i]==B[j] where the lcs increase
            size_t i=A.size(), j=B.size();
            while(i>=1 && j>=1) {
                if(A[i-1]==B[j-1]) {
                    res.push_back(A[i-1]);
                    --i;
                    --j;
                }else if(dp[i-1][j]>dp[i][j-1]) {
                    --i;
                }else {
                    --j;
                }
            }

            std::reverse(res.begin(), res.end());
            return res;
    }
};

TEST_CASE("Test longestCommonSubsequence", "[]")
{
    Solution2 sl2;
    REQUIRE(sl2.longestCommonSubsequence("abcde", "acde")==4);
    REQUIRE(sl2.longestCommonSubsequence2("abcde", "acde")=="acde");
    REQUIRE(sl2.longestCommonSubsequence2("abcdef", "acde")=="acde");
}

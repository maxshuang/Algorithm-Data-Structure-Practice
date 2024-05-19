/*
*  Longest Common Substring Problem:
1. Data Deduplication: Finding common substrings can help in identifying duplicate data for deduplication purposes.
2. String Search Algorithms: Longest common substrings are used in algorithms like the Rabin-Karp for string searching.
3. Genetic Algorithms: In genetic algorithms, common substrings can represent genetic material that is passed from one generation to the next.
4. Pattern Recognition: In pattern recognition, finding common substrings can help identify recurring patterns in data.
5. Web Search: Some search algorithms use longest common substrings to find similar web pages.
*/

/*
state: dp[i][j], lcs for string t1 which ends with t1[i-1] and string t2 which ends with t2[j-1]
state transfer: if t1[i-1]==t2[j-1], dp[i][j]=dp[i-1][j-1]+1
                if t1[i-1]!=t2[j-1], dp[i][j]=max(dp[i-1][j], dp[i][j-1])
initial state: dp[i][0]=0, dp[0][j]=0

Time Complexity: O(MN)
Space Complexity: O(MN)
*/

#include <string>
#include <algorithm>
#include <cstring>
#include "catch.hpp"

const int MAX=10001;
int dp[MAX][MAX];

// Space Complexity: O(M*N)
int LongestCommonSubstring(const std::string& t1, const std::string& t2) {
    int ans=0;
    for(size_t i=1; i<=t1.size(); ++i) {
        for(size_t j=1; j<=t2.size(); ++j) {
            if(t1[i-1]==t2[j-1]) dp[i][j]=dp[i-1][j-1]+1;
            else dp[i][j]=std::max(dp[i-1][j], dp[i][j-1]);
            if(dp[i][j]>ans) ans=dp[i][j];
        }
    }

    return ans;   
}

std::string LongestCommonSubstring2(const std::string& t1, const std::string& t2) {
    int ans=0;
    int lcs_i=0, lcs_j=0;
    for(size_t i=1; i<=t1.size(); ++i) {
        for(size_t j=1; j<=t2.size(); ++j) {
            if(t1[i-1]==t2[j-1]) dp[i][j]=dp[i-1][j-1]+1;
            else dp[i][j]=std::max(dp[i-1][j], dp[i][j-1]);
            if(dp[i][j]>ans) {
                ans=dp[i][j];
                lcs_i=i;
                lcs_j=j;
            }
        }
    }

    std::string res;
    while(lcs_i>=1 && lcs_j>=1 && t1[lcs_i-1]==t2[lcs_j-1]) {
        res.push_back(t1[lcs_i-1]);
        --lcs_i;
        --lcs_j;
    }

    std::reverse(res.begin(), res.end());
    return res;   
}

// Space Complexity: O(N)
int LongestCommonSubstring_compress(const std::string& t1, const std::string& t2) {
    int ans=0;
    // space compression:
    int dp[MAX];
    memset(dp, 0, sizeof(dp));
    for(size_t i=1; i<=t1.size(); ++i) {
        // pre is the dp[i-1][j-1]
        int pre=dp[0];
        
        for(size_t j=1; j<=t2.size(); ++j) {
            // This is the dp[i-1][j]
            int tmp=dp[j];
            
            // we need dp[i-1][j-1] here, but it's covered by dp[i][j-1]
            // so we need to save dp[i-1][j-1] before getting dp[i][j-1] 
            if(t1[i-1]==t2[j-1]) dp[j]=pre+1;
            
            // dp[j-1] is the last inner j => dp[i][j-1]
            // dp[j] is the last inner i => dp[i-1][j]
            else dp[j]=std::max(dp[j], dp[j-1]);

            // pre becomes the dp[i-1][j-1] for next j term            
            pre=tmp;

            if(dp[j]>ans) ans=dp[j];
        }
    }

    return ans;   
}

TEST_CASE("Test LongestCommonSubstring", "") {
    SECTION("LongestCommonSubstring1") {
        REQUIRE(LongestCommonSubstring("acdyyyyytt", "pyyyyq")==4);
        REQUIRE(LongestCommonSubstring("acdyyyyytt", "pyyyy")==4);
        REQUIRE(LongestCommonSubstring("yyyyytt", "pyyyyq")==4);
    }

    SECTION("LongestCommonSubstring2") {
        REQUIRE(LongestCommonSubstring_compress("acdyyyyytt", "pyyyyq")==4);
        REQUIRE(LongestCommonSubstring_compress("acdyyyyytt", "pyyyy")==4);
        REQUIRE(LongestCommonSubstring_compress("yyyyytt", "pyyyyq")==4);
    }

    SECTION("LongestCommonSubstring3") {
        REQUIRE(LongestCommonSubstring2("acdyyyyytt", "pyyyyq")=="yyyy");
        REQUIRE(LongestCommonSubstring2("acdyyyyytt", "acdq")=="acd");
        REQUIRE(LongestCommonSubstring2("yyyyytt", "pyytq")=="yyt");
    }
}
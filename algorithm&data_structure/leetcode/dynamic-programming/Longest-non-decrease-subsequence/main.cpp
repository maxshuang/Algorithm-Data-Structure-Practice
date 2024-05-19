/**
 * 给定一个长度为 n 的序列 A（n <= 5000），求出一个最长的 A 的子序列，满足该子序列的后一个元素不小于前一个元素。
*/

/*
*  Solution1:
*  set dp[i] is the longest non-decrease subsequnce which end with A[i]
*  initial state: dp[0]=1;
*  state transfer: dp[i]=max(A[j]<=A[i])(dp[j]+1)
*  Time complexity: O(N^2)
*
*  There exists O(NlogN) algorithm, https://www.cnblogs.com/itlqs/p/5743114.html
*/

#include <string>
#include <vector>
#include <algorithm>

int LongestNondecreaseSubsequence(const std::string& A) {
    std::vector<int> dp(A.size(), 0);
    int ans=0;
    dp[0]=1;
    for(size_t i=1; i<A.size(); ++i) {
        for(size_t j=1; j<i; ++j) {
            if(A[j]<=A[i]) {
                dp[i]=std::max(dp[i], dp[j]+1);
                ans=std::max(ans, dp[i]);
            }
        }
    }

    return ans;
}
/*
 * You are given an array prices where prices[i] is the price of a given stock on the ith day, and an integer fee representing a transaction fee.
Find the maximum profit you can achieve. You may complete as many transactions as you like, but you need to pay the transaction fee for each transaction.
Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

Constraints:
1 <= prices.length <= 5 * 104
1 <= prices[i] < 5 * 104
0 <= fee < 5 * 104
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    int maxProfit(std::vector<int>& prices, int fee) {
        // dp[i][0]=max(dp[i-1][0], dp[i-1][1]+prices[i]-fee)
        // dp[i][1]=max(dp[i-1][1], dp[i-1][0]-prices[i])
        int dp_i1_1=-prices[0];
        int dp_i1_0=0;
        for(int i=1; i<prices.size(); ++i) {
            int tmp=std::max(dp_i1_0, dp_i1_1+prices[i]-fee);
            dp_i1_1=std::max(dp_i1_1, dp_i1_0-prices[i]);
            dp_i1_0=tmp;
        }

        return dp_i1_0;
    }
};

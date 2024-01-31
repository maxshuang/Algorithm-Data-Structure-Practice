/*
 * You are given an integer array prices where prices[i] is the price of a given stock on the ith day.
On each day, you may decide to buy and/or sell the stock. You can only hold at most one share of the stock at any time. However, you can buy it then immediately sell it on the same day.
Find and return the maximum profit you can achieve.

Constraints:
1 <= prices.length <= 3 * 104
0 <= prices[i] <= 104
 */

class Solution {
public:
    // greedy algorithm: make sure we has every positive difference
    int maxProfit(vector<int>& prices) {
        int maxProfit=0;
        for(int i=1; i<prices.size(); ++i){
            if(prices[i]>prices[i-1]) {
                maxProfit+=(prices[i]-prices[i-1]);
            }
        }

        return maxProfit;
    }

    // dynamic programming
    int maxProfit2(vector<int>& prices) {
        // state: day, hold or not
        // selection: buy/sell/do nothing
        // state transfer function:
        // dp[i][hold]=max(dp[i-1][hold], dp[i-1][unhold]-p[i]); // do nothing or buy
        // dp[i][unhold]=max(dp[i-1][hold]+p[i], dp[i-1][unhold])  // sell or do nothing
        // base case:
        // dp[0][0]=0; dp[0][1]=-p[0];
        int dp_i1_0=0, dp_i1_1=-prices[0];

        for(int i=1; i<prices.size(); ++i) {
            int dp_i_0=max(dp_i1_1+prices[i], dp_i1_0);
            int dp_i_1=max(dp_i1_1, dp_i1_0-prices[i]);
            dp_i1_0 = dp_i_0;
            dp_i1_1 = dp_i_1;
        }

        return dp_i1_0;
    }
};

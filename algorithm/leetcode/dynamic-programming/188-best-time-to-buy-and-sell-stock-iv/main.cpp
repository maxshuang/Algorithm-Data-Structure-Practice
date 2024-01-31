/*
 * You are given an integer array prices where prices[i] is the price of a given stock on the ith day, and an integer k.
Find the maximum profit you can achieve. You may complete at most k transactions: i.e. you may buy at most k times and sell at most k times.
Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

Constraints:
1 <= k <= 100
1 <= prices.length <= 1000
0 <= prices[i] <= 1000
*/

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        vector<int> hold(k+1, -prices[0]);
        vector<int> cash(k+1, 0);
        // hold->sell->hold->sell->...
        for(int i = 1;i < prices.size();i++){
            for(int j = 1;j <= k;j++){
                hold[j] = max(hold[j], cash[j-1]-prices[i]);
                cash[j] = max(cash[j], hold[j]+prices[i]);
            }
        }
        return sell[k];
    }

    int maxProfit2(int k, vector<int>& prices) {
        // state: day, hold or not, maximum nums of transation(buy+sell)
        // selection: buy/sell/do nothing
        // state transfer function:
        // dp[i][k][1]=max(dp[i-1][k][1], dp[i-1][k-1][0]-p[i]); // do nothing or buy
        // dp[i][k][0]=max(dp[i-1][k][1]+p[i], dp[i-1][k][0])  // sell or do nothing
        // base case:
        // dp[x][0][0]=0;
        // dp[x][0][1]=INT_MIN;

        vector<vector<vector<int>>> dp(prices.size(), vector<vector<int>>(k+1, vector<int>(2, 0)));
        for(int i=0; i<prices.size(); ++i){
            dp[i][0][1]=INT_MIN;
        }
        for(int j=1; j<k+1; ++j){
            dp[0][j][1]=-prices[0];
        }

        for(int i=1; i<prices.size(); ++i) {
            for(int j=1; j<k+1; ++j) {
                dp[i][j][1]=max(dp[i-1][j][1], dp[i-1][j-1][0]-prices[i]);
                dp[i][j][0]=max(dp[i-1][j][1]+prices[i], dp[i-1][j][0]);
            }
        }

        return dp[prices.size()-1][k][0];
    }
};

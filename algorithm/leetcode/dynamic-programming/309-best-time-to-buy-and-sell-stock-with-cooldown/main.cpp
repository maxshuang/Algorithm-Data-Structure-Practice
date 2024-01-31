/*
 * You are given an array prices where prices[i] is the price of a given stock on the ith day.
Find the maximum profit you can achieve. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times) with the following restrictions:
After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).
Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

Constraints:
1 <= prices.length <= 5000
0 <= prices[i] <= 1000
 */

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size()<=1) return 0;
        if(prices.size()==2) return prices[0]>=prices[1]?0: prices[1]-prices[0];
        //dp[i][0]=max(dp[i-1][0], dp[i-1][1]+prices[i])
        //dp[i][1]=max(dp[i-1][1], dp[i-2][0]-prices[i])
        vector<vector<int>> dp(prices.size(), vector<int>(2, 0));
        // base case
        dp[0][1]=-prices[0];

        for(int i=1; i<prices.size(); ++i) {
            if(i<2){
                dp[i][1]=max(dp[i-1][1], -prices[i]);
            }else {
                dp[i][1]=max(dp[i-1][1], dp[i-2][0]-prices[i]);
            }
            dp[i][0]=max(dp[i-1][0], dp[i-1][1]+prices[i]);
        }

        return dp[prices.size()-1][0];
    }

    // maxProfit2 is easier to compress the state space
    int maxProfit2(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> f(n, vector<int>(3));
        f[0][0] = -prices[0];
        for (int i = 1; i < n; ++i) {
            f[i][0] = max(f[i - 1][0], f[i - 1][2] - prices[i]);
            f[i][1] = f[i - 1][0] + prices[i];
            f[i][2] = max(f[i - 1][1], f[i - 1][2]);
        }
        return max(f[n - 1][1], f[n - 1][2]);
    }

    int maxProfit3(vector<int>& prices) {
        int n = prices.size();
        int f0 = -prices[0];
        int f1 = 0;
        int f2 = 0;
        for (int i = 1; i < n; ++i) {
            int newf0 = max(f0, f2 - prices[i]);
            int newf1 = f0 + prices[i];
            int newf2 = max(f1, f2);
            f0 = newf0;
            f1 = newf1;
            f2 = newf2;
        }

        return max(f1, f2);
    }
};

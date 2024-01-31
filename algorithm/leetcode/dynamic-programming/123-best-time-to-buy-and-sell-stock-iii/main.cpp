/*
 * You are given an array prices where prices[i] is the price of a given stock on the ith day.
Find the maximum profit you can achieve. You may complete at most two transactions.
Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

Constraints:
1 <= prices.length <= 105
0 <= prices[i] <= 105
 */

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<int> hold(3, -prices[0]);
        vector<int> cash(3, 0);
        // hold->sell->hold->sell->...
        for(int i = 1;i < prices.size();i++){
            for(int j = 1;j <= 2;j++){
                hold[j] = max(hold[j], cash[j-1]-prices[i]);
                cash[j] = max(cash[j], hold[j]+prices[i]);
            }
        }
        return cash[2];
    }
    
    int maxProfit2(vector<int>& prices) {
        if(prices.size()<=1) return 0;
        // state: day, hold or not, maximum nums of transation(buy+sell)
        // selection: buy/sell/do nothing
        // state transfer function:
        // dp[i][k][1]=max(dp[i-1][k][1], dp[i-1][k-1][0]-p[i]); // do nothing or buy
        // dp[i][k][0]=max(dp[i-1][k][1]+p[i], dp[i-1][k][0])  // sell or do nothing
        // base case:
        // dp[-1][x][0]=0;
        // dp[-1][x][1]=INT_MIN;
        // dp[x][0][0]=0;
        // dp[x][0][1]=INT_MIN;

        // k=0,1,2
        // hold=0,1
        // ===>
        // dp[i][2][1]=max(dp[i-1][2][1], dp[i-1][1][0]-prices[i]);
        // dp[i][2][0]=max(dp[i-1][2][1]+prices[i], dp[i-1][2][0]);
        // dp[i][1][1]=max(dp[i-1][1][1], dp[i][0][0]-prices[i]);
        // dp[i][1][0]=max(dp[i-1][1][1]+prices[i], dp[i-1][1][0]);
        // dp[i][0][1]=INT_MIN;
        // dp[i][0][0]=0;

        // Simplify:
        // s21=max(s21, s10-prices[i]);
        // s20=max(s21+prices[i], s20);
        // s11=max(s11, s00-prices[i]);
        // s10=max(s11+prices[i], s10);

        // as for 'hold' for the day0 is impossible
        // so 's21' and 's11' is initialized to INT_MIN
        int s21=INT_MIN, s20=0;
        int s10=0, s11=INT_MIN;
        for(int i=0; i<prices.size(); ++i) {
            s21=max(s21, s10-prices[i]);
            s20=max(s21+prices[i], s20);
            s11=max(s11, -prices[i]);
            s10=max(s11+prices[i], s10);
        }

        return s20;
    }

    // Actually: maxProfit3 and maxProfit2 have the same underlying meaning 
    int maxProfit3(vector<int>& prices) {
        // four states: buy1, sell1, buy2, sell2
        int n = prices.size();
        // base case:
        // for the 0th day, buy1/buy2 means offer first price
        int buy1 = -prices[0], sell1 = 0;
        int buy2 = -prices[0], sell2 = 0;

        for (int i = 1; i < n; ++i) {
            // state transfer function:
            // buy1[i]=max(buy1[i-1], -prices[i])
            // sell1[i]=max(buy1[i-1]+prices[i], sell1[i-1])
            // buy2[i]=max(buy2[i-1], sell1[i-1]-prices[i])
            // sell2[i]=max(sell2[i-1], buy2[i-1]+prices[i])
            buy1 = max(buy1, -prices[i]);
            sell1 = max(sell1, buy1 + prices[i]);
            buy2 = max(buy2, sell1 - prices[i]);
            sell2 = max(sell2, buy2 + prices[i]);
        }
        return sell2;
    }
};

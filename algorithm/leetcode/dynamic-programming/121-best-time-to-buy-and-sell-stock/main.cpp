/*
 * You are given an array prices where prices[i] is the price of a given stock on the i_th day.
You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.
Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

Constraints:
1 <= prices.length <= 105
0 <= prices[i] <= 104
*/

/*
Solution:


*/

#include <vector>

class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
       // Greedy algorithm: find the max difference between every element and the minimum one
       // find the mininum and calculate the profit
       int minPrice=100000;
       int maxPro=0;
       for(int price: prices){
           maxPro=std::max(price-minPrice, maxPro);
           minPrice=std::min(minPrice, price);
       }

       return maxPro;
    }
   
    // dynamic programming 
    int maxProfit2(std::vector<int>& prices) {
        // state: day, hold or not, maximum nums of trade(buy+sell)
        // selection: buy/sell/do nothing
        // state transfer function:
        // dp[i][k][hold]=max(dp[i-1][k][hold], dp[i-1][k-1][unhold]-p[i]); // do nothing or buy
        // dp[i][k][unhold]=max(dp[i-1][k][hold]+p[i], dp[i-1][k][unhold])  // sell or do nothing
        // base case:
        // dp[-1][x][0]=0;
        // dp[-1][x][1]=INT_MIN;
        // dp[x][0][0]=0;
        // dp[x][0][1]=INT_MIN;
        
        // When k=1:
        // dp[i][1][1]=max(dp[i-1][1][1], dp[i-1][0][0]-p[i])=max(dp[i-1][1][1], -p[i]);
        // dp[i][1][0]=max(dp[i-1][1][1]+p[i], dp[i-1][1][0])
        // ==============>
        // dp[i][1]=max(dp[i-1][1], -p[i]);
        // dp[i][0]=max(dp[i-1][1]+p[i], dp[i-1][0])
        
        int dp_i1_0=0, dp_i1_1=-prices[0];

        for(int i=1; i<prices.size(); ++i) {
            int dp_i_0=std::max(dp_i1_1+prices[i], dp_i1_0);
            int dp_i_1=std::max(dp_i1_1, -prices[i]);
            dp_i1_0 = dp_i_0;
            dp_i1_1 = dp_i_1;
        }

        return dp_i1_0;
    }
};

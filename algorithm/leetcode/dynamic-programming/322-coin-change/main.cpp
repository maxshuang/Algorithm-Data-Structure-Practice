/*
 You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.
You may assume that you have an infinite number of each kind of coin.

Constraints:
1 <= coins.length <= 12
1 <= coins[i] <= 231 - 1
0 <= amount <= 104
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    int coinChange(std::vector<int>& coins, int amount) {
        // base case
        int *dp=new int[amount+1];
        for(int i=0; i<amount+1; ++i){
            dp[i]=10001;
        }
        dp[0]=0;

        // status transfer function
        // dp[n] = min{dp[n-coins[i]]+1|0<=i<size, dp[n]}
        for(int n=0; n<amount+1; ++n){
            // selection
            for(int coin: coins){
                if(n<coin){
                    continue;
                }
                dp[n]=std::min(dp[n-coin]+1, dp[n]);
            }
        }

        return dp[amount]!=10001?dp[amount]:-1;
    }
};

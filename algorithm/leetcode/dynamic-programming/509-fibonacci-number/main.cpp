/*
 The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence, such that each number is the sum of the two preceding ones, starting from 0 and 1. That is,

Constraints:
0 <= n <= 30
 */

class Solution {
public:
    int fib(int n) {
        if(n==0) return 0;
        if(n==1) return 1;

        int dp_i_1=1;
        int dp_i_2=0;

        // status transfer function
        // f(n)=f(n-1)+f(n-2)
        int dp=0;
        for(int i=2; i<n+1; ++i) {
            dp=dp_i_1+dp_i_2;
            dp_i_2=dp_i_1;
            dp_i_1=dp;
        }

        return dp;
    }
};

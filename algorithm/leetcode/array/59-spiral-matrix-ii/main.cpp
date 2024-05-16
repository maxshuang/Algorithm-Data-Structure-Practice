/*
 * 
Given a positive integer n, generate an n x n matrix filled with elements from 1 to n^2 in spiral order.
Constraints: 1 <= n <= 20
 */

/*
Same solution as 54-spiral-matrix
*/

#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> generateMatrix(int n) {
        std::vector<std::vector<int>> res(n, std::vector<int>(n, 0));
        int left=0, right=n-1;
        int upper=0, lower=n-1;
        int idx=1;
        while(left<=right && upper <= lower){
            // left to right, update upper
            for(int i=left; i<=right; ++i) {
                res[upper][i]=(idx++);
            }
            ++upper;
            // upper to lower, update right
            for(int i=upper; i<=lower; ++i) {
                res[i][right]=(idx++);
            }
            --right;
            // right to left, update lower
            for(int i=right; upper <= lower && i>=left; --i) {
                res[lower][i]=(idx++);
            }
            --lower;
            // lower to upper, update left {
            for(int i=lower; left<=right && i>=upper; --i) {
                res[i][left]=(idx++);
            }
            ++left;
        }

        return res;
    }
};

/*
 *
Given an m x n matrix, return all elements of the matrix in spiral order.
 
Constraints:
m == matrix.length
n == matrix[i].length
1 <= m, n <= 10
-100 <= matrix[i][j] <= 100
*/

/*
Solution:
This is the problem of enumeration, you need to carefully maintain the border at the sequence of
up/right/down/left untill up==down && left==right
*/

#include <vector>

class Solution {
public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
        std::vector<int> res;
        int m=matrix.size();
        int n=matrix[0].size();
        int left=0, right=n-1;
        int upper=0, lower=m-1;

        while(left<=right && upper <= lower){
            // left to right, update upper
            for(int i=left; i<=right; ++i) {
                res.push_back(matrix[upper][i]);
            }
            ++upper;
            // upper to lower, update right
            for(int i=upper; i<=lower; ++i) {
                res.push_back(matrix[i][right]);
            }
            --right;
            // right to left, update lower
            for(int i=right; upper <= lower && i>=left; --i) {
                res.push_back(matrix[lower][i]);
            }
            --lower;
            // lower to upper, update left {
            for(int i=lower; left<=right && i>=upper; --i) {
                res.push_back(matrix[i][left]);
            }
            ++left;
        }

        return res;
    }
};

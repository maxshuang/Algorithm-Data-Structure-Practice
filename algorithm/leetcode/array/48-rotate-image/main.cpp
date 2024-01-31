/*
 * You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).
You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

Constraints:
n == matrix.length == matrix[i].length
1 <= n <= 20
-1000 <= matrix[i][j] <= 1000
 */

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        // rotate 90 degree means col will become row
        int n=matrix.size();
        // 1. we can flip around the diagonal： (i,j)=>(j,i)
        for(int i=0; i<n; ++i) {
            for(int j=i+1; j<n; ++j) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        // 2. then flip around the vetical line
        for(int i=0; i<n; ++i){
            for(int j=0, k=n-1; j<k; ++j, --k){
                swap(matrix[i][j], matrix[i][k]);
            }
        }

        return;
    }
};

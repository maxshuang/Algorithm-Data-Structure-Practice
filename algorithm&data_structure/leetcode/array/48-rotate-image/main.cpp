/*
 * https://leetcode.cn/problems/rotate-image/description/ 
You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).
You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. 
DO NOT allocate another 2D matrix and do the rotation.

Constraints:
n == matrix.length == matrix[i].length
1 <= n <= 20
-1000 <= matrix[i][j] <= 1000
 */

/*
This is the problem of matrix tranformation, we can observe the transformation to find the pattern:

1. rotate 90 degree clock-wise
1 2   =>  4 1
4 5   =>  5 2

original column index becomes new row index, original (N-1-row) index becomes new column index.
<i, j> => <j, N-1-i>

2. rotate 180 degree clockwise
1 2   =>  5 4
4 5   =>  2 1
<i, j> => <j, i>

3. rotate 90 degree anticlockwise
1 2   =>  2 5
4 5   =>  1 4
<i, j> => <N-1-j, i>

4. rotate 180 degree anticlockwise
1 2   =>  5 4
4 5   =>  2 1
<i, j> => <j, i>

in-place rotate can be quite tricky, need change to easier operations:
<i, j> => <j, N-1-i>  
==
(flip around the diagonal)
<i, j> => <j, i>
+
(flip around the middle vertical line)
<j, i> => <j, N-1-i>
*/

#include <vector>
#include <algorithm>

class Solution {
public:
    void rotate(std::vector<std::vector<int>>& matrix) {
        // rotate 90 degree means col will become row
        int n=matrix.size();
        // 1. we can flip around the diagonal(/daɪˈæɡ.ən.əl/)： (i,j)=>(j,i)
        // only need to exchange half of the element
        for(int i=0; i<n; ++i) {
            for(int j=i+1; j<n; ++j) {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }
        // 2. then flip around the vetical line
        for(int i=0; i<n; ++i){
            for(int j=0, k=n-1; j<k; ++j, --k){
                std::swap(matrix[i][j], matrix[i][k]);
            }
        }

        return;
    }
};

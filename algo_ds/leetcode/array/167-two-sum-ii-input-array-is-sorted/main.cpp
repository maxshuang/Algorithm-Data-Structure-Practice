/*
 *
Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order, 
find two numbers such that they add up to a specific target number. 
Let these two numbers be numbers[index1] and numbers[index2] where 1 <= index1 < index2 <= numbers.length.
Return the indices of the two numbers, index1 and index2, added by one as an integer array [index1, index2] of length 2.
The tests are generated such that there is exactly one solution. You may not use the same element twice.
Your solution must use only constant extra space.

Constraints:
2 <= numbers.length <= 3 * 104
-1000 <= numbers[i] <= 1000
numbers is sorted in non-decreasing order.
-1000 <= target <= 1000
The tests are generated such that there is exactly one solution.
*/
/*
Solution:
For a sorted array, we can use double pointer to calacute the sum and easily learn that we need to move forward the left pointer
or move backward the right pointer

Time Complexity: O(N)
*/

#include <vector>

class Solution {
public:
    // O(N)
    std::vector<int> twoSum(std::vector<int>& numbers, int target) {
        int left=0, right=numbers.size()-1;
        while(left<right) {
            int sum = numbers[left]+numbers[right];
            if(sum==target){
                return {left+1, right+1};
            }else if(sum<target) {
                ++left;
            }else {
                --right;
            }
        }
        return {};
    }
};

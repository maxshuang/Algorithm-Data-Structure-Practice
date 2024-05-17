/*
 * Given an integer array nums of unique elements, return all possible subsets (the power set).
The solution set must not contain duplicate subsets. Return the solution in any order.

Constraints:
1 <= nums.length <= 10
-10 <= nums[i] <= 10
All the numbers of nums are unique.
 */

/*
Solution:
backtrace in multi-way tree, maintain the path when traverse in DFS
Time Complexity: O(N!), N fac'torial
Space Complexity: O(N), for stack
*/

#include <vector>

class Solution {
    std::vector<int> combination;
    std::vector<std::vector<int>> res;
public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
        backtrace(nums, 0);
        return res;
    }

    void backtrace(std::vector<int>& nums, int start) {
        res.push_back(combination);
        for(int i=start; i<nums.size(); ++i) {
            // make selection
            combination.push_back(nums[i]);
            backtrace(nums, i+1);
            // revert seletion
            combination.pop_back();
        }
    }
};

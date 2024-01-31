/*
 * Given an integer array nums of unique elements, return all possible subsets (the power set).
The solution set must not contain duplicate subsets. Return the solution in any order.

Constraints:
1 <= nums.length <= 10
-10 <= nums[i] <= 10
All the numbers of nums are unique.
 */

class Solution {
    vector<int> combination;
    vector<vector<int>> res;
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        backtrace(nums, 0);
        return res;
    }

    void backtrace(vector<int>& nums, int start) {
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

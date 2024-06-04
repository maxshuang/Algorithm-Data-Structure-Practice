/*
 * Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
The solution set must not contain duplicate subsets. Return the solution in any order.
 
Constraints:
1 <= nums.length <= 10
-10 <= nums[i] <= 10
 */

#include <vector>
#include <algorithm>

class Solution {
    std::vector<int> combination;
    std::vector<std::vector<int>> res;
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        backtrace(nums, 0);
        return res;
    }

    void backtrace(std::vector<int>& nums, int start) {
        res.push_back(combination);
        for(int i=start; i<nums.size(); ++i) {
            if(i>start&&nums[i]==nums[i-1]){
                continue;
            }
            // make selection
            combination.push_back(nums[i]);
            backtrace(nums, i+1);
            // revert seletion
            combination.pop_back();
        }
    }
};

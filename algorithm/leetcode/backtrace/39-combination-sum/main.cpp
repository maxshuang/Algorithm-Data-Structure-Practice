/*
 * Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.
The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.
The test cases are generated such that the number of unique combinations that sum up to target is less than 150 combinations for the given input.

Constraints:
1 <= candidates.length <= 30
2 <= candidates[i] <= 40
All elements of candidates are distinct.
1 <= target <= 40
 */

class Solution {
    vector<int> combination;
    int preSum;
    vector<vector<int>> res;
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        res.clear();
        backtrace(candidates, target, 0);
        return res;
    }
    void backtrace(vector<int>& candidates, int target, int start) {
        // end condition
        if(preSum==target){
            res.push_back(combination);
            return;
        }

        int size = candidates.size();
        for(int i=start; i<size; ++i) {
            if(preSum+candidates[i]>target) {
                continue;
            }
            // make selection
            preSum+=candidates[i];
            combination.push_back(candidates[i]);
            backtrace(candidates, target, i);
            // revert seletion
            preSum-=candidates[i];
            combination.pop_back();
        }
    }
};

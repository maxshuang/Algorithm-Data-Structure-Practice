/*
 * Given a collection of candidate numbers (candidates) and a target number (target), 
find all unique combinations in candidates where the candidate numbers sum to target.
Each number in candidates may only be used once in the combination.
Note: The solution set must not contain duplicate combinations.

Constraints:
1 <= candidates.length <= 100
1 <= candidates[i] <= 50
1 <= target <= 30
 */

#include <vector>
#include <algorithm>

class Solution {
    std::vector<int> combination;
    int preSum;
    std::vector<std::vector<int>> res;
public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {
        res.clear();
        std::sort(candidates.begin(), candidates.end());
        backtrace(candidates, target, 0);
        return res;
    }
    void backtrace(std::vector<int>& candidates, int target, int start) {
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
            if(i>start&&candidates[i]==candidates[i-1]){
                continue;
            }
            // make selection
            preSum+=candidates[i];
            combination.push_back(candidates[i]);

            // truncating branches here is more efficient
            if(preSum>target){
                preSum-=candidates[i];
                combination.pop_back();
                return;
            }

            backtrace(candidates, target, i+1);
            
            // revert seletion
            preSum-=candidates[i];
            combination.pop_back();

        }
    }
};

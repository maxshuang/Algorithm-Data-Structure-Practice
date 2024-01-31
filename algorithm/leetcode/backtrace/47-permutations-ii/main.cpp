/*
 * Given a collection of numbers, nums, that might contain duplicates, return all possible unique permutations in any order.

 Constraints:
1 <= nums.length <= 8
-10 <= nums[i] <= 10
 */

class Solution {
    vector<int> combination;
    vector<vector<int>> res;
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<bool> used(nums.size(), false);
        backtrace(nums, used);
        return res;
    }

    void backtrace(vector<int>& nums, vector<bool>& used){
        // end condition
        if(combination.size()==nums.size()) {
            res.push_back(combination);
        }

        int cur=-11;
        for(int i=0; i<nums.size(); ++i){
            if(used[i]==true){
                continue;
            }
            // skip duplicate for the same layer
            if(nums[i]==cur){
                continue;
            }

            // make selection
            combination.push_back(nums[i]);
            used[i]=true;
            cur=nums[i];
            backtrace(nums, used);

            // revert selection
            used[i]=false;
            combination.pop_back();
        }
    }
};

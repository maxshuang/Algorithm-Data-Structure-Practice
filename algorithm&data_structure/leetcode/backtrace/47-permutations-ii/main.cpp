/*
 * Given a collection of numbers, nums, that might contain duplicates, 
 return all possible unique permutations in any order.

 Constraints:
1 <= nums.length <= 8
-10 <= nums[i] <= 10
 */

/*
Solution:
1. using counting-tag
2. sort the original array to remove the duplicated elements in the same layer
*/

#include <vector>
#include <algorithm>

class Solution {
    std::vector<int> combination;
    std::vector<std::vector<int>> res;
public:
    std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        std::vector<bool> used(nums.size(), false);
        backtrace(nums, used);
        return res;
    }

    void backtrace(std::vector<int>& nums, std::vector<bool>& used){
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

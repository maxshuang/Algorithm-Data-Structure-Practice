/*
 * Given an array nums of distinct integers, return all the possible permutations. 
 You can return the answer in any order.

Constraints:
1 <= nums.length <= 6
-10 <= nums[i] <= 10
All the integers of nums are unique.
 */

#include <vector>

class Solution {
    std::vector<int> path;
    std::vector<std::vector<int>> res;
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        std::vector<bool> visited(nums.size(), false);
        backtrace(nums, visited);
        return res;
    }

    void backtrace(std::vector<int>& nums, std::vector<bool>& visited) {
        int size=nums.size();
        // base case
        if(path.size()==size) {
            res.push_back(path);
            return;
        }

        for(int i=0; i<size; ++i) {
            if(visited[i]==true) {
                continue;
            }
            // add to path
            visited[i]=true;
            path.emplace_back(nums[i]);

            backtrace(nums, visited);
            
            // revert the node
            visited[i]=false;
            path.pop_back();
        }
    }
};

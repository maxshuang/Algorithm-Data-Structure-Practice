/*
 *Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:
0 <= a, b, c, d < n
a, b, c, and d are distinct.
nums[a] + nums[b] + nums[c] + nums[d] == target
You may return the answer in any order.

Constraints:
1 <= nums.length <= 200
-109 <= nums[i] <= 109
-109 <= target <= 109
*/

/*
Solution:
reduce to solving this problem until we meet two-sum problem.
Time Complexity: O(N^3), after sorting
Space Complexity: O(1)
*/

#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {
        if (nums.size() < 4) {
            return {};
        }
        std::sort(nums.begin(), nums.end());
        int length=nums.size();
        std::vector<std::vector<int>> res;
        // sum4
        for(int i=0; i<nums.size()-3; ++i) {
            if(i>0 && nums[i]==nums[i-1]) {
                continue;
            }
            // truncate path
            if ((long) nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) {
                break;
            }
            if ((long) nums[i] + nums[length - 3] + nums[length - 2] + nums[length - 1] < target) {
                continue;
            }

            int target3=target-nums[i];
            int start3=i+1;
            // sum3
            for(int j=start3; j<nums.size()-2; ++j) {
                if(j>start3 && nums[j]==nums[j-1]) {
                    continue;
                }

                // truncate path
                if ((long)nums[j] + nums[j + 1] + nums[j + 2] > target3) {
                    break;
                }
                if ((long) nums[j] + nums[length - 2] + nums[length - 1] < target3) {
                    continue;
                }

                // sum2, O(N)
                long target2=(long)target3-nums[j];
                int start2=j+1;
                int start=start2, end=nums.size()-1;
                while(start<end){
                    int sum=nums[start]+nums[end];
                    if(sum==target2){
                        res.push_back({nums[i], nums[j], nums[start], nums[end]});
                        while(start<end&&nums[start]==nums[start+1]) {
                            ++start;
                        }
                        while(start<end&&nums[end]==nums[end-1]) {
                            --end;
                        }
                        ++start;
                        --end;
                    }else if(sum<target2){
                        ++start;
                    }else {
                        --end;
                    }
                }
            }
        }
        return res;
    }
};

/*
 *You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.
Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.

Constraints:
1 <= nums.length <= 100
0 <= nums[i] <= 400
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    int rob(std::vector<int>& nums) {
        if(nums.size()==1) return nums[0];

        // dp[i]=max(dp[i-1], dp[i-2]+nums[i])
        int dp_i1=std::max(nums[0], nums[1]);
        int dp_i2=nums[0];
        for(int i=2; i<nums.size(); ++i) {
            int tmp=std::max(dp_i1, dp_i2+nums[i]);
            dp_i2=dp_i1;
            dp_i1=tmp;
        }

        return dp_i1;
    }
};

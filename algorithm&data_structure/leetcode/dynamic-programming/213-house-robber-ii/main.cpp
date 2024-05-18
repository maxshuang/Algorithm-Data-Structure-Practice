/*
 * You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed. All houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, adjacent houses have a security system connected, and it will automatically contact the police if two adjacent houses were broken into on the same night.
Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.

Constraints:
1 <= nums.length <= 100
0 <= nums[i] <= 1000
 */
#include <vector>
#include <algorithm>

class Solution {
public:
    int rob(std::vector<int>& nums) {
        if(nums.size()==1) return nums[0];
        if(nums.size()==2) return std::max(nums[0], nums[1]);

        int size=nums.size();
        return std::max(robRange(nums, 0, size-2), robRange(nums, 1, size-1));
    }

    int robRange(std::vector<int>& nums, int i, int j){
        // dp[i]=max(dp[i-1], dp[i-2]+nums[i])
        int dp_i1=std::max(nums[i], nums[i+1]);
        int dp_i2=nums[i];
        for(int k=i+2; k<j+1; ++k) {
            int tmp=std::max(dp_i1, dp_i2+nums[k]);
            dp_i2=dp_i1;
            dp_i1=tmp;
        }

        return dp_i1;
    }
};

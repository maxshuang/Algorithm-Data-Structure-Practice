/*
 * Given an integer array nums, handle multiple queries of the following type:
Calculate the sum of the elements of nums between indices left and right inclusive where left <= right.
Implement the NumArray class:
NumArray(int[] nums) Initializes the object with the integer array nums.
int sumRange(int left, int right) Returns the sum of the elements of nums between indices left and right inclusive (i.e. nums[left] + nums[left + 1] + ... + nums[right]).

Constraints:
1 <= nums.length <= 104
-105 <= nums[i] <= 105
0 <= left <= right < nums.length
At most 104 calls will be made to sumRange.
 */
#include <vector>

class NumArray {
    // sum before i
    std::vector<int> preSum;
public:
    NumArray(std::vector<int>& nums) {
        preSum.push_back(0);
        for(int i=0; i<nums.size(); ++i) {
            preSum.push_back(preSum.back()+nums[i]);
        }
    }

    int sumRange(int left, int right) {
        return preSum[right+1]-preSum[left];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */

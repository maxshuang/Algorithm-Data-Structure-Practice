/*
 Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.
Note that you must do this in-place without making a copy of the array.

Constraints:
1 <= nums.length <= 104
-231 <= nums[i] <= 231 - 1
*/

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int slow=0, fast=0;
        int length=nums.size();
        while(fast<length){
            if(nums[fast]!=0){
                nums[slow]=nums[fast];
                ++slow;
            }
            ++fast;
        }
        // set the rest to 0
        while(slow<length){
            nums[slow]=0;
            ++slow;
        }
    }
};

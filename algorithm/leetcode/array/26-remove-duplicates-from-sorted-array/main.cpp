/*
 Given an integer array nums sorted in non-decreasing order, remove the duplicates in-place such that each unique element appears only once. The relative order of the elements should be kept the same. Then return the number of unique elements in nums.

Consider the number of unique elements of nums to be k, to get accepted, you need to do the following things:

Change the array nums such that the first k elements of nums contain the unique elements in the order they were present in nums initially. The remaining elements of nums are not important as well as the size of nums.
Return k.

Constraints:
1 <= nums.length <= 3 * 104
-100 <= nums[i] <= 100
nums is sorted in non-decreasing order.
*/

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int length=nums.size();
        if(length==0) return 0;
        int slow=0, fast=0;
        
        while(fast<length){
            // find a different one, move forward slow
            if(nums[fast]!=nums[slow]){
                ++slow;
                nums[slow]=nums[fast];
            }
            ++fast;
        }
        return slow+1;
    }
};

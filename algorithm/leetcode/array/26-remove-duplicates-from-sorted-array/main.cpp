/*
 Given an integer array nums sorted in non-decreasing order, remove the duplicates in-place such that each unique element appears only once. 
The relative order of the elements should be kept the same. Then return the number of unique elements in nums.

Consider the number of unique elements of nums to be k, to get accepted, you need to do the following things:

Change the array nums such that the first k elements of nums contain the unique elements in the order they were present in nums initially. 
The remaining elements of nums are not important as well as the size of nums.
Return k.

Constraints:
1 <= nums.length <= 3 * 104
-100 <= nums[i] <= 100
nums is sorted in non-decreasing order.
*/

/*
Solution: 
For a sorted array, so basically, we need to exchange the pos of duplicated elements with non-duplicated elements.
Traditionally, we use fast-slow pointer to meet our needs.
1. Fast pointer will continue to move forward until it finds the first pos that has different value with its precedent pos.
2. Slow pointer will continue to move forward until it finds the first pos that has same value with its prececent pos.
3. Then exchange their value, and repeat step 1 again.

A simpler solution:
1. Fast pointer finds the next unique element.
2. Let slow pointer points to next valid pos.
3. Put the element to which the fast pointer points to the next valid pos.
4. End until fast pointer bypasses the end of array. 

Time Complexity: O(N), it ends when first point exceeds the end of the array.
Space Complexity: O(1)
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

/*
Given an integer array nums and an integer val, remove all occurrences of val in nums in-place. 
The order of the elements may be changed. Then return the number of elements in nums which are not equal to val.
Consider the number of elements in nums which are not equal to val be k, to get accepted, you need to do the following things:
Change the array nums such that the first k elements of nums contain the elements which are not equal to val. 
The remaining elements of nums are not important as well as the size of nums. 
Return k

Constraints:
0 <= nums.length <= 100
0 <= nums[i] <= 50
0 <= val <= 100
*/

/*
Same as the problem of removing duplicated element. 
Find value that is not 'val' and move it to the front one by one.

Time Complexity: O(N)
Space Complexity: O(1)
*/

#include <vector>

class Solution {
public:
    int removeElement(std::vector<int>& nums, int val) {
       int slow=0, fast=0;
       int length=nums.size();
       while(fast<length){
           if(nums[fast]!=val){
               nums[slow]=nums[fast];
               ++slow;
           }
           ++fast;
       }
       return slow;
    }
};

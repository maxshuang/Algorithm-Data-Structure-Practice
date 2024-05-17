/*
 * Given an integer array nums and an integer k, split nums into k non-empty subarrays such that the largest sum of any subarray is minimized.
Return the minimized largest sum of the split.
A subarray is a contiguous part of the array.

Constraints:
1 <= nums.length <= 1000
0 <= nums[i] <= 106
1 <= k <= min(50, nums.length)
 */

/*
classic min-max problem. 
the relationship of the largest sum of any subarray and the number of non-empty subarrays is monotonical, non-increasing. [max(nums), sum(nums)]
*/

#include <vector>
#include <algorithm>

class Solution {
public:
    int splitArray(std::vector<int>& nums, int k) {
       // given a specified x, we can split the array into several subarrays which has sums smaller than x. As we increasing x, we can find the total parts of split becomes small and reach 1 at last.
       // so we can binary search to find the lower bound of x when we get k splits
        int sum=0;
        int maxi=-1;
        for(int num: nums){
            sum+=num;
            maxi=std::max(maxi, num);
        }

        int size=nums.size();
        int start=maxi;
        int end=sum;
        // find the lower_bound
        while(start<=end) {
            int mid=start+(end-start)/2;
            // get splits
            int split=1;
            int cap=mid;
            for(int i=0; i<size; ++i){
                if(cap>=nums[i]){
                    cap-=nums[i];
                    continue;
                }
                ++split;
                cap=mid-nums[i];
            }

            // judge
            if(split<=k){
                end=mid-1;
            }else {
                start=mid+1;
            }
        }

        // we can always find a x
        return start;
    }
};

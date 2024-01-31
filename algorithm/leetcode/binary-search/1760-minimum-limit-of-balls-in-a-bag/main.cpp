/*
 * You are given an integer array nums where the ith bag contains nums[i] balls. You are also given an integer maxOperations.
You can perform the following operation at most maxOperations times:
Take any bag of balls and divide it into two new bags with a positive number of balls.
For example, a bag of 5 balls can become two new bags of 1 and 4 balls, or two new bags of 2 and 3 balls.
Your penalty is the maximum number of balls in a bag. You want to minimize your penalty after the operations.
Return the minimum possible penalty after performing the operations.

Constraints:
1 <= nums.length <= 10^5
1 <= maxOperations, nums[i] <= 10^9
 */

class Solution {
public:
    int minimumSize(vector<int>& nums, int maxOperations) {
        // give a specified minMax, we can split the nums and get a corresponding operation.
        // the operation is a non-increasing sequence
        // using binary research
        int maxi=0;
        for(int num: nums){
            maxi=max(maxi, num);
        }

        int n=nums.size();
        int start=1;
        int end=maxi;
        while(start<=end){
            int mid=start+(end-start)/2;
            long long operation=0;
            for(int num: nums){
                operation+=(num-1)/mid;
            }

            // judge
            if(operation<=maxOperations){
                end=mid-1;
            }else {
                start=mid+1;
            }
        }

        return start;
    }
};

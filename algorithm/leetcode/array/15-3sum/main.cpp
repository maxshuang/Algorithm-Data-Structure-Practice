/*
 * Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
Notice that the solution set must not contain duplicate triplets.

Constraints:
3 <= nums.length <= 3000
-105 <= nums[i] <= 105
*/

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        // O(N^2)
        int size=nums.size();
        for(int i=0; i<size-2; ++i) {
            // skip duplicate
            if(i>0 && nums[i]==nums[i-1]){
                continue;
            }

            int target = -nums[i];
            // quick path
            if(nums[i+1]+nums[i+2]>target) {
                break;
            }
            if(nums[size-1]+nums[size-2]<target) {
                continue;
            }

            // change to two-sum problem
            // O(N)
            int start=i+1;
            int j=start, k=size-1;
            while(j<k) {
                int sum=nums[j]+nums[k];
                if(sum==target){
                    res.push_back({nums[i], nums[j], nums[k]});
                    while(j<k&&nums[j]==nums[j+1]){
                        ++j;
                    }
                    while(j<k&&nums[k]==nums[k-1]){
                        --k;
                    }
                    ++j;
                    --k;
                }else if(sum>target){
                    --k;
                }else {
                    ++j;
                }
            }
            }

        return res;
    }
};

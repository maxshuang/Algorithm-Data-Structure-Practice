/*
 * Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]],
such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
Notice that the solution set must not contain duplicate triplets.

Constraints:
3 <= nums.length <= 3000
-105 <= nums[i] <= 105
*/

/*
Solution:
reduce to solving this problem until we meet two-sum problem.
Time Complexity: O(NlogN), after sorting, the time complexity of a single two-sum problem can be O(logN).
Space Complexity: O(1)
*/
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        // O(NlogN)
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> res;
        // O(N^2) => O(NlogN)
        // An interesting thing is, a O(NlogN) sorting can reduce a single term of two-sum problem to O(logN)
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

            // change to two-sum problem for a sort array
            // O(N), Can optimize to O(logN) for binary search
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

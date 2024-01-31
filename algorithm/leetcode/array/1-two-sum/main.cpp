/*
 * 
Problem
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.
You can return the answer in any order.

Constraints:
2 <= nums.length <= 104
-109 <= nums[i] <= 109
-109 <= target <= 109
Only one valid answer exists.

Illustration
A classic approach to finding the sum of two numbers.
Solution 1:
The simplest approach is brute force, where we iteratively calculate the sum of two numbers and compare it to the target. If they match, that is the answer to this problem.
Time complexity: O(N^2). There are a total of N*(N-1)/2 combinations when summing two numbers.
Space complexity: O(1). No additional space is needed.


Solution 2:

Another solution for such sum problems is to use sorting when the results exhibit monotonicity. This can reduce the time complexity to O(NlogN). In this case, since the data distribution doesn't inherently have monotonicity, implementing a sorting algorithm can provide order to the sum results.
Time complexity: O(N^2 + NlogN) or O(N + NlogN). Some efficient sorting algorithms, like quicksort, already require O(N^2), but using radix sort can bring sorting time down to O(N), and monotonic sum searching requires O(NlogN).
Space complexity: O(N). Sorting disrupts the original order of data, so additional storage is needed for both the data and its original order, resulting in O(N) space requirement.


Solution 3:

When the data is unsorted, an efficient way to search is by utilizing a hashtable to achieve an amortized O(1) search efficiency. The key detail here is how to use the hashtable. If all the data is initially placed in the hashtable and then traversed, the issue arises that it becomes challenging to differentiate duplicate data entries from the original data (<4>, <4,4>). Therefore, additional work is needed, such as storing the count of each data item, like <num, count>, e.g., <4, 2>, to distinguish such cases. This adds complexity. Therefore, the recommended approach is to dynamically add data to the hashtable, which avoids the problem of identical data items.
Time complexity: Amortized O(N). For each element, we check if residue (target-item) is in the hashtable.
Space complexity: O(N). It may be necessary to store all the elements.
 */

class Solution3 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashtable;
        for (int i = 0; i < nums.size(); ++i) {
            auto it = hashtable.find(target - nums[i]);
            if (it != hashtable.end()) {
                return {it->second, i};
            }
            // latter one will find the former one
            hashtable[nums[i]] = i;
        }
        return {};
    }
};

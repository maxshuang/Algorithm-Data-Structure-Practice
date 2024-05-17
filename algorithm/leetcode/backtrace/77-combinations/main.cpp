/*
 * Given two integers n and k, return all possible combinations of k numbers chosen from the range [1, n].
You may return the answer in any order.

Constraints:
1 <= n <= 20
1 <= k <= n
 */

#include <vector>

class Solution {
    std::vector<int> combination;
    std::vector<std::vector<int>> res;
public:
    std::vector<std::vector<int>> combine(int n, int k) {
        backtrace(n, k, 1);
        return res;
    }

    void backtrace(int n, int k, int start) {
        // end condition
        if(combination.size()==k){
            res.push_back(combination);
            return;
        }

        for(int i=start; i<n+1; ++i) {
            // make selection
            combination.push_back(i);
            backtrace(n, k, i+1);
            // revert seletion
            combination.pop_back();
        }
    }
};

/*
 Find all valid combinations of k numbers that sum up to n such that the following conditions are true:

Only numbers 1 through 9 are used.
Each number is used at most once.
Return a list of all possible valid combinations. The list must not contain the same combination twice, and the combinations may be returned in any order.

Constraints:
2 <= k <= 9
1 <= n <= 60
 */

class Solution {
    vector<int> combination;
    int preSum;
    vector<vector<int>> res;
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        res.clear();
        backtrace(k, n, 0, 1);
        return res;
    }

    void backtrace(int k, int n, int depth, int start) {
        // end condition
        if(depth==k && preSum==n){
            res.push_back(combination);
            return;
        }

        for(int i=start; i<10 && preSum+i<=n; ++i) {
            // make selection
            preSum+=i;
            combination.push_back(i);
            backtrace(k, n, depth+1, i+1);
            // revert seletion
            preSum-=i;
            combination.pop_back();
        }
    }
};

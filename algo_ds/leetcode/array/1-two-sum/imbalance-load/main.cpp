/*
Possible solution:
1. brute force: for O(N*N) range, need O(1) to find out the max diff, maintain the max and min
2. slice window? How to quickly find out the max diff in a window ?
3. classic range query problem? BIT? SegmentTree?
*/
#include <vector>

class Solution {
    int segementCnt(const std::vector<int>& weights, int k) {
        int cnt=0;
        for(int i=0; i<weights.size(); ++i) {
            int min=100000000;
            int max=weights[i];
            for(int j=i; j<weights.size(); ++j) {
                if(weights[j]>=min && weights[j]<=max) {
                    ++cnt;
                    continue;
                }
                
                if(weights[j]<min) {
                    min=weights[j];
                }else if(weights[j]>max) {
                    max=weights[j];
                }

                if(max-min <= k) ++cnt;
                else break;
            }
        }

        return cnt;
    }
};
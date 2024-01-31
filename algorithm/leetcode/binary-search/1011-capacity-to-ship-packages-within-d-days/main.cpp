/*
 * A conveyor belt has packages that must be shipped from one port to another within days days.
The ith package on the conveyor belt has a weight of weights[i]. Each day, we load the ship with packages on the conveyor belt (in the order given by weights). We may not load more weight than the maximum weight capacity of the ship.
Return the least weight capacity of the ship that will result in all the packages on the conveyor belt being shipped within days days.

Constraints:
1 <= days <= weights.length <= 5 * 104
1 <= weights[i] <= 500
 */

class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        // the result is between [max(w[i]), sum(w[i)], and non-decreasing, using binary search
        int maxi=0;
        int sum=0;
        for(int w: weights){
            maxi=max(w, maxi);
            sum+=w;
        }

        int start=maxi;
        int end=sum;
        // find left bound for non-increasing sequeue
        while(start<=end){
            int mid = start+(end-start)/2;

            // calculate the minDay we need to ship all cargos
            int minDays=1;
            int cap=mid;
            for(int j=0; j<weights.size(); ++j){
                if(cap>=weights[j]) {
                    cap-=weights[j];
                    continue;
                }
                // next day
                ++minDays;
                cap=mid-weights[j];
            }

            // judge
            if(minDays>days) {
                start=mid+1;
            }else {
                end=mid-1;
            }
        }

        return start;
    }
};

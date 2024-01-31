/*
 *Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.
Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.
Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.
Return the minimum integer k such that she can eat all the bananas within h hours.

Constraints:
1 <= piles.length <= 104
piles.length <= h <= 109
1 <= piles[i] <= 109
 */

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int maxi=0;
        for(int pile: piles) {
            maxi=max(maxi, pile);
        }

        int start=1, end=maxi;
        while(start<=end) {
            int mid=(start+end)/2;
            if(check(piles, h, mid)) {
                end=mid-1;
            }else {
                start=mid+1;
            }
        }

        return start;
    }

    bool check(vector<int>& piles, int h, int speed) {
        long long needHour=0;
        for(int i=0; i<piles.size(); ++i) {
            needHour+=((piles[i]-1)/speed+1);
        }

        return needHour<=h;
    }
};

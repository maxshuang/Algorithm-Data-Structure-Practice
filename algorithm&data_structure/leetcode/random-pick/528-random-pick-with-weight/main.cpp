/*
 *You are given a 0-indexed array of positive integers w where w[i] describes the weight of the ith index.
You need to implement the function pickIndex(), which randomly picks an index in the range [0, w.length - 1] (inclusive) and returns it. The probability of picking an index i is w[i] / sum(w).
For example, if w = [1, 3], the probability of picking index 0 is 1 / (1 + 3) = 0.25 (i.e., 25%), and the probability of picking index 1 is 3 / (1 + 3) = 0.75 (i.e., 75%).

Constraints:
1 <= w.length <= 104
1 <= w[i] <= 105
pickIndex will be called at most 104 times.
 */

class Solution {
    vector<int> buckets;
    int bck;
    int ibck;
public:
    Solution(vector<int>& w):buckets(w), bck(0), ibck(0){
        float sum=0, mini=1000000;
        for(int wi: w) {
            sum+=wi;
            mini=min((float)wi, mini);
        }
        // using bucket to simulate the distribution of probability, so we can get the same distribution when we have a small nums of sample
        float miniv=mini/sum;
        int k=1;
        while(miniv*k<1) k*=10;
        buckets.resize(w.size());
        for(int i=0; i<w.size(); ++i) {
            buckets[i]=(int)(w[i]/sum*k);
        }
    }

    int pickIndex() {
         if(bck>=buckets.size()) {
            bck=0;
        }

        if(ibck<buckets[bck]){
            ++ibck;
            return bck;
        }

        ++bck;
        ibck=0;
        return pickIndex();
    }
};


class Solution {
    vector<int> preSum;
public:
    Solution(vector<int>& w) {
        srand(0);
        preSum.resize(w.size());
        preSum[0]=w[0];
        for(int i=1; i<w.size(); ++i){
            preSum[i]=preSum[i-1]+w[i];
        }
    }

    int pickIndex() {
        int random=rand()%preSum.back()+1;
        // find first index which value is not less than rand
        int start=0, end=preSum.size()-1;
        while(start<end) {
            int mid=start+(end-start)/2;
            if(preSum[mid]<random) {
                start=mid+1;
            }else {
                end=mid;
            }
        }

        // start==end
        return start;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */

/*
 *You are given a 0-indexed array of positive integers w where w[i] describes the weight of the ith index.
You need to implement the function pickIndex(), which randomly picks an index in the range [0, w.length - 1] (inclusive) and returns it. The probability of picking an index i is w[i] / sum(w).
For example, if w = [1, 3], the probability of picking index 0 is 1 / (1 + 3) = 0.25 (i.e., 25%), and the probability of picking index 1 is 3 / (1 + 3) = 0.75 (i.e., 75%).

Constraints:
1 <= w.length <= 104
1 <= w[i] <= 105
pickIndex will be called at most 104 times.
 */

#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <map>
#include "catch.hpp"

class Solution
{
    std::vector<int> buckets;
    int bck;
    int ibck;

public:
    Solution(const std::vector<int> &w) : buckets(w), bck(0), ibck(0)
    {
        float sum = 0, mini = 1000000;
        for (int wi : w)
        {
            sum += wi;
            mini = std::min((float)wi, mini);
        }
        // using bucket to simulate the distribution of probability, so we can get the same distribution when we have a small nums of sample
        float miniv = mini / sum;
        int k = 1;
        while (miniv * k < 1)
            k *= 10;
        buckets.resize(w.size());
        for (size_t i = 0; i < w.size(); ++i)
        {
            buckets[i] = (int)(w[i] / sum * k);
        }
    }

    int pickIndex()
    {
        if (bck >= (int)buckets.size())
        {
            bck = 0;
        }

        if (ibck < buckets[bck])
        {
            ++ibck;
            return bck;
        }

        ++bck;
        ibck = 0;
        return pickIndex();
    }
};

class Solution2 {
private:
    std::mt19937 gen;
    std::uniform_int_distribution<int> dis;
    std::vector<int> pre;

public:
    Solution2(const std::vector<int>& w): gen(std::random_device{}()), dis(1, std::accumulate(w.begin(), w.end(), 0)) {
        std::partial_sum(w.begin(), w.end(), std::back_inserter(pre));
    }
    
    int pickIndex() {
        int x = dis(gen);
        return std::lower_bound(pre.begin(), pre.end(), x) - pre.begin();
    }
};

class Solution3 {
private:
    std::vector<int> pre;

public:
    Solution3(const std::vector<int>& w) {
        srand(time(nullptr));
        pre.resize(w.size());
        pre[0]=w[0];
        for(int i=1; i<(int)w.size(); ++i)
            pre[i]=pre[i-1]+w[i];
    }
    
    int pickIndex() {
        int x = rand()%pre.back();
        return std::upper_bound(pre.begin(), pre.end(), x) - pre.begin();
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */

bool floatEqual(float a, float b)
{
    return std::abs(a - b) <= 0.0001;
}

TEST_CASE("Test random-pick-with-weight", "")
{
    SECTION("test1")
    {
        Solution2 sl2(std::vector<int>{1, 3});
        std::map<int, int> pick_map;
        for (int i = 0; i < 10000; ++i)
            pick_map[sl2.pickIndex()]++;

        //REQUIRE(floatEqual((float)pick_map[0] / 1000, 0.25));
        //REQUIRE(floatEqual((float)pick_map[1] / 1000, 0.75));
    }

    SECTION("test2")
    {
        Solution2 sl2(std::vector<int>{1, 1, 2});
        std::map<int, int> pick_map;
        for (int i = 0; i < 1000; ++i)
            pick_map[sl2.pickIndex()]++;

        //REQUIRE(floatEqual((float)pick_map[0] / 1000, 0.25));
        //REQUIRE(floatEqual((float)pick_map[1] / 1000, 0.25));
        //REQUIRE(floatEqual((float)pick_map[2] / 1000, 0.5));
    }

    SECTION("test3")
    {
        Solution2 sl2(std::vector<int>{1});
        std::map<int, int> pick_map;
        for (int i = 0; i < 1000; ++i)
            pick_map[sl2.pickIndex()]++;
    }
}
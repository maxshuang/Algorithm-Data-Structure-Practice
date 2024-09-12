#define CATCH_CONFIG_MAIN
#include <iostream>
#include <iostream>
#include <ctime>
#include <unistd.h>
#include <memory> // For smart pointers
#include <queue>
#include <sys/time.h> // For gettimeofday
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <utility>
#include "catch.hpp"
using namespace std;

// Problem: rate limiter
// 1. rate limited by userID
// 2. 5 requests/pre second/minutes/hour
// 3. fix window, 
// pros： simple, high-efficient, IoT
// cons: can't handle bustry trafic, poor 
// sliding window
// Pros: handle bustry trafic, 
// Cons: log rate limiter, counter rate limiter(estimation method)
// Bucket Token, 
// Pros: allow bustry traffic at some extend(capacity of bucket)
// Leaky Token, 
// Pro: limit the traffic in a fix shape,
// advanced algorithm , 

// redis as the storage counter
// consistent hash, key->node 
// pre-allocated slots, [0-2^31-1] => [continous], [], []


// Time mock
class Timer {
    virtual int64 getUnixTimeMillis()=0;
};

class MockTimer : public Timer{
public:
    MockTimer(const std::vector<int>& times): times(times), idx(0){}
    int64 getUnixTimeMillis(){
        // [TODO]
        if(idx>=time.size()) return -1;  
        return times[idx++];
    }

private:
    std::vector<int> times;
    int idx;
};

Timer mockTimer = new MockTimer();

// define an interface
class RateLimiter {
    virtual bool IsAllow()=0;
};

// helper
RateLimiter* newBucketTokenRateLimiter(int cap, int rate, int winMillis) {
    return new BucketTokenRateLimiter(cap, rate, winMillis, mockTimer);
}

// 10 request per minute => rate=10, winMillis=1*60*1000 millis
class BucketTokenRateLimiter: public RateLimiter{
public:
    BucketTokenRateLimiter(int cap, int rate, int winMillis, Timer* timer):cap(cap), cnt(0), rate(rate), timer(timer)
    {
        curMillis=timer->getUnixTimeMillis();
    }
    
    bool IsAllow(){
        int64 nowMillis = timer->getUnixTimeMillis();

        if(nowMillis < curMillis) {
            // clock went backward
            // smoother
            cnt = cnt/2;
            curMillis=nowMillis;
            return true;
        }

        // if no tokens, refill it
        // lazy refill
        if(cnt == 0) {
            refill(nowMillis);
        }

        if(cnt>0) {
            --cnt;
            return true;
        }

        return false;
    }

private:
    void refill(int64 nowMillis) {
        int tokens = (int)((nowMillis-curMillis)/(double)winMillis)*rate;
        
        cnt = std::max(cap, tokens);
        
        if(tokens>0) {
            curMillis=nowMillis;
        }
    }

private:
    const int cap;
    // std::mutex(heavy), or std::atomic_variable(light)
    int cnt;  // tokens in the bucket,better
    int rate;
    int64 curMillis;
    int winMillis;
    // depend injection
    Timer* timer;
};

class BucketTokenLimiter {
public:
    BucketTokenLimiter(int cap, int rate, int64 winMillis, Timer* timer){}

    bool IsAllow(const std::string& user){
        if(!userRaters.count(user)) {
            userRaters.emplace(usr, newBucketTokenRateLimiter(cap, rate, winMillis));
        }

        // delegate
        return userRaters[user].IsAllow();
    }

private:
    unordered_map<string, BucketTokenRateLimiter> userRaters;
};

TEST_CASE("Normal test", "[]")
{   
    // 1 request per second
    int cap=3, rate=1;
    int64 winMillis=1000;
    
    BucketTokenLimiter rl(cap, rate, winMillis);

    REQUIRE(rl.IsAllow("alina")==true);
}

TEST_CASE("Abnormal test", "[]")
{  
    REQUIRE(1==0);
}
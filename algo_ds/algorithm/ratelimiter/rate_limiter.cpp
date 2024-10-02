#include <iostream>
#include <ctime>
#include <unistd.h>
#include <memory> // For smart pointers
#include <queue>
#include <sys/time.h> // For gettimeofday
#include <algorithm>

// Creator helper
//std::shared_ptr<RateLimiter> NewRateLimiterInSeconds(int cap, int seconds);
//std::shared_ptr<RateLimiter> NewRateLimiterInMinutes(int cap, int minutes);
//std::shared_ptr<RateLimiter> NewRateLimiterInHours(int cap, int hours);
// or Factory method

// Clock Backward strategy
// New Clock

// [TODO]: change to interface
struct Clock {
	int64_t getUnixTimeMillis(){
		// long tv_sec; long tv_usec;
		timeval tv;
		gettimeofday(&tv, nullptr);
		// Convert timeval to milliseconds
		int64_t millis = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
		return millis;
	}
};

// interface
struct RateLimiter {
    virtual bool IsAllowed()=0;
};

///
/// FixWindowRateLimiter
///
class FixWindowRateLimiter : public RateLimiter {
public:
    FixWindowRateLimiter(int cap, int winMillis, Clock* clock);
    // Time: O(1), Space: O(1)
	// Can't handle the burst of traffic at the edge of adjacent windows
	bool IsAllowed();
	virtual ~FixWindowRateLimiter(){}
private:
    Clock *clock;
    int64_t curMillis;
    int cnt;
	// define as const
    const int cap;
    const int winMillis;
};

FixWindowRateLimiter::FixWindowRateLimiter(int cap, int winMillis, Clock* ck=new Clock())
    : clock(ck), curMillis(0), cnt(0), cap(cap), winMillis(winMillis) {
    if (cap <= 0 || winMillis <= 0) {
		// standard std for C++
        throw std::invalid_argument("cap and win must be positive integers.");
    }
    curMillis=clock->getUnixTimeMillis();
}

bool FixWindowRateLimiter::IsAllowed() {
    int64_t nowMillis = clock->getUnixTimeMillis();
    int64_t diff = nowMillis - curMillis;

    if (diff < 0) {
        // Clock went backward or overflow; handle this gracefully
		// Don't just return false, it will fail the system 
		// [NOTE]: log warn here
        curMillis = nowMillis;
		// A bit aggressive, can be smoother, such as cnt=cnt/2+1;
        cnt = 1;
        return true;
    }

    if (diff < winMillis) {
        if (cnt < cap) {
            ++cnt;
            return true;
        } else {
            return false;
        }
    } else {
        curMillis = nowMillis;
        cnt = 1;
        return true;
    }
}

//assertFalse(limiter.allowed(BOB),
//        "Bob's request 5 at timestamp=2001 must not be allowed");
void Test_Normal_FixWin() {
    std::cout << "normal:" << std::endl;
    auto rl = std::make_unique<FixWindowRateLimiter>(2, 1000);
    std::cout << (rl->IsAllowed() == true) << std::endl; 
    std::cout << (rl->IsAllowed() == true) << std::endl;
    std::cout << (rl->IsAllowed() == false) << std::endl;
    sleep(1);
    std::cout << (rl->IsAllowed() == true) << std::endl;
}

void Test_CornerCase1_FixWin() {
    std::cout << "corner case 1:" << std::endl;
    auto rl = std::make_unique<FixWindowRateLimiter>(1, 1000);
    std::cout << (rl->IsAllowed() == true) << std::endl; 
    std::cout << (rl->IsAllowed() == false) << std::endl;
    sleep(1);
    std::cout << (rl->IsAllowed() == true) << std::endl;
    sleep(1);
    std::cout << (rl->IsAllowed() == true) << std::endl;
}

void Test_CornerCase2_FixWin() {
    std::cout << "corner case 2: handle burst traffic" << std::endl;
    auto rl = std::make_unique<FixWindowRateLimiter>(3, 2000);
	usleep(1900000);
    std::cout << (rl->IsAllowed() == true) << std::endl; 
    std::cout << (rl->IsAllowed() == true) << std::endl;
    std::cout << (rl->IsAllowed() == true) << std::endl;
	usleep(200000); // 200ms
    std::cout << (rl->IsAllowed() == true) << std::endl;
    std::cout << (rl->IsAllowed() == true) << std::endl;
	std::cout << (rl->IsAllowed() == true) << std::endl;
}

///
/// SlidingWindow
///
class SlidingWindowLogRateLimiter : public RateLimiter {
public:
    SlidingWindowLogRateLimiter(int cap, int winMillis, Clock *clock);
    // Time: O(1), Space: O(N)
	virtual bool IsAllowed(); 
	virtual ~SlidingWindowLogRateLimiter(){}
private:
	// Solution1: We could reduce the Space complexity by grouping the request to a specific granularity
	// like 100ms
	// Solution2: Actually we don't care about the request, so we can estimate the request
	// of the overlapped range
	std::queue<int64_t> que;
    int cnt;
	// define as const
    const int cap;
    const int winMillis;
    Clock *clock;
};

SlidingWindowLogRateLimiter::SlidingWindowLogRateLimiter(int cap, int winMillis, Clock* clock=new Clock())
    : cnt(0), cap(cap), winMillis(winMillis), clock(clock) {
    if (cap <= 0 || winMillis <= 0) {
		// standard std for C++
        throw std::invalid_argument("cap and win must be positive integers.");
    }
}

bool SlidingWindowLogRateLimiter::IsAllowed() {
	int64_t nowMillis = clock->getUnixTimeMillis();
	// clock went backward
	if(!que.empty() && nowMillis<que.back()) {
		std::queue<time_t> empty;
		que.swap(empty);
		cnt=1;
		que.emplace(nowMillis);
		return true;
	}

	// std::queue: front, back, emplace/push, pop
	while(!que.empty() && winMillis<=(nowMillis-que.front())) {
		que.pop();
		--cnt;
	}

	if(cnt<=cap) {
    que.emplace(nowMillis);
	  ++cnt;
    return true;
  }

	return false;
}

void Test_Normal_SlidingWin() {
    std::cout << "normal:" << std::endl;
    auto rl = std::make_unique<SlidingWindowLogRateLimiter>(2, 1000);
    std::cout << (rl->IsAllowed() == true) << std::endl; 
    std::cout << (rl->IsAllowed() == true) << std::endl;
    std::cout << (rl->IsAllowed() == false) << std::endl;
    sleep(2);
    std::cout << (rl->IsAllowed() == true) << std::endl;
}

void Test_CornerCase1_SlidingWin() {
    std::cout << "corner case 1:" << std::endl;
    auto rl = std::make_unique<SlidingWindowLogRateLimiter>(1, 1000);
    std::cout << (rl->IsAllowed() == true) << std::endl; 
    std::cout << (rl->IsAllowed() == false) << std::endl;
    sleep(1);
    std::cout << (rl->IsAllowed() == true) << std::endl;
    sleep(1);
    std::cout << (rl->IsAllowed() == true) << std::endl;
}

void Test_CornerCase2_SlidingWin() {
    std::cout << "corner case 2: handle burst traffic" << std::endl;
    auto rl = std::make_unique<SlidingWindowLogRateLimiter>(3, 2000);
	usleep(1900000);
    std::cout << (rl->IsAllowed() == true) << std::endl; 
    std::cout << (rl->IsAllowed() == true) << std::endl;
    std::cout << (rl->IsAllowed() == true) << std::endl;
	usleep(200000); // 200ms
    std::cout << (rl->IsAllowed() == false) << std::endl;
    std::cout << (rl->IsAllowed() == false) << std::endl;
	std::cout << (rl->IsAllowed() == false) << std::endl;
}

class SlidingWindowCounterRateLimiter : public RateLimiter {
public:
    SlidingWindowCounterRateLimiter(int cap, int winMillis);
    virtual bool IsAllowed(); 
    virtual ~SlidingWindowCounterRateLimiter() = default;
private:
    Clock clock;
    int64_t preMillis;
    int preCnt;
    int64_t curMillis;
    int curCnt;
    const int cap;
    const int winMillis;

    double calculatePreWeight(int64_t nowMillis);
};

SlidingWindowCounterRateLimiter::SlidingWindowCounterRateLimiter(int cap, int winMillis)
    : preMillis(0), preCnt(0), curMillis(0), curCnt(0), cap(cap), winMillis(winMillis) {
    if (cap <= 0 || winMillis <= 0) {
        throw std::invalid_argument("cap and winMillis must be positive integers.");
    }
    preMillis = this->clock.getUnixTimeMillis();
    curMillis = preMillis;
}

double SlidingWindowCounterRateLimiter::calculatePreWeight(int64_t nowMillis) {
    int64_t winStart = std::max((int64_t)0, nowMillis - winMillis);
    int64_t winEnd = preMillis + winMillis;
    // when preMillis==curMillis at the beginning, preWeight can > 1, but preCnt=0
    // so it doesn't matter
    return std::max(0.0, (winEnd - winStart) / (double)winMillis);
}

bool SlidingWindowCounterRateLimiter::IsAllowed() {
    int64_t nowMillis = clock.getUnixTimeMillis();

    if (nowMillis < curMillis) {
        // Handle clock rollback
        return false;
    }

    if ((nowMillis - curMillis) > winMillis) {
        // Move the window forward
        preMillis = curMillis;
        preCnt = curCnt;
        curMillis = nowMillis;
        curCnt = 0;
    }

    double preWeight = calculatePreWeight(nowMillis);
    //std::cout << "preWeight:" << preWeight << std::endl;
    if ((int)(preWeight * preCnt + curCnt) < cap) {
        ++curCnt;
        return true;
    }

    return false;
}

void Test_Normal_SlidingWinCounter() {
    std::cout << "normal:" << std::endl;
    auto rl = std::make_unique<SlidingWindowCounterRateLimiter>(2, 1000);
    std::cout << (rl->IsAllowed() == true) << std::endl; 
    std::cout << (rl->IsAllowed() == true) << std::endl;
    std::cout << (rl->IsAllowed() == false) << std::endl;
    sleep(2);
    std::cout << (rl->IsAllowed() == true) << std::endl;
}

void Test_CornerCase1_SlidingWinCounter() {
    std::cout << "corner case 1:" << std::endl;
    auto rl = std::make_unique<SlidingWindowCounterRateLimiter>(1, 1000);
    std::cout << (rl->IsAllowed() == true) << std::endl; 
    std::cout << (rl->IsAllowed() == false) << std::endl;
    usleep(1100000);
    std::cout << (rl->IsAllowed() == true) << std::endl;
    usleep(1100000);
    std::cout << (rl->IsAllowed() == true) << std::endl;
}

void Test_CornerCase2_SlidingWinCounter() {
    std::cout << "corner case 2: handle burst traffic" << std::endl;
    auto rl = std::make_unique<SlidingWindowCounterRateLimiter>(3, 3000);
    usleep(2900000);
    std::cout << (rl->IsAllowed() == true) << std::endl; 
    std::cout << (rl->IsAllowed() == true) << std::endl;
    std::cout << (rl->IsAllowed() == true) << std::endl;
    std::cout << (rl->IsAllowed() == false) << std::endl;
    usleep(100000); // 100ms
    usleep(1000000); // 1s
    std::cout << (rl->IsAllowed() == true) << std::endl;
    std::cout << (rl->IsAllowed() == false) << std::endl;
    usleep(1000000); // 1s
	  std::cout << (rl->IsAllowed() == true) << std::endl;
}

class TokenBucketRateLimiter : public RateLimiter {
public:
    TokenBucketRateLimiter(int cap, int rate, int winMillis);
    virtual bool IsAllowed(); 
    virtual ~TokenBucketRateLimiter() = default;
private:
    Clock clock;
    int tokens;
    int64_t curMillis;
    const int rate; // pre winMillis
    const int cap;
    const int winMillis;

    void refill();
};

TokenBucketRateLimiter::TokenBucketRateLimiter(int cap, int rate, int winMillis):
tokens(0), curMillis(clock.getUnixTimeMillis()), rate(rate), cap(cap), winMillis(winMillis){}

void TokenBucketRateLimiter::refill() {
    // greedy, not interval-based
    // for interval-based algorithm, you can just jump to the last interval previous to nowMillis
    int64_t nowMillis = clock.getUnixTimeMillis();
    tokens= std::min(cap, (int)(rate*(nowMillis-curMillis)/(double)winMillis));
    if(tokens>0)
        curMillis=nowMillis;
}

bool TokenBucketRateLimiter::IsAllowed() {
    // lazy refill
    if(tokens==0) refill();

    if(tokens>0) {
        --tokens;
        return true;
    }

    return false;
}

void Test_CornerCase2_TokenBucket() {
    std::cout << "corner case 2: handle burst traffic" << std::endl;
    auto rl = std::make_unique<TokenBucketRateLimiter>(5, 1, 500);
    sleep(1);
    std::cout << (rl->IsAllowed() == true) << std::endl; 
    std::cout << (rl->IsAllowed() == true) << std::endl;
    // consume up all buckets
    std::cout << (rl->IsAllowed() == false) << std::endl;
    sleep(3);
    for(int i=0; i<5; ++i) rl->IsAllowed();
    // reach the cap
    std::cout << (rl->IsAllowed() == false) << std::endl;
    sleep(1); // 1s
	  std::cout << (rl->IsAllowed() == true) << std::endl;
    std::cout << (rl->IsAllowed() == true) << std::endl;
}

class LeakyBucketRateLimiter : public RateLimiter {
public:
    LeakyBucketRateLimiter(int cap, int leakRate, int winMillis);
    virtual bool IsAllowed(); 
    virtual ~LeakyBucketRateLimiter() = default;
private:
    Clock clock;
    int waterLevel;
    int64_t curMillis;
    const int cap;
    const int leakRate; // pre winMillis
    const int winMillis;

    void leak();
};

LeakyBucketRateLimiter::LeakyBucketRateLimiter(int cap, int leakRate, int winMillis): waterLevel(0),
curMillis(clock.getUnixTimeMillis()), cap(cap), leakRate(leakRate), winMillis(winMillis){}

void LeakyBucketRateLimiter::leak() {
    int64_t nowMillis=clock.getUnixTimeMillis();
    int leakTokens = (int)(((nowMillis-curMillis)/(double)winMillis)*leakRate);
    
    if(leakTokens>0) {
        waterLevel=std::max(0, waterLevel-leakTokens);
        curMillis=nowMillis;
    }
}

bool LeakyBucketRateLimiter::IsAllowed() {
    // lazy leak
    //if(waterLevel==cap) leak();

    // should call leak at each requests to avoid bursty traffic
    leak(); 

    if(waterLevel<cap) {
        ++waterLevel;
        return true;
    }

    return false;
}

void Test_CornerCase2_LeakyBucket() {
    std::cout << "corner case 2: handle burst traffic" << std::endl;
    auto rl = std::make_unique<LeakyBucketRateLimiter>(5, 1, 500);
    for(int i=0; i<5; ++i) rl->IsAllowed();
    std::cout << (rl->IsAllowed() == false) << std::endl; 
    sleep(1);
    std::cout << (rl->IsAllowed() == true) << std::endl; 
    std::cout << (rl->IsAllowed() == true) << std::endl;
    std::cout << (rl->IsAllowed() == false) << std::endl;
    // bucket is full
    std::cout << (rl->IsAllowed() == false) << std::endl;
}

int main() {
  //Test_Normal_FixWin();
  //Test_CornerCase1_FixWin();
  //Test_CornerCase2_FixWin();
  
  //Test_Normal_SlidingWin();
  //Test_CornerCase1_SlidingWin();
  //Test_CornerCase2_SlidingWin();
  
  //Test_Normal_SlidingWinCounter();
  //Test_CornerCase1_SlidingWinCounter();
  //Test_CornerCase2_SlidingWinCounter();
  
  //Test_CornerCase2_TokenBucket();
  
  Test_CornerCase2_LeakyBucket();
  
  return 0;
}
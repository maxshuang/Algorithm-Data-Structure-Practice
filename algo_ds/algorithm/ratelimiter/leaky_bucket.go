package ratelimiter

import (
	"sync"
)

// leakyBucket is quite suitable for reshaping traffic and traffic control
// good for scenarios like sidecar replication

// Time Complexity: O(1), Space Complexity: O(1)
// Leaky bucket designs for reshaping traffic and traffic control, the rate range is [0, rate]

type LeakyBucket struct {
	mu         sync.Mutex
	rate       int // rate/s
	count      int
	cap        int
	delay      int64 // us/token
	lastFillUs int64
}

func NewLeakyBucket(rate int, cap int) *LeakyBucket {
	return &LeakyBucket{
		rate:       rate,
		count:      0,
		cap:        cap,
		delay:      int64(1000000 / rate),
		lastFillUs: getMicroSecond(),
	}
}

func (lb *LeakyBucket) Allow() bool {
	lb.mu.Lock()
	defer lb.mu.Unlock()

	if lb.count <= 0 {
		lb.Refill()
		if lb.count <= 0 {
			return false
		}
	}

	lb.count -= 1
	return true
}

func (lb *LeakyBucket) Refill() {
	nowUs := getMicroSecond()
	diff := nowUs - lb.lastFillUs
	if diff < 0 || diff < lb.delay {
		return
	}

	lb.count += int(diff / lb.delay)
	if lb.count > lb.cap {
		lb.count = lb.cap
	}
	lb.lastFillUs = nowUs
}

package ratelimiter

import (
	"sync"
)

// Time Complexity: O(1), Space Complexity: O(1)
// Token Bucket Algorithm allows burst traffic at [rate, cap]

type TokenBucket struct {
	mu         sync.Mutex
	rate       int // tokens/second
	count      int
	cap        int
	lastFillUs int64
}

func NewTokenBucket(rate int, cap int) *TokenBucket {
	return &TokenBucket{
		rate:       rate,
		count:      0,
		cap:        cap,
		lastFillUs: getMicroSecond(),
	}
}

func Min(a int, b int) int {
	if a <= b {
		return a
	}

	return b
}

func (tb *TokenBucket) Allow() bool {
	tb.mu.Lock()
	defer tb.mu.Unlock()

	// we only refill when there is no tokens
	if tb.count <= 0 {
		tb.Refill()
		if tb.count <= 0 {
			return false
		}
	}

	tb.count -= 1
	return true
}

func (tb *TokenBucket) Refill() {
	nowUs := getMicroSecond()
	diff := int(float64(nowUs-tb.lastFillUs) * float64(tb.rate) / 1000000)
	// we add this judgement because at high time resolution, updating lastUs directly may results in
	// no tokens at all because the float32 truncation to int
	if diff <= 0 {
		return
	}
	tb.count = Min(tb.cap, tb.count+diff)
	tb.lastFillUs = nowUs
}

package ratelimiter

type TokenBucket struct {
	rate   int // second
	lastUs int64
	count  int
}

func NewTokenBucket(rate int) *TokenBucket {
	return &TokenBucket{
		rate:   rate,
		lastUs: 0,
		count:  0,
	}
}

func (tb *TokenBucket) Request() bool {
	nowUs := getMicroSecond()
	tb.count += int(float32(nowUs-tb.lastUs) * float32(tb.rate) / 1000000)
	tb.lastUs = nowUs

	if tb.count == 0 {
		return false
	}

	tb.count--
	return true
}

package ratelimiter

// leakyBucket is quite suitable for reshaping traffic and traffic control
// good for scenarios like sidecar replication, or

type LeakyBucket struct {
	rate   int
	delay  float32 // us
	lastUs int64
}

func NewLeakyBucket(rate int) *LeakyBucket {
	return &LeakyBucket{
		rate:  rate,
		delay: float32(1000000 / rate),
	}
}

// hahaha
func (lb *LeakyBucket) Request() bool {
	nowUs := getMicroSecond()
	diff := nowUs - lb.lastUs
	lb.lastUs = nowUs
	return diff > lb.delay
}

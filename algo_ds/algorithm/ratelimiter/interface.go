package ratelimiter

import "time"

type RateLimiter interface {
	// Allow asks for a valid token
	Allow() bool
}

func getMilliSecond() int64 {
	// Get the current time
	now := time.Now()

	// Convert the current time to milliseconds since the Unix epoch
	return now.UnixNano() / int64(time.Millisecond)
}

func getMicroSecond() int64 {
	// Get the current time
	now := time.Now()

	// Convert the current time to milliseconds since the Unix epoch
	return now.UnixNano() / int64(time.Microsecond)
}

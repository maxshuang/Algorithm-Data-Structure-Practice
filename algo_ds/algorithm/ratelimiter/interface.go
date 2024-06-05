package ratelimiter

import "time"

type RateLimiter interface {
	// Request asks for a valid token
	Request() bool
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

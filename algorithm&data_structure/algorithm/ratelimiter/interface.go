type RateLimiter interface {
	// Request asks for a valid token
	Request() bool
}
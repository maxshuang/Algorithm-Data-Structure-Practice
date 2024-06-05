package ratelimiter

import (
	"testing"
	"time"

	"github.com/stretchr/testify/require"
)

func TestTokenBucket(t *testing.T) {
	tb := NewTokenBucket(1000) // 1000 tokens/s

	time.Sleep(1 * time.Second)
	for i := 0; i < 100; i++ {
		require.True(t, tb.Request())
	}
	require.False(t, tb.Request())

	time.Sleep(6 * time.Millisecond)
	for i := 0; i < 5; i++ {
		require.True(t, tb.Request())
	}
}

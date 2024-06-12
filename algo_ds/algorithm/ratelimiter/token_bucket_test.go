package ratelimiter

import (
	"testing"
	"time"

	"github.com/stretchr/testify/require"
)

func TestTokenBucket(t *testing.T) {
	tb := NewTokenBucket(1000, 100) // 1000 tokens/s

	time.Sleep(1 * time.Second)
	for i := 0; i < 100; i++ {
		require.True(t, tb.Allow())
	}
	require.False(t, tb.Allow())

	time.Sleep(6 * time.Millisecond)
	for i := 0; i < 5; i++ {
		require.True(t, tb.Allow())
	}
}

func TestTokenBucketAbnormal(t *testing.T) {
	tb := NewTokenBucket(100, 1000) // 100 tokens/s => 1 token/ 10ms

	for i := 0; i < 1000; i++ {
		time.Sleep(time.Millisecond)
		require.False(t, tb.Allow())
		time.Sleep(9 * time.Millisecond)
		require.True(t, tb.Allow())
	}
	require.False(t, tb.Allow())

	time.Sleep(60 * time.Millisecond)
	for i := 0; i < 5; i++ {
		require.True(t, tb.Allow())
	}
}

package ratelimiter

import (
	"testing"
	"time"

	"github.com/stretchr/testify/require"
)

func TestLeakyBucket(t *testing.T) {
	tb := NewLeakyBucket(100, 100) // 100 tokens/s => 10 ms/token

	time.Sleep(1 * time.Second)
	for i := 0; i < 100; i++ {
		require.True(t, tb.Allow())
	}
	require.False(t, tb.Allow())

	time.Sleep(10 * time.Millisecond)
	require.True(t, tb.Allow())
	for i := 0; i < 5; i++ {
		require.False(t, tb.Allow())
	}
}

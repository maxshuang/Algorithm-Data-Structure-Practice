package ratelimiter

import (
	"testing"
	"time"

	"github.com/stretchr/testify/require"
)

func TestFixWindowCounter(t *testing.T) {
	fwc := &FixWindowCounter{
		preMs:  0,
		count:  0,
		cap:    5,
		window: 500,
	}

	require.True(t, fwc.Request())
	time.Sleep(1 * time.Second)
	require.True(t, fwc.Request())
	time.Sleep(1 * time.Second)
	require.True(t, fwc.Request())
	time.Sleep(2 * time.Second)
	for i := 1; i < 6; i++ {
		require.True(t, fwc.Request())
	}
	require.False(t, fwc.Request())
	require.False(t, fwc.Request())
}

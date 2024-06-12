package ratelimiter

import (
	"testing"
	"time"

	queue "github.com/eapache/queue/v2"
	"github.com/stretchr/testify/require"
)

func TestSliceWindowCounter1(t *testing.T) {
	sw := &SliceWindowCounter1{
		que:    queue.New[int64](),
		window: 1000,
		cap:    5,
	}

	require.True(t, sw.Allow())
	time.Sleep(1 * time.Second)
	require.True(t, sw.Allow())
	time.Sleep(1 * time.Second)
	require.True(t, sw.Allow())
	time.Sleep(2 * time.Second)
	for i := 1; i < 6; i++ {
		require.True(t, sw.Allow())
	}
	require.False(t, sw.Allow())
	require.False(t, sw.Allow())
}

func TestSliceWindowCounter2(t *testing.T) {
	sw := &SliceWindowCounter2{
		que:      queue.New[Unit](),
		window:   1000,
		cap:      5,
		total:    0,
		granu:    10,
		curCount: 0,
		curMs:    getMilliSecond(),
	}

	require.True(t, sw.Allow())
	time.Sleep(1 * time.Second)
	require.True(t, sw.Allow())
	time.Sleep(1 * time.Second)
	require.True(t, sw.Allow())
	time.Sleep(2 * time.Second)
	for i := 1; i < 6; i++ {
		require.True(t, sw.Allow())
	}
	require.False(t, sw.Allow())
	require.False(t, sw.Allow())

	time.Sleep(1 * time.Second)
	for i := 1; i < 6; i++ {
		require.True(t, sw.Allow())
		time.Sleep(20 * time.Millisecond)
	}
	require.False(t, sw.Allow())
}

func TestSliceWindowCounter3(t *testing.T) {
	sw := New(1000, 10, 5)

	require.True(t, sw.Allow())
	require.True(t, sw.Allow())
	time.Sleep(1 * time.Second)
	require.True(t, sw.Allow())
	time.Sleep(2 * time.Second)
	for i := 1; i < 6; i++ {
		require.True(t, sw.Allow())
		time.Sleep(11 * time.Millisecond)
	}
	require.False(t, sw.Allow())
	time.Sleep(956 * time.Millisecond)
	require.True(t, sw.Allow())
	require.False(t, sw.Allow())
}

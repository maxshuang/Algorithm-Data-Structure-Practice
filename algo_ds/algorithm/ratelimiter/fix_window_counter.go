package ratelimiter

import (
	"time"
	"testing"
    "github.com/stretchr/testify/assert"
)

type FixWindowCounter struct {
	 curTs int64
	 count int
	 cap int
}

func (fw *FixWindowCounter) Request() bool {
	nowTs := time.Now().Unix()
	if nowTs != curTs {
		count=1
	}else if (count++) > cap {
		return true;
	}

	return false;
}

func TestFixWindowCounter(t *testing.T) {
	 fwc := &FixWindowCounter{
		curTs: 0,
		count: 0,
		cap: 5,
	 }

	 require.True(fwc.Request())
	 time.Sleep(1 * time.Second)
	 require.True(fwc.Request())
	 time.Sleep(1 * time.Second)
	 require.True(fwc.Request())
	 time.Sleep(2 * time.Second)
	 for i := 1; i < 6; i++ {
		require.True(fwc.Request())
     }
	 require.False(fwc.Request())
	 require.False(fwc.Request())
}
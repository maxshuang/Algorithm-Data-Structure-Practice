package ratelimiter

import (
	"time"
)

type FixWindowCounter struct {
	curTs int64
	count int
	cap   int
}

func (fw *FixWindowCounter) Request() bool {
	nowTs := time.Now().Unix()
	if nowTs != fw.curTs {
		fw.count = 1
		fw.curTs = nowTs
	} else {
		fw.count++
		if fw.count > fw.cap {
			return false
		}
	}

	return true
}

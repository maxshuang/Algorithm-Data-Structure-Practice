package ratelimiter

import "strconv"

// FixWindowCounter is a simple algorithm, but it can't handle the burst traffic at the edge of adjacent windows

type FixWindowCounter struct {
	preMs  int64
	count  int
	cap    int
	window int
}

func (fw *FixWindowCounter) Allow() bool {
	nowMs := getMilliSecond()
	diff := nowMs - fw.preMs
	if diff >= 0 && diff < int64(fw.window) {
		fw.count++
		if fw.count > fw.cap {
			return false
		}
	} else if diff >= int64(fw.window) {
		fw.count = 1
		fw.preMs = nowMs
	} else {
		panic("timestamp drawbacks: " + "nowMs:" + strconv.FormatInt(nowMs, 10) + ", preMs:" + strconv.FormatInt(fw.preMs, 10))
	}

	return true
}

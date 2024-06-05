package ratelimiter

import (
	"strconv"

	queue "github.com/eapache/queue/v2"
)

// SliceWindowCounter is more suitable for burst traffic and thus good for protecting the backend service
// The con of this algorithm is that it will drop the outbounded requests

type SliceWindowCounter1 struct {
	que    *queue.Queue[int64]
	window int
	cap    int
}

func (sw *SliceWindowCounter1) Request() bool {
	nowTs := getMilliSecond()
	sw.que.Add(nowTs)
	for sw.que.Length() > 0 {
		if nowTs-sw.que.Peek() > int64(sw.window) {
			sw.que.Remove()
		} else {
			break
		}
	}

	return sw.que.Length() <= sw.cap
}

type Unit struct {
	Ms    int64
	Count int
}

type SliceWindowCounter2 struct {
	que      *queue.Queue[Unit]
	window   int
	cap      int
	total    int
	granu    int
	curCount int
	curMs    int64
}

func (sw *SliceWindowCounter2) Request() bool {
	nowMs := getMilliSecond()
	diff := nowMs - sw.curMs

	if diff >= 0 && diff < int64(sw.granu) {
		sw.curCount++
		sw.total++
	} else if diff >= int64(sw.granu) {
		sw.que.Add(Unit{sw.curMs, sw.curCount})
		sw.curCount = 1
		sw.curMs = nowMs
		sw.total++
	} else {
		panic("timestamp drawbacks: " + "nowMs:" + strconv.FormatInt(nowMs, 10) + ", preMs:" + strconv.FormatInt(sw.curMs, 10))
	}

	for sw.que.Length() > 0 {
		un := sw.que.Peek()
		if nowMs-un.Ms > int64(sw.window) {
			sw.que.Remove()
			sw.total -= un.Count
		} else {
			break
		}
	}

	return sw.total <= sw.cap
}

// array version
type SliceWindowCounter3 struct {
	window int
	granu  int
	cap    int
	total  int
	slots  []Unit // need maintain the exact ms in the slot to distinguish different round
}

func New(win int, granu int, cap int) *SliceWindowCounter3 {
	return &SliceWindowCounter3{
		window: win,
		granu:  granu,
		cap:    cap,
		total:  0,
		slots:  make([]Unit, (win+granu-1)/granu),
	}
}

func (sw *SliceWindowCounter3) Request() bool {
	nowMs := getMilliSecond()
	idx := int(nowMs % int64(sw.granu))
	if nowMs == sw.slots[idx].Ms {
		sw.slots[idx].Count++
	} else {
		sw.slots[idx].Count = 1
		sw.slots[idx].Ms = nowMs
	}
	total := sw.slots[idx].Count

	end := idx
	idx = (idx + 1) % len(sw.slots)
	for idx != end {
		if nowMs-sw.slots[idx].Ms < int64(sw.window) {
			total += sw.slots[idx].Count
		}
		idx = (idx + 1) % len(sw.slots)
	}

	if total < sw.cap {
		return true
	}

	return false
}

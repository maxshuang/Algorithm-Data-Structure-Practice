#include <iostream>

// Solution:
// 1. keep the <key, frequency>: map, hash map
// 2. find the smallest frequency, sorted or heap structure, map<frequency, key>
// 3. remove the lru item with smallest frequency, map<frequency, LRU*>

class LFU {
public:
    LFU(int cap);
    ~LFU();
    int get(int key);
    void set(int key, int val);
private:
};




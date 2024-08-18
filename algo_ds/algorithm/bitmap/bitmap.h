#pragma once
#include <cmath>
// bit manipulation 有小规模的算法技巧和大规模的优化设计
// 比如 redis 中的 bitcount 和 bitpos 操作就被优化到了极致


inline int bitmap_set(int *bitmap, int index) {
    int i = index / 32;
    int j = index % 32;
    bitmap[i] |= (1 << j);
    return 0;
}

// O(K) time complexity, K is the number of 1 in bitmaps
inline int bitmap_count(int *bitmap, int count) {
    int bc=0;
    for(int i=0; i<count; ++i) {
        int b=bitmap[i];
        while(b!=0) {
            ++bc;
            // interesting trick to count the number of 1 in the bitmap
            // image b=0x1100, b-1=0x1011, b&=(b-1)=0x1000
            b&=(b-1);
        }
    }
    return bc;
}

inline int bitmap_get(int *bitmap, int index) {
    int i = index / 32;
    int j = index % 32;
    return (bitmap[i] & (1 << j)) != 0;
}

inline int bitmap_clear(int *bitmap, int index) {
    int i = index / 32;
    int j = index % 32;
    bitmap[i] &= ~(1 << j);
    return 0;
}

// find out the first position of 1 in the bitmap
// O(N) time complexity, N is the number of bitmap array
inline int bitmap_pos(int *bitmap, int bl) {
    for(int i=0; i<bl; ++i) {
        if(bitmap[i]!=0) {
            // we can use __builtin_ffs(single instruction) to find the first bit set
            // for better performance
            // the return value is 1-based, so we need to minus 1
            // int bit_pos = __builtin_ffs(bitmap[i]);
            // return i*32+bit_pos-1;
            for(int j=0; j<32; ++j) {
                if(bitmap[i] & (1<<j)) {
                    return i*32+j;
                }
            }
        }
    }
    return -1;
}

// O(1) time complexity, check if it has only one 1
inline bool bitmap_isPowerOfTwo(int x) {
    return (x && !(x&(x-1)));
} 

/*
Finding the largest power of 2 (most significant bit, or MSB) of a number can be useful in several scenarios in computer science and programming:

Binary Search: If you're implementing a binary search or a similar algorithm that repeatedly divides the problem size by 2, you might need to find the largest power of 2 less than or equal to a given number to determine the initial problem size.

Bit Manipulation: In bit manipulation tasks, finding the MSB can be useful. For example, in graphics programming, you might need to find the highest set bit in a color value to normalize it.

Memory Allocation: In systems programming, especially when dealing with memory allocation, it's often necessary to allocate memory in chunks that are powers of 2. In such cases, finding the largest power of 2 less than or equal to a given number can help determine the appropriate chunk size.

Networking: In networking, particularly in routing, the largest power of 2 less than or equal to a given number is used to determine the network mask for IP addresses.

Data Structures: Certain data structures like binary indexed trees (also known as Fenwick trees) and segment trees often require finding the largest power of 2 less than or equal to a given number.
*/
// O(K) time compelxity, K is the number of 1 in the bitmap
// find the largest msb that is less than or equal to N
inline int bitmap_msb(int N) {
    int b=N;
    int msb=0;
    // 这个比较好理解，本质上是数 1
    while(b) {
        msb=b;
        b&=(b-1);
    }
    return msb;
}

inline int bitmap_msb2(int M) {
    int N=M;
    N = N| (N>>1);
    N = N| (N>>2);
    N = N| (N>>4);
    N = N| (N>>8);
    N = N| (N>>16);

    return N-(N>>1);
}

// find the least significant bit number
inline int bitmap_lsb(int N) {
    // 这个利用地位清 0 + 异或
    return N^(N&(N-1));
}

// find the least significant bit number
inline int bitmap_lsb2(int N) {
    // -N is the two's complement of N
    return N&(-N);
}

int lsbPosition(int n) {
    // If number is zero, return error
    if (n == 0) {
        return -1;
    }

    // log2(n & -n) gives the position of the LSB
    int lsbP = log2(n & -n);

    // increment by 1 to get the position
    return lsbP + 1;
}

int msbPosition(int n) {
    // log2(n) = log(n) / log(2)
    int msbP = log2(n);

    // increment by 1 to get the position
    return msbP + 1;
}
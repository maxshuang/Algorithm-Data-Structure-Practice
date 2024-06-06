#include <vector>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// two operations:
// 1. add, l, r, x
// 2. sum, l, r

enum Type {
    ADD,
    SUM,
};

struct Op {
    Type tp;
    int l;
    int r;
    int x;
};

int blockSize=0;
int blockCount=0;
std::vector<int> blockSum;  // for range sum
std::vector<int> lazyTag;   // for range add/sub

void add(std::vector<int>& array, const Op& op);
int sum(std::vector<int>& array, const Op& op);

std::vector<int> Calculate(std::vector<int>& array, const std::vector<Op>& ops) {
    // block decomposite the array
    int arrSize=array.size();
    blockSize=std::sqrt(arrSize);
    blockCount=(arrSize+blockSize-1)/blockSize;
    blockSum.resize(blockCount, 0);
    lazyTag.resize(blockCount, 0);
    for(int i=0; i<blockCount; ++i) {
        int start=blockSize*i;
        int end=std::min(blockSize, arrSize-start);
        for(int j=0; j<end; ++j) {
            blockSum[i]+=array[start+j];
        }
    }

    // do the operations
    std::vector<int> res;
    for(size_t i=0; i<ops.size(); ++i) {
        switch(ops[i].tp) {
            case ADD:
                add(array, ops[i]);
                break;
            case SUM:
                res.push_back(sum(array, ops[i]));
                break;
        }
    }

    return res;
}

// for Add:
// 1. cover the whole block, add the op.x*blockSize to the sum
// 2. cover only a part of block, do the range add
void add(std::vector<int>& array, const Op& op) {
    int lb=op.l/blockSize, rb=op.r/blockSize;

    // inside a single block
    if(lb==rb) {
        for(int i=op.l; i<=op.r; ++i) {
            array[i]+=op.x;
        }
        blockSum[lb]+= (op.r-op.l+1)*op.x;
        return;
    }

    // [l, (lb+1)*blockSize) 
    for(int i=op.l; i<(lb+1)*blockSize; ++i) {
        array[i]+=op.x;
    }
    blockSum[lb]+=((lb+1)*blockSize-op.l)*op.x;
    
    // [(lb+1)*blockSize, rb*blockSize)
    for(int i=lb+1; i<rb; ++i) {
        blockSum[i]+=blockSize*op.x;
        lazyTag[i]+=op.x;
    }

    // [rb*blockSize, op.r]
    for(int i=rb*blockSize; i<=op.r; ++i) {
        array[i]+=op.x;
    }
    blockSum[rb]+=(op.r-rb*blockSize+1)*op.x;
}

// for Sum:
// 1. cover the whole block, add block sum to total
// 2. cover a part of block, do the range sum
int sum(std::vector<int>& array, const Op& op) {
    // NOTE: can use static table to accelerate the query
    int lb=op.l/blockSize, rb=op.r/blockSize;
    int total=0;

    // inside a single block
    if(lb==rb) {    
        for(int i=op.l; i<=op.r; ++i) {
            total+=array[i];
        }
        total += lazyTag[lb]*(op.r-op.l+1);
        return total;
    }

    // [l, (lb+1)*blockSize) 
    for(int i=op.l; i<(lb+1)*blockSize; ++i) {
        total+=array[i];
    }
    total += lazyTag[lb]*((lb+1)*blockSize-op.l);
    
    // [(lb+1)*blockSize, rb*blockSize)
    for(int i=lb+1; i<rb; ++i) {
        total+=blockSum[i];
    }

    // [rb*blockSize, op.r]
    for(int i=rb*blockSize; i<=op.r; ++i) {
       total+=array[i];
    }
    total += lazyTag[rb]*(op.r-rb*blockSize+1);

    return total;
}

TEST_CASE("Test block composition", "")
{
    std::vector<int> array{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<Op> ops{{Type::SUM, 1, 4, 0}, {Type::ADD, 2, 7, 10},
         {Type::ADD, 3, 4, 3}, {Type::SUM, 5, 9, 0}, {Type::SUM, 0, 9, 0}};
    std::vector<int> res = Calculate(array, ops);
    REQUIRE(res==std::vector<int>{10, 65, 111});
}
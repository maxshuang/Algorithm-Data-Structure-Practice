#include <iostream>
#include <cmath>
#include <algorithm>
#include <string.h>

#define kMaxSize 1007

int data[kMaxSize*kMaxSize];
int data_backup[kMaxSize*kMaxSize];
int tag[kMaxSize];
int b_size=0;
int b_num=0;
int N=0, Q=0;

int id(int i) { return (i-1)/b_size+1; }
int first(int i) { return (i-1)*b_size+1; }
int last(int i) { 
    if(i==b_num) return N;
    return i*b_size; 
}

void sort(int g) {
    // sort will break the original sequence, so
    // we copy to backup
    int l=first(g), r=last(g);
    for(int i=l; i<=r; ++i) data_backup[i]=data[i];
    std::sort(data_backup+l, data_backup+r+1);
}

void operate(int l, int r, int w) {
    int sg=id(l), eg=id(r);
    if(sg==eg) {
        for(int i=l; i<=r; ++i) data[i]+=w;
        sort(sg);
        return;
    }
    
    int lst=last(sg);
    for(int i=l; i<=lst; ++i) data[i]+=w;
    sort(sg);
    for(int i=sg+1; i<eg; ++i) tag[i]+=w;
    int fst=first(eg);
    for(int i=fst; i<=r; ++i) data[i]+=w;
    sort(eg);
}

int query(int l, int r, int c) {
    int sg=id(l), eg=id(r);
    int sum=0;
    
    if(sg==eg) {
        // we can't use binary search here because the data_backup doesn't know the 
        // original sequence
        for(int i=l; i<=r; ++i) { if(data[i]+tag[sg]>=c) ++sum; }
        return sum;      
    }

    int lst=last(sg);
    for(int i=l; i<=lst; ++i) { if(data[i]+tag[sg]>=c) ++sum; }
    for(int i=sg+1; i<eg; ++i) {
        //[NOTE]: need use data_backup here
        sum+=(data_backup+last(i)+1-std::lower_bound(data_backup+first(i), data_backup+last(i)+1, c-tag[i]));
    }
    int fst=first(eg);
    for(int i=fst; i<=r; ++i) { if(data[i]+tag[eg]>=c) ++sum; }
    return sum;
}

int main() {
    memset(data, 0, sizeof(data));
    memset(tag, 0, sizeof(tag));
    std::cin >> N >> Q;
    b_size=std::sqrt(N);
    b_num=(N+b_size-1)/b_size; // round up
    for(int i=1; i<=N; ++i) {
        std::cin >> data[i];
    }
    for(int i=1; i<=b_num; ++i) {
        sort(i);
    }
    while(Q) {
        char op;
        int L, R, C;
        std::cin >> op >> L >> R >> C;
        if(op=='M') {
            operate(L, R, C);
        }else if(op=='A') {
            std::cout << query(L, R, C) << std::endl;
        }
        --Q;
    }
    return 0;
}
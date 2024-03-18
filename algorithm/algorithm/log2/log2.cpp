#include <cmath>
#include <bits/stdc++.h>

// O(logN)
int log2_Olg(int x) {
    if(x==0) return -1;
    int cnt=-1;
    while(x) {
        x>>=1;
        cnt++;    
    }
    return cnt;
}

// O(loglogN)
int log2_Olglg(int x) {
    if(x==0) return -1;
    int l=1, r=sizeof(x)*8;
    while(l<=r) {
        int m=(l+r)>>1;
        if(x>>m) l=m+1;
        else r=m-1;                    
    }
    
    return l-1;
}

// O(1)
int log2_O1(int x) {
    if(x==0) return -1;
    return std::__lg(x);
}

// time complexity ?? eps precision
int log2(int x) {
    if(x==0) return -1;
    // std::log2(float/double)
    return std::log2(x);
}

// O(loglogN)
int log2_fun2(int n) {  
  if(n==0) return -1;
  int result = 0;  
  if(n&0xffff0000) {result += 16; n >>= 16; }  
  if(n&0x0000ff00) {result += 8; n >>= 8; }  
  if(n&0x000000f0) {result += 4; n >>= 4; }  
  if(n&0x0000000c) {result += 2; n >>= 2; }  
  if(n&0x00000002) {result += 1; n >>= 1; }  
  return result; 
}

int log2_binary(int x) {
    if(x==0) return -1;
    double x1 = x;
    double eps=1e-5;
    double l=0, r=sizeof(x)*8;
    while(l+eps<r) {
        double m=(l+r)/2;
        if(std::pow(2, m)<=x1) l=m;
        else r=m;                    
    }

    return (int)l;
}

// 0-based index
int lsb(int n) {
    if (n == 0) return -1;
    return __builtin_ctz(n);
}

// 0-based index, O(logN)
int lsb2(int n) {
    if (n == 0) return -1;
    int cnt=0;
    while((n&1)==0) {
        n>>=1;
        cnt++;
    }
    
    return cnt;
}

// 0-based index, O(loglogN)
int lsb3(int n) {
    if (n == 0) return -1;
    
    int result = 0;  
    if(!(n&0x0000ffff)) {result += 16; n >>= 16; }  
    if(!(n&0x000000ff)) {result += 8; n >>= 8; }  
    if(!(n&0x0000000f)) {result += 4; n >>= 4; }  
    if(!(n&0x00000003)) {result += 2; n >>= 2; }  
    if(!(n&0x00000001)) {result += 1; n >>= 1; }  
    
    return result; 
}
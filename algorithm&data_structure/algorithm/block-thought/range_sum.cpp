#include <cmath>
#include <iostream>
#include <vector>
#include <string.h>

#define kMaxSize 300

long long data[kMaxSize*kMaxSize];
long long tag[kMaxSize];
long long sum[kMaxSize];

int op, l, r, c;
int N;
int kSize;

inline int id(int i) {
    return (i-1)/kSize+1;
}

inline int first(int g) {
    return (g-1)*kSize+1;
}

inline int last(int g) {
    return g*kSize;
}

void add(int l, int r, int c)
{
    int sg=id(l), eg=id(r);
    if(sg==eg) {
        // brute
        for(int i=l; i<=r; ++i) data[i]+=c;
        sum[sg]+=c*(r-l+1);
        return;
    }

    int lst=last(sg);
    for(int i=l; i<=lst; ++i) data[i]+=c;
    sum[sg]+=c*(lst-l+1);
    for(int i=sg+1; i<=eg-1; ++i) {
        tag[i]+=c;
        sum[i]+=c*kSize;
    }
    int fst=first(eg);
    for(int i=fst; i<=r; ++i) data[i]+=c;
    sum[eg]+=c*(r-fst+1);
}

long long output(int l, int r, int c)
{
    long long sum1=0;
    int sg=id(l), eg=id(r);
    if(sg==eg) {
        // brute
        for(int i=l; i<=r; ++i) sum1=(sum1+tag[sg]+data[i])%c;
        return sum1;
    }

    int lst=last(sg);
    for(int i=l; i<=lst; ++i) sum1=(sum1+tag[sg]+data[i])%c;
    for(int i=sg+1; i<eg; ++i) sum1=(sum1+sum[i])%c;
    int fst=first(eg);
    for(int i=fst; i<=r; ++i) sum1=(sum1+tag[eg]+data[i])%c;

    return sum1;
}

int main()
{
    memset(data, 0, sizeof(data));
    memset(tag, 0, sizeof(tag));
    memset(sum, 0, sizeof(sum));
    //freopen("/home/maxshuang/Downloads/a2.in", "r", stdin);
    std::cin >> N;
    kSize=std::sqrt(N);
    for (int i = 1; i <= N; ++i) {
        // [NOTE]: make sure to initize the sum here
        std::cin >> data[i];
        sum[id(i)]+=data[i];
    }

    int M=N;
    while (M)
    {
        std::cin >> op >> l >> r >> c;
        if (op == 0)
            add(l, r, c);
        else
            std::cout << output(l, r, c+1) << std::endl;
        --M;
    }
    return 0;
}
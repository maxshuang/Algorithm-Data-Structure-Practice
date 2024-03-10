#include <iostream>
#include <vector>

int tree[1000001];

long long getTimber(int n, int cut) {
    long long total=0;
    for(int i=0; i<n; ++i) {
        if(tree[i]>cut) total+=(tree[i]-cut);
    }
    return total;
}

int main(){
    int N, M;
    std::cin >> N >> M;
    std::cout << N << " " << M << std::endl;
    for(int i=0; i<N; ++i) {
        std::cin >> tree[i];
    }

    int lf=400001;
    int rt=1;
    // getTimber[lf, rt] is a non-decreasing sequence
    // find the lower bound
    while(lf>=rt) {
        int mid=rt+((lf-rt)>>1);
        // take care that the [lf, rt] is in decreasing order
        if(getTimber(N, mid)>=(long long)M) rt=mid+1;
        else lf=mid-1;
    }

    std::cout << lf;
    return 0;
}
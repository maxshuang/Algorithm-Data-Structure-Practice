#include <iostream>
#include <cmath>

double coeffic[14];
int N;
double l, r;
double eps=1e-5;

double ff(double x) {
    double res=0.0;
    for(int i=0; i<N+1; ++i)
        res+=coeffic[i]*std::pow(x, N-i);

    return res;
}


int main() {
    std::cin >> N >> l >> r;
    for(int i=0; i<N+1; ++i) {
        std::cin >> coeffic[i];
    }

    while(r-l>eps) {
        double mid=l+(r-l)/2;
        if(ff(mid-eps)<ff(mid+eps)) l=mid;
        else r=mid;
    }

    std::cout << l;
    
    return 0;
}
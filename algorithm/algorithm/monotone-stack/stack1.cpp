#include <iostream>
#include <string.h>

#define kMaxSize 1000005

int heights[kMaxSize];
int energies[kMaxSize];
int sums[kMaxSize];
int N=0;

void walk(int i) {
    // walk right
    for(int j=i+1; j<=N; ++j) {
        if(heights[j]>heights[i]) {
            sums[j]+=energies[i];
            break;
        }
    }

    // walk left
    for(int j=i-1; j>=1; --j) {
        if(heights[j]>heights[i]) {
            sums[j]+=energies[i];
            break;
        }
    }
}

int main() {
    memset(heights, 0, sizeof(heights));
    memset(energies, 0, sizeof(energies));
    memset(sums, 0, sizeof(sums));
    
    std::cin >> N;
    for(int i=1; i<=N; ++i) {
        std::cin >> heights[i] >> energies[i];
    }

    for(int i=1; i<=N; ++i) {
        walk(i);
    }
    
    int max=0;
    for(int i=1; i<=N; ++i) {
        if(sums[i]>max) max=sums[i];
    }
    
    std::cout << max << std::endl;
}
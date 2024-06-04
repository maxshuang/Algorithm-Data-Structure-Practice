#include "common.h"

// selection sort is a not stable algorithm because of the exchange operation

// Time Complexity: O-(N^2/2) for comparison, O(N) for exchange, know both the upper bound and lower bound
// Space Complexity: O(1)
// Data Movement: O(N), read more than write(GOOD!!!)
// Can't use any information at each round

void selection_sort(int* vec, int num) {
    // Don't need to deal with the last round
    for(int i=0; i<num-1; ++i) {
        int min=i;
        for(int j=i+1; j<num; ++j) {
            if(vec[j]<vec[min]) {
                min=j;
            }
        }
        if(i!=min) {
            exchange(vec, i, min);
        }
    }
}
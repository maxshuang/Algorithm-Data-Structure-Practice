#include "common.h"

// selection sort is a not stable algorithm, the exchange operation may reverse the 
// original sequence of the same values 

// Time Complexity: O-(N^2/2) for comparison, O(N) for exchange, know both the upper bound and lower bound
// Space Complexity: O(1)
// Data Movement: O(N), read more than write(GOOD!!!)
// Can't use any information at each round

void selection_sort(int* vec, int c) {
    for(int i=0; i<c; ++i) {
        int min=i;
        for(int j=i+1; j<c; ++j) {
            if(vec[j]<vec[min]) {
                min=j;
            }
        }
        if(i!=min) {
            exchange(vec, i, min);
        }
    }
}
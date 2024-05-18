#include "counting_sort.h"

// Counting sort algorithm is a stable algorithm
// Used in the situation when the value range is small and limited
// Time Complexity: O(N+K) compares and exchanges
// Space Complexity: O(N+K) auxiliary space
//
// bucket sort is a bit like counting sort, but it's used when the value range is large but even distributed
// in the bucket sort, element only has a rough position, sequence between buckets is sorted, but the elements in the bucket are not sorted

void counting_sort(int *vec, int num, int maxN)
{
    // [NOTE]: built-in types will not be initialized if not specified any value
    int *auxiliary = new int[num]{0};
    int *count = new int[maxN + 1]{0};

    // calculate the frequency of each element
    for (int i = 0; i < num; ++i)
        count[vec[i]]++;
    // calculate the cumulative frequency
    for (int i = 0; i < maxN; ++i)
        count[i + 1] += count[i];
    // backward assignment to keep the stability
    for (int i = num - 1; i >= 0; --i)
        auxiliary[--count[vec[i]]] = vec[i];

    delete[] auxiliary;
    delete[] count;
}
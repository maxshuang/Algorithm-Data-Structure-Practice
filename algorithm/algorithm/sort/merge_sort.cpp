#include <stdlib.h>
#include "common.h"
#include "merge_sort.h"
#include "insertion_sort.h"

// Merge sort is a divide and conquer algorithm
// Later rounds can make use of the partially ordered data from the previous rounds
// It's a stable algorithm
//
// Time Complexity: O(1.39NlogN) compares and O(NlogN) exchanges
// Space Complexity: O(N) auxiliary space
// optimization1: check if subarrays are already ordered before merge
// optimization2: use in-place insertion-sort for small subarrays
// optimization3: flip the usage of vec to reduce the copy between vec and nvec
// optimization4: three-way merge sort ??

void merge_sort(int *vec, int num)
{
    int *nvec = (int *)malloc(num * sizeof(int));
    sort(vec, 0, num, nvec);
    free((void *)nvec);
}

void sort(int *vec, int l, int r, int *nvec)
{
    // single or none
    if (r <= l + 1)
        return;

    int m = l + (r - l) / 2;
    sort(vec, l, m, nvec);
    sort(vec, m, r, nvec);

    // optimization1: check if already ordered
    if(vec[m-1] > vec[m])
        merge(vec, l, m, r, nvec);
}

// optimization2: use in-place insertion-sort for small subarrays
void sort2(int *vec, int l, int r, int *nvec)
{
    // single or none
    if (r-l<=64)
        return insertion_sort_range(vec, l, r);

    int m = l + (r - l) / 2;
    sort(vec, l, m, nvec);
    sort(vec, m, r, nvec);

    // optimization1: check if already ordered
    if(vec[m-1] > vec[m])
        merge(vec, l, m, r, nvec);
}

void merge(int *vec, int l, int m, int r, int *nvec)
{
    int i = l;
    int j = m;
    int k = l;
    while (i < m && j < r)
    {
        if (vec[i] < vec[j])
            nvec[k++] = vec[i++];
        else
            nvec[k++] = vec[j++];
    }
    while (i < m)
        nvec[k++] = vec[i++];
    while (j < r)
        nvec[k++] = vec[j++];

    // copy back
    for (int p = l; p < r; ++p)
        vec[p] = nvec[p];

    //print(vec, l, r);
}

void merge_compact(int *vec, int l, int m, int r, int *nvec)
{
    int i = l;
    int j = m;
    for(int k = l; k < r; ++k)
    {
        if (i >= m)
            nvec[k] = vec[j++];
        else if (j >= r)
            nvec[k] = vec[i++];
        else if (vec[i] < vec[j])
            nvec[k] = vec[i++];
        else
            nvec[k] = vec[j++];
    }

    // copy back
    for (int p = l; p < r; ++p)
        vec[p] = nvec[p];
}

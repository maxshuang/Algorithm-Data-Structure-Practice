#include "quick_sort.h"
#include "insertion_sort.h"
#include "common.h"

// quick sort is a divide and conquer algorithm
// It's not a stable algorithm
// Time Complexity: O(1.39NlogN) compares and O(NlogN) exchanges, worst case is O(N^2), so normally a better option is randomized quick sort
// less data movement than merge sort
// [NOTE]: So hard to write a correct quick sort, keeping the invariant is the key
//
//
// optimization1: using insertion sort when the size of the array is small
// optimization2: using median value as pivot
// optimization3: three-way quick sort for too many duplicate keys
// optimization4: randomize the array to avoid the worst case

void quick_sort(int *vec, int num)
{
    return quick_sort_range(vec, 0, num - 1);
}

void quick_sort_range(int *vec, int l, int r)
{
    if (l >= r)
        return;
    int m = partition_compact(vec, l, r);
    quick_sort_range(vec, l, m - 1);
    quick_sort_range(vec, m + 1, r);

    // print(vec, l, r);
}

// optimization1: using insertion sort when the size of the array is small
void quick_sort_range2(int *vec, int l, int r)
{
    if (r - l <= 64)
        return insertion_sort_range(vec, l, r);
    int m = partition_compact(vec, l, r);
    quick_sort_range(vec, l, m - 1);
    quick_sort_range(vec, m + 1, r);

    // print(vec, l, r);
}

int partition_wrong(int *vec, int l, int r)
{
    int pivot = pivot_func(vec, l, r);
    int i = l, j = r;
    while (i < j)
    {
        while (vec[i] <= pivot && i <= j)
            i++;
        while (vec[j] > pivot && j >= i)
            j--;
        if (i < j)
        {
            exchange(vec, i, j);
            i++;
            j--;
        }
    }

    // three conditions: i==j, i=r+1, j=l-1
    // what if happens: i=r+1, j=l-1 ???
    return i;
}

// This implement is hard to understand because keeping no invariant during the while process
int partition_wrong2(int *vec, int l, int r)
{
    int pivot = pivot_func2(vec, l, r);
    int i = l, j = r;
    while (i < j)
    {
        // std::cout << "i:" << i << ",j:" << j << std::endl;
        //  same value would exachange their positions here
        while (vec[i] < pivot && i <= r)
            i++;
        while (vec[j] > pivot && j >= l)
            j--;
        if (i >= j)
            break;

        exchange(vec, i++, j--);
    }

    // wrong: may be ...j,i...
    // two conditions: i==j, or i==j+1
    // problem here, don't know where is the pivot ???
    return i;
}

int partition_wrong3(int *vec, int l, int r)
{
    int pivot = pivot_func(vec, l, r);
    int i = l+1, j = r;
    while (i < j)
    {
        // std::cout << "i:" << i << ",j:" << j << std::endl;
        // same value would exachange their positions here
        while (vec[i] < pivot && i <= r)
            i++;
        while (vec[j] > pivot && j >= l)
            j--;
        if (i >= j)
            break;

        exchange(vec, i++, j--);
    }

    // wrong: may be ...j,i...
    // two conditions: i==j, or i==j+1
    // when i+1==j, because there is no guarantee that vec[j] <= pivot, so here is the bug for example [1, 2, 3, 4, 5] 
    exchange(vec, l, j);
    return j;
}

int partition_compact(int *vec, int l, int r)
{
    // keep the invariant: vec[l..i] <= pivot, vec[j..r] >= pivot
    int pivot = vec[l];
    int i = l, j = r + 1;
    while (true)
    {
        // std::cout << "i:" << i << ",j:" << j << std::endl;
        //  same value would exachange their positions here
        while (vec[++i] < pivot)
            if (i == r)
                break;
        while (vec[--j] > pivot)
            if (j == l)
                break;
        if (i >= j)
            break;
        exchange(vec, i, j);
    }

    // two conditions: i==j, or i==j+1
    // before we skip the pivot, we need to set pivot to its proper position
    exchange(vec, l, j);
    return j;
}

int pivot_func(int *vec, int l, int r)
{
    return vec[l];
}

// choose a median value as pivot
int pivot_func2(int *vec, int l, int r)
{
    if (r - l >= 2)
    {
        // find the median
        int m = l + (r - l) / 2;
        int p=find_median(vec, l, m, r);
        exchange(vec, l, p);
    }

    return vec[l];
}

int find_median(int* vec, int l, int m, int r)
{
    if (vec[l] < vec[m])
    {
        if (vec[m] < vec[r])
            return m;
        else if (vec[l] < vec[r])
            return r;
    }
    else
    {
        if (vec[r] < vec[m])
            return m;
        else if(vec[r] < vec[l])
            return r;
    }
    return l;
}

// Quick 3-way sort is a variant of quick sort that is much faster for arrays with large numbers of duplicate keys
// It's not a stable algorithm

void quick_3way(int *vec, int num)
{
    quick_3way_range(vec, 0, num - 1);
}

void quick_3way_range(int *vec, int l, int r)
{
    if (l >= r)
        return;

    int pivot = vec[l];
    // keep the invariant: vec[l..lt] < pivot, vec[lt+1..i-1] == pivot, vec[gt..r] > pivot
    int lt = l - 1; // less than boundary
    int gt = r + 1; // greater than boundary
    int i = l;
    while (i < gt)
    {
        if (vec[i] == pivot)
            ++i; // expand the range of pivot
        else if (vec[i] < pivot)
            exchange(vec, ++lt, i++); // expand the range of less than, since vec[lt+1]==pivot, we need to skip it
        else
            exchange(vec, --gt, i); // expand the range of greater than, since vec[gt-1]!=pivot, we need to recheck it
    }

    quick_3way_range(vec, l, lt);
    quick_3way_range(vec, gt, r);
}
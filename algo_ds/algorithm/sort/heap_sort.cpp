#include "heap_sort.h"
#include "common.h"

// heap sort is kind of algorithm benefited from the partial order of the array
// Not stable, the sequence will be reversed when sorting
// Time complexity: O(nlogn), worst case: O(nlogn), best case: O(nlogn)
// Space complexity: O(1)
// Time complexity for the heap: O(logN) for insert, O(logN) for delete
// The heap sort is not good for small arrays, because the heapify process is too slow
// It can't utilize the original order of the array

// optimization1: use the original array to store the heap, so no need to copy the array
// optimization2: multi-way heap
// optimization3: use insertion sort for small arrays
// Immutability of the keys
// Index priority Queue

void float_up(int *vec, int num, int p)
{
    if (p == 0)
        return;

    while (p != 0)
    {
        int pp = p / 2; // for the left child
        if ((p & 1) == 0)
            pp--; // for the right child

        if (vec[p] <= vec[pp])
            break;

        exchange(vec, pp, p);
        p = pp;
    }
}

void sink_down(int *vec, int num, int q)
{
    int lc = 2 * q + 1;
    while (lc < num)
    {
        if (lc < num - 1 && vec[lc] < vec[lc + 1])
            lc++;
        if(vec[lc] <= vec[q])
            break;
        exchange(vec, q, lc);
        lc=2*lc+1;
    }
}

void make_max_heap(int *vec, int num)
{
    if (num <= 1)
        return;
    int non_leaf_pos = num / 2 - 1;
    for (int i = non_leaf_pos; i >= 0; i--)
    {
        sink_down(vec, num, i);
    }
}

void heap_sort(int *vec, int num)
{
    make_max_heap(vec, num);
    for (int i = num - 1; i > 0; --i)
    {
        exchange(vec, 0, i);
        sink_down(vec, i, 0);
    }
}
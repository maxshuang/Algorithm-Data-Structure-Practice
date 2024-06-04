#include <algorithm>
#include <cstring>
#include "common.h"
#include "insertion_sort.h"

// insertion_sort is like sort hand cards.
// it's a stable algorithm only if the comparison doesn't contain equal sign
// Time Complexity: O-(N^2/4) for average compares, O-(N^2/4) for average exchange. Worst Case is O-(N^2/2) for compares, O-(N^2/2) for exchanges
// Space Complexity: O(1)
// Data Movement: O-(N^2), too much read and write
// Can use the initial order of items in the input, GOOD if the original items are nearly in order (much, much faster)

// optimization1: use binary search to find the position to insert(upper_bound to remain the original order)

// This is not an implement of insertion sort, but a implement of selection sort !!!!
void insertion_sort(int *vec, int num)
{
    // no need for the first round
    for (int i = 0; i < num; i++)
    {
        int min_pos = i;
        // find the smallest one
        for (int j = i + 1; j < num; j++)
        {
            if (vec[j] < vec[min_pos])
            {
                min_pos = j;
            }
        }

        if (i != min_pos)
        {
            int smallest = vec[min_pos];
            // backward the elements for [i, min-1] untill the vacated position.
            for (int j = min_pos - 1; j >= i; j--)
            {
                vec[j + 1] = vec[j];
            }
            vec[i] = smallest;
        }

        // print(vec, num);
    }
}

// select a card and put it in a right position
void insertion_sort_compact(int *vec, int num)
{
    // keep the invariant: vec[0, i] is ordered
    for (int i = 1; i < num; i++)
    {
        // this implement is a bit like bubble sort, but it needs to bubble to the right position directly at each round
        // 2x write than the first implement
        // very easy to make mistake here
        int key = vec[i];
        int j = i - 1;
        for (; j >= 0 && key < vec[j]; j--)
        {
            vec[j+1] = vec[j];
        }
        vec[j+1] = key;
    }
}

void insertion_sort_range(int *vec, int l, int r)
{
    for (int i = l + 1; i < r; i++)
    {
        // this implement is a bit like bubble sort, but it needs to bubble to the right position directly at each round
        // 2x write than the first implement
        for (int j = i; j > 0 && vec[j] < vec[j - 1]; j--)
        {
            exchange(vec, j, j - 1);
        }
    }
}

/*
void insertion_sort(int arr[], int len) {
  if (len < 2) return;
  for (int i = 1; i != len; ++i) {
    int key = arr[i];
    auto index = upper_bound(arr, 0, i, key) - arr;
    // 使用 memmove 移动元素，比使用 for 循环速度更快，时间复杂度仍为 O(n)
    // Only for trivial objects, for non-trivial objects, use std::move
    memmove(arr + index + 1, arr + index, (i - index) * sizeof(int));
    arr[index] = key;
  }
}
*/
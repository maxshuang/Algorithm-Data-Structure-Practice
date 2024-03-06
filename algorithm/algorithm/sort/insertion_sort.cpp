#include "common.h"
#include "insertion_sort.h"

// insertion_sort is like sort hand cards.
// it's a stable algorithm only if the comparison doesn't contain equal sign
// Time Complexity: O-(N^2/4) for average compares, O-(N^2/4) for average exchange. Worst Case is O-(N^2/2) for compares, O-(N^2/2) for exchanges
// Space Complexity: O(1)
// Data Movement: O-(N^2), too much read and write
// Can use the initial order of items in the input, GOOD if the original items are nearly in order (much, much faster)

void insertion_sort(int *vec, int num)
{
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

void insertion_sort_compact(int *vec, int num)
{
    // keep the invariant: vec[0, i] is ordered
    for (int i = 1; i < num; i++)
    {
        // this implement is a bit like bubble sort, but it needs to bubble to the right position directly at each round
        // 2x write than the first implement
        for (int j = i; j > 0 && vec[j] < vec[j - 1]; j--)
        {
            exchange(vec, j, j-1);
        }
    }
}

void insertion_sort_range(int *vec, int l, int r)
{
     for (int i = l+1; i < r; i++)
    {
        // this implement is a bit like bubble sort, but it needs to bubble to the right position directly at each round
        // 2x write than the first implement
        for (int j = i; j > 0 && vec[j] < vec[j - 1]; j--)
        {
            exchange(vec, j, j-1);
        }
    }
}

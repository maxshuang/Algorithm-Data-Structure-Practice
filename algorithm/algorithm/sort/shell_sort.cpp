#include "shell_sort.h"
#include "common.h"

// shell sort is an advanced version of insertion sort
// the h-sorting organizes the data in a way that the following rounds can benefit from the paritally ordered data
// It's some kinds of information shared between rounds
//
// if the factor is 3, the average time complexity can be O(N^3/2). less compares and less exchanges


void shellsort(int *vec, int num, int factor)
{
    int h = 1;
    while (h < num / 3)
        h = factor * h;
    while (h >= 1)
    {
        for (int i = h; i < num; ++i)
        {
            for (int j = i; j >=h && vec[j] < vec[j - h]; j -= h)
            {
                exchange(vec, j, j - h);
            }
        }
        h = h / factor;
        
        //print(vec, num);
    }
}
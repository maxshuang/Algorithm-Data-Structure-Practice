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

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
// Inplace Implementation
// Time Complexity: O(n^2logn)
void inplace_merge(int arr[], int start, int mid, int end)
{
	int start2 = mid + 1;

	// If the direct merge is already sorted
	if (arr[mid] <= arr[start2]) {
		return;
	}

	// Two pointers to maintain start
	// of both arrays to merge
	while (start <= mid && start2 <= end) {

		// If element 1 is in right place
		if (arr[start] <= arr[start2]) {
			start++;
		}
		else {
			int value = arr[start2];
			int index = start2;

			// Shift all the elements between element 1
			// element 2, right by 1.
			while (index != start) {
				arr[index] = arr[index - 1];
				index--;
			}
			arr[start] = value;

			// Update all the pointers
			start++;
			mid++;
			start2++;
		}
	}
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void inplace_mergeSort(int arr[], int l, int r)
{
	if (l < r) {

		// Same as (l + r) / 2, but avoids overflow
		// for large l and r
		int m = l + (r - l) / 2;

		// Sort first and second halves
		inplace_mergeSort(arr, l, m);
		inplace_mergeSort(arr, m + 1, r);

		inplace_merge(arr, l, m, r);
	}
}

/*
MergeSort+insertion_sort+shell_sort
Time Complexity: O(nlogn^2)

// C++ program for the above approach
#include <bits/stdc++.h>
using namespace std;

// Calculating next gap
int nextGap(int gap)
{
	if (gap <= 1)
		return 0;
		
	return (int)ceil(gap / 2.0);
}

// Function for swapping
void swap(int nums[], int i, int j)
{
	int temp = nums[i];
	nums[i] = nums[j];
	nums[j] = temp;
}

// Merging the subarrays using shell sorting
// Time Complexity: O(nlog n)
// Space Complexity: O(1)
void inPlaceMerge(int nums[], int start,
							int end)
{
	int gap = end - start + 1;
	
	for(gap = nextGap(gap); 
		gap > 0; gap = nextGap(gap)) 
	{
		for(int i = start; i + gap <= end; i++) 
		{
			int j = i + gap;
			if (nums[i] > nums[j])
				swap(nums, i, j);
		}
	}
}

// merge sort makes log n recursive calls
// and each time calls merge()
// which takes nlog n steps
// Time Complexity: O(n*log n + 2((n/2)*log(n/2)) +
// 4((n/4)*log(n/4)) +.....+ 1)
// Time Complexity: O(logn*(n*log n))
// i.e. O(n*(logn)^2)
// Space Complexity: O(1)
void mergeSort(int nums[], int s, int e)
{
	if (s == e)
		return;

	// Calculating mid to slice the
	// array in two halves
	int mid = (s + e) / 2;

	// Recursive calls to sort left
	// and right subarrays
	mergeSort(nums, s, mid);
	mergeSort(nums, mid + 1, e);
	
	inPlaceMerge(nums, s, e);
}
*/
// C++ program to demonstrate performance of 
// C qsort and C++ sort() algorithm 
// From:https://www.geeksforgeeks.org/c-qsort-vs-c-sort/
// The GNU Standard C++ library, for example, uses a 3-part hybrid sorting algorithm: introsort is performed first (introsort itself being a hybrid of quicksort and heap sort) followed by an insertion sort on the result.
// The new C++11 standard requires that the complexity of sort to be O(Nlog(N)) in the worst case
// STL’s sort ran faster than C’s qsort, because C++’s templates generate optimized code for a particular data type and a particular comparison function. STL’s sort runs 20% to 50% faster than the hand-coded quicksort and 250% to 1000% faster than the C qsort library function
// References: http://theory.stanford.edu/~amitp/rants/c++-vs-c https://en.wikipedia.org/wiki/Sort_(C%2B%2B)

#include <bits/stdc++.h> 
#include "catch.hpp"
using namespace std; 

// Number of elements to be sorted 
#define N 1000000 

// A comparator function used by qsort 
int compare(const void * a, const void * b) 
{ 
	return ( *(int*)a - *(int*)b ); 
} 

// Driver program to test above functions 
TEST_CASE("standard QuickSort", "[standard]")
{ 
	int arr[N], dupArr[N]; 

	// seed for random input 
	srand(time(NULL)); 

	// to measure time taken by qsort and sort 
	clock_t begin, end; 
	double time_spent; 

	// generate random input 
	for (int i = 0; i < N; i++) 
		dupArr[i] = arr[i] = rand()%100000; 

	begin = clock(); 
	qsort(arr, N, sizeof(int), compare); 
	end = clock(); 

	// calculate time taken by C qsort function 
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC; 

	cout << "Time taken by C qsort() - "
		<< time_spent << endl; 

	time_spent = 0.0; 

	begin = clock(); 
	sort(dupArr, dupArr + N); 
	end = clock(); 

	// calculate time taken by C++ sort 
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC; 

	cout << "Time taken by C++ sort() - "
		<< time_spent << endl; 
    // Time taken by C qsort() - 0.127721
    // Time taken by C++ sort() - 0.065018

} 
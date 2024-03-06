#pragma once

void quick_sort(int* vec, int num);
void quick_sort_range(int* vec, int l, int r);
int partition_wrong2(int* vec, int l, int r);
int partition_wrong3(int* vec, int l, int r);
int partition_compact(int* vec, int l, int r);
int pivot_func(int* vec, int l, int r);
int pivot_func2(int* vec, int l, int r);
int find_median(int* vec, int l, int m, int r);

void quick_3way(int* vec, int num);
void quick_3way_range(int* vec, int l, int r);

int partition_wrong(int* vec, int l, int r);

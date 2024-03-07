#pragma once
#include <vector>

class IndexPriorityMinQueue
{
public:
    IndexPriorityMinQueue(int maxN) : size_(0), maxN_(maxN), heap_(maxN_, -1), heap_key_index_(maxN_, -1), key_heap_index_(maxN_, -1) {}
    void Insert(int k, int val);
    int DelMin();
    int Min();
    int MinIndex();
    bool IsEmpty();
    bool Contains(int k);
    void Change(int k, int val); // ???
    void Delete(int k);
    int Size();

private:
    void swim(int k);
    void sink(int k);
    void exch(int i, int j);

    int size_;
    int maxN_;
    std::vector<int> heap_;
    std::vector<int> heap_key_index_;
    std::vector<int> key_heap_index_;
};
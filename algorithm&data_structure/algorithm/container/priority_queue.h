#pragma once
#include <vector>

class PriorityMinQueue
{
public:
    PriorityMinQueue():size_(0) { heap_.push_back(-1); };
    void Insert(int val);
    int DelMin();
    int Min();
    int Size();
    bool IsEmpty();

private:
    void swim(int pos);
    void sink(int pos);

    std::vector<int> heap_;
    int size_; // size_ is overlap with the index of last element
};
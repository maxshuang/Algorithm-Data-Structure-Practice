#include "priority_queue.h"

void PriorityMinQueue::Insert(int val)
{
    heap_.push_back(val);
    swim(++size_);
}

int PriorityMinQueue::Min()
{
    if (size_ == 0)
        return -1; // problem

    return heap_[1];
}

int PriorityMinQueue::DelMin()
{
    if (size_ == 0)
        return -1; // problem

    int min = heap_[1];
    std::swap(heap_[1], heap_[size_--]);
    sink(1);
    return min;
}

int PriorityMinQueue::Size()
{
    return size_;
}

bool PriorityMinQueue::IsEmpty()
{
    return size_ == 0;
}

void PriorityMinQueue::swim(int pos)
{
    int pp = pos / 2;
    while (pp >= 1 && heap_[pos] < heap_[pp])
    {
        std::swap(heap_[pos], heap_[pp]);
        pos = pp;
        pp = pp / 2;
    }
}

void PriorityMinQueue::sink(int pos)
{
    int lc = 2 * pos;
    while (lc <= size_)
    {
        // find the smaller child
        if (lc < size_ && heap_[lc + 1] < heap_[lc])
            lc++;
        if (heap_[pos] < heap_[lc])
            break;
        std::swap(heap_[pos], heap_[lc]);
        lc = 2 * lc;
    }
}
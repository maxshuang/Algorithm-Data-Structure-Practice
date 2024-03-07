#include "index_priority_queue.h"
#include "common.h"

// IndexPriorityMinQueue is used for Multiway merge

void IndexPriorityMinQueue::Insert(int k, int val)
{
    if (k >= maxN_ || k < 0 || key_heap_index_[k] != -1)
        return;

    heap_[size_]=val;
    ++size_;
    heap_key_index_[size_ - 1] = k;
    key_heap_index_[k] = size_ - 1;
    swim(size_ - 1);

    //print(heap_, size_);
}

int IndexPriorityMinQueue::MinIndex()
{
    if (size_ == 0)
        return -1; // problem

    return heap_key_index_[0];
}

int IndexPriorityMinQueue::Min()
{
    if (size_ == 0)
        return -1; // problem

    return heap_[0];
}

int IndexPriorityMinQueue::DelMin()
{
    if (size_ == 0)
        return -1; // problem

    int index = heap_key_index_[0];
    exch(0, size_ - 1);
    size_--;
    sink(0);
    return index;
}

int IndexPriorityMinQueue::Size()
{
    return size_;
}

bool IndexPriorityMinQueue::IsEmpty()
{
    return size_ == 0;
}

void IndexPriorityMinQueue::swim(int pos)
{
    while (pos > 0)
    {
        int pp = pos / 2;
        if ((pos & 1) == 0)
            pp--;
        if (heap_[pos] >= heap_[pp])
        {
            break;
        }
        exch(pos, pp);
        pos = pp;
    }
}

void IndexPriorityMinQueue::sink(int pos)
{
    int lc = 2 * pos + 1;
    while (lc < size_)
    {
        // find the smaller child
        if (lc < size_-1 && heap_[lc + 1] < heap_[lc])
            lc++;
        if (heap_[pos] < heap_[lc])
            break;
        exch(pos, lc);
        lc = 2 * lc;
    }
}

void IndexPriorityMinQueue::exch(int i, int j)
{
    std::swap(heap_[i], heap_[j]);
    std::swap(heap_key_index_[i], heap_key_index_[j]);
    std::swap(key_heap_index_[heap_key_index_[i]], key_heap_index_[heap_key_index_[j]]);
}

bool IndexPriorityMinQueue::Contains(int k)
{
    if(k<0 || k>=maxN_) return false;

    return key_heap_index_[k] != -1;
}

void IndexPriorityMinQueue::Change(int k, int val)
{
    if(k<0 || k>=size_|| key_heap_index_[k] == -1) return;

    int index = key_heap_index_[k];
    heap_[index] = val;
    swim(index);
    sink(index);
}

void IndexPriorityMinQueue::Delete(int k)
{
    if(k<0 || k>=size_|| key_heap_index_[k] == -1) return;
    
    int index = key_heap_index_[k];
    exch(index, size_-1);
    size_--;
    swim(index);
    sink(index);
    key_heap_index_[k] = -1;
    heap_key_index_[size_] = -1;
}
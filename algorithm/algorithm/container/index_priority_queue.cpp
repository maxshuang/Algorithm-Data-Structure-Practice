#include "index_priority_queue.h"
#include "common.h"

template <class T, class Comp>
void IndexPriorityQueue<T, Comp>::Insert(int k, const T &val)
{
    int k1 = k + 1;
    if (k1 > maxN_ || k1 <= 0 || key_heap_index_[k1] != -1)
        return;

    ++size_;
    heap_[size_] = val;
    heap_key_index_[size_] = k1;
    key_heap_index_[k1] = size_;
    swim(size_);
}

template <class T, class Comp>
int IndexPriorityQueue<T, Comp>::TopIndex() const
{
    if (size_ <= 0)
        return -1; // problem

    return heap_key_index_[1] - 1;
}

template <class T, class Comp>
int IndexPriorityQueue<T, Comp>::Pop()
{
    if (size_ <= 0)
        return -1; // problem

    int index = heap_key_index_[1];
    exch(1, size_);
    size_--;
    sink(1);
    return index - 1;
}

template <class T, class Comp>
const T &IndexPriorityQueue<T, Comp>::Top() const
{
    if (size_ <= 0) {
        static T t; // problem, may not have the default constructor
        return t;
    }

    return heap_[1];
}

template <class T, class Comp>
int IndexPriorityQueue<T, Comp>::Size() const
{
    return size_;
}

template <class T, class Comp>
bool IndexPriorityQueue<T, Comp>::IsEmpty() const
{
    return size_ == 0;
}

template <class T, class Comp>
void IndexPriorityQueue<T, Comp>::swim(int pos)
{
    while (pos > 1)
    {
        int pp = pos / 2;
        // std::less is the maximum heap
        if (comp_(heap_[pos], heap_[pp]))
            break;
        exch(pos, pp);
        pos = pp;
    }
}

template <class T, class Comp>
void IndexPriorityQueue<T, Comp>::sink(int pos)
{
    int lc = 2 * pos;
    while (lc <= size_)
    {
        // std::less is the maximum heap
        if (lc <= size_ - 1 && comp_(heap_[lc], heap_[lc + 1]))
            lc++;
        if (comp_(heap_[lc], heap_[pos]))
            break;
        exch(pos, lc);
        lc = 2 * lc;
    }
}

template <class T, class Comp>
void IndexPriorityQueue<T, Comp>::exch(int i, int j)
{
    std::swap(heap_[i], heap_[j]);
    std::swap(heap_key_index_[i], heap_key_index_[j]);
    std::swap(key_heap_index_[heap_key_index_[i]], key_heap_index_[heap_key_index_[j]]);
}

template <class T, class Comp>
bool IndexPriorityQueue<T, Comp>::ContainsIndex(int k) const
{
    int k1 = k + 1;
    if (k1 <= 0 || k1 > maxN_)
        return false;

    return key_heap_index_[k1] != -1;
}

template <class T, class Comp>
void IndexPriorityQueue<T, Comp>::Change(int k, const T &val)
{
    int k1 = k + 1;
    if (k1 <= 0 || k1 > maxN_ || key_heap_index_[k1] == -1)
        return;

    int index = key_heap_index_[k1];
    heap_[index] = val;
    swim(index);
    sink(index);
}

template <class T, class Comp>
void IndexPriorityQueue<T, Comp>::DeleteIndex(int k)
{
    int k1 = k + 1;
    if (k1 <= 0 || k1 > maxN_ || key_heap_index_[k1] == -1)
        return;

    int index = key_heap_index_[k1];
    exch(index, size_);
    key_heap_index_[k1] = -1;
    heap_key_index_[size_] = -1;
    size_--;
    swim(index);
    sink(index);
}
#pragma once
#include <vector>
#include <functional>

// Aligned to std::priority_queue, std::less is for the maximum heap
template <class T, class Comp = std::less<T>>
class IndexPriorityQueue
{
public:
    IndexPriorityQueue(int maxN) : size_(0), maxN_(maxN), heap_(maxN_ + 1), heap_key_index_(maxN_ + 1, -1), key_heap_index_(maxN_ + 1, -1) {}
    void Insert(int k, const T &val)
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
    // return key
    int Pop()
    {
        if (size_ <= 0)
            return -1; // problem

        int index = heap_key_index_[1];
        exch(1, size_);
        size_--;
        sink(1);
        return index - 1;
    }
    const T &Top() const
    {
        if (size_ <= 0)
        {
            static T t; // problem, may not have the default constructor
            return t;
        }

        return heap_[1];
    }
    int TopIndex() const
    {
        if (size_ <= 0)
            return -1; // problem

        return heap_key_index_[1] - 1;
    }

    bool ContainsIndex(int k) const
    {
        int k1 = k + 1;
        if (k1 <= 0 || k1 > maxN_)
            return false;

        return key_heap_index_[k1] != -1;
    }
    void Change(int k, const T &val)
    {
        int k1 = k + 1;
        if (k1 <= 0 || k1 > maxN_ || key_heap_index_[k1] == -1)
            return;

        int index = key_heap_index_[k1];
        heap_[index] = val;
        swim(index);
        sink(index);
    }
    void DeleteIndex(int k)
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
    bool IsEmpty() const { return size_ == 0; }
    int Size() const { return size_; }

private:
    void swim(int k)
    {
        while (k > 1)
        {
            int pp = k / 2;
            // std::less is the maximum heap
            if (comp_(heap_[k], heap_[pp]))
                break;
            exch(k, pp);
            k = pp;
        }
    }
    void sink(int pos)
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
    void exch(int i, int j)
    {
        std::swap(heap_[i], heap_[j]);
        std::swap(heap_key_index_[i], heap_key_index_[j]);
        std::swap(key_heap_index_[heap_key_index_[i]], key_heap_index_[heap_key_index_[j]]);
    }

    int size_;
    int maxN_;
    // [WARN] don't initialize heap_ here, or it will require default constructor for T
    // [FIXME](maxshuang)
    std::vector<T> heap_;
    // heap index => key
    std::vector<int> heap_key_index_;
    // key => heap index
    std::vector<int> key_heap_index_;
    Comp comp_;
};

// Explicit instantiation
template class IndexPriorityQueue<int, std::less<int>>;
template class IndexPriorityQueue<int, std::greater<int>>;
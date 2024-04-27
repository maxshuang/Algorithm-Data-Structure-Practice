#pragma once
#include <vector>
#include <functional>

template<class T, class Comp=std::less<T>>
class IndexPriorityQueue
{
public:
    IndexPriorityQueue(int maxN) : size_(0), maxN_(maxN), heap_(maxN_+1), heap_key_index_(maxN_+1, -1), key_heap_index_(maxN_+1, -1) {}
    void Insert(int k, const T& val);
    // return key
    int Pop();
    const T& Top() const;
    int TopIndex() const;
    bool IsEmpty() const;
    bool ContainsIndex(int k) const;
    void Change(int k, const T& val);
    void DeleteIndex(int k);
    int Size() const;

private:
    void swim(int k);
    void sink(int k);
    void exch(int i, int j);

    int size_;
    int maxN_;
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
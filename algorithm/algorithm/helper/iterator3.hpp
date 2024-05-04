#pragma once
#include <forward_list>
#include "iterator_base.hpp"

// ListIterator is the Iterator implementation of std::forward_list
template <class Tp, class Ptr=Tp*, class Ref=Tp&>
class SListIterator : public Iterator<Tp, Ptr, Ref>
{
public:
    typedef SListIterator<Tp, Ptr, Ref> self_type;
    typedef Iterator<Tp, Ptr, Ref> base_type;

    explicit SListIterator(const typename std::forward_list<Tp>::iterator &iter) : fl_iter_(iter) {}
    virtual ~SListIterator() {}

    // ok for the Covariant Return Type
    self_type &operator++() override
    {
        ++fl_iter_;
        return *this;
    }

    self_type operator++(int) override
    {
        self_type tmp = *this;
        ++(*this);
        return tmp;
    }

    // C++ doesn't support contravariant parameter types for virtual functions directly
    bool operator==(const base_type &other) const override
    {
        return fl_iter_ == static_cast<const self_type&>(other).fl_iter_;
    }

    bool operator!=(const base_type &other) const override
    {
        return !(*this == other);
    }

    Ptr operator->() const override
    {
        return &*fl_iter_;
    }

    Ref operator*() const override
    {
        return *fl_iter_;
    }

private:
    typename std::forward_list<Tp>::iterator fl_iter_;
};

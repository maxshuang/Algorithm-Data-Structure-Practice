#pragma once
#include <iterator>

// std::algorithm style iterator interface
template <class Tp, class Ptr, class Ref>
class Iterator : public std::iterator<std::forward_iterator_tag, Tp,
                                      std::ptrdiff_t, Ptr, Ref>
{
public:
    typedef Iterator<Tp, Ptr, Ref> self_type;
    virtual ~Iterator() {}

    virtual self_type &operator++() = 0;
    //virtual self_type operator++(int) = 0;
    virtual bool operator==(const self_type &) const = 0;
    virtual bool operator!=(const self_type &) const = 0;
    virtual Ptr operator->() const = 0;
    virtual Ref operator*() const = 0;
};
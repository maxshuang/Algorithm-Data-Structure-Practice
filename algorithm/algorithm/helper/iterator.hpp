#pragma once
#include <forward_list>

template <class T>
class Iterator {
public:
    typedef typename std::forward_list<T>::iterator base_type;
    typedef typename base_type::iterator_category iterator_category;
    typedef typename base_type::value_type        value_type;
    typedef typename base_type::difference_type   difference_type;
    typedef typename base_type::pointer           pointer;
    typedef typename base_type::reference         reference;

    explicit Iterator(const base_type &iter): iter_(iter) {}
    ~Iterator() = default;
    Iterator(const Iterator &) = default;
    Iterator &operator=(const Iterator &) = default;

    // Pre-increment
    Iterator &operator++() {
        ++iter_;
        return *this;
    }

    // Post-increment
    Iterator operator++(int) {
        Iterator other = *this;
        ++(*this);
        return other;
    }

    bool operator==(const Iterator &other) const {
        return iter_ == other.iter_;
    }

    bool operator!=(const Iterator &other) const {
        return !(*this == other);
    }

    pointer operator->() const {
        return &(operator*());
    }

    reference operator*() const {
        return *iter_;
    }

private:
    base_type iter_;
};
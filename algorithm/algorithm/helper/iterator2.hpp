#include <forward_list>

template <class T>
class ConstIterator2: public std::forward_list<T>::const_iterator {
public:
    typedef typename std::forward_list<T>::const_iterator base_type;

    explicit ConstIterator2(const base_type &iter):  base_type(iter){}
};
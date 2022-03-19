#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "reverse_iterator.hpp"

namespace ft
{
template<typename T, typename Alloc = std::allocator<T> >
class vector
{
public:
    typedef T value_type;
    typedef Alloc allocator_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename Alloc::pointer pointer;
    typedef typename Alloc::const_pointer const_pointer;
    typedef pointer iterator;
    typedef const_pointer const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
};
} // namespace ft

#endif

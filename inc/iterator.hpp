#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
template<class Iter>
typename iterator_traits<Iter>::difference_type
distance(Iter start, Iter last)
{
    typename iterator_traits<Iter>::difference_type result = 0;
    for (; start != last; ++start, ++result) ;
    return result;
}
} // namespace ft

#endif

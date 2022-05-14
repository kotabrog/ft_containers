#ifndef MAP_HPP
#define MAP_HPP

#include "_Rb_tree.hpp"
#include "pair.hpp"

namespace ft
{
template<typename Key, typename T, typename Compare = std::less<Key>,
         typename Alloc = std::allocator<ft::pair<const Key, T> > >
class map
{
public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef ft::pair<const Key, T> value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Compare key_compare;
    typedef Alloc allocator_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename Alloc::pointer pointer;
    typedef typename Alloc::const_pointer const_pointer;
    // typedef // iterator;
    // typedef // const_iterator;
    // typedef ft::reverse_iterator<iterator> reverse_iterator;
    // typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

};

} // namespace ft

#endif

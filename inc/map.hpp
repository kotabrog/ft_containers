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

private:
    // key_compareの部分はpair用のcompareに変更
    typedef _Rb_tree<value_type, key_compare, allocator_type> _Tree;

public:
    typedef typename _Tree::iterator iterator;
    typedef typename _Tree::const_iterator const_iterator;
    typedef typename _Tree::reverse_iterator reverse_iterator;
    typedef typename _Tree::const_reverse_iterator const_reverse_iterator;

};

} // namespace ft

#endif

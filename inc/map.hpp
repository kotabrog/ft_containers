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
    typedef pair<const Key, T> value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Compare key_compare;
    typedef Alloc allocator_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename Alloc::pointer pointer;
    typedef typename Alloc::const_pointer const_pointer;

public:
    class value_compare
        : public std::binary_function<value_type, value_type, bool>
    {
    protected:
        Compare comp;

        value_compare(Compare c) : comp(c) {}

    public:
        bool operator()(const value_type& lhs, const value_type& rhs) const
        {
            return comp(lhs.first, rhs.first);
        }
    };

private:
    class _PairFirstCompare: public value_compare
    {
    public:
        _PairFirstCompare() : value_compare(Compare()) {}
        _PairFirstCompare(Compare c) : value_compare(c) {}

        bool operator()(const value_type& lhs, const value_type& rhs) const
        {
            return this->comp(lhs.first, rhs.first);
        }

        Compare& get_key_compare() const
        {
            return this->comp;
        }
    };

    class _PairValueCopy
    {
    public:
        template<typename U>
        void operator()(U& dest, U& src)
        {
            dest.second = src.second;
        }
    };

    typedef _Rb_tree<value_type, _PairFirstCompare, allocator_type, _PairValueCopy> _Tree;

    _Tree _tree;

public:
    typedef typename _Tree::iterator iterator;
    typedef typename _Tree::const_iterator const_iterator;
    typedef typename _Tree::reverse_iterator reverse_iterator;
    typedef typename _Tree::const_reverse_iterator const_reverse_iterator;

    map() : _tree(Compare()) {};

    iterator begin()
    {
        return iterator(_tree._begin);
    }

    iterator end()
    {
        return iterator(&(_tree._end));
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(iterator(&(_tree._end)));
    }

    reverse_iterator rend()
    {
        return reverse_iterator(iterator(_tree._begin));
    }

    pair<iterator, bool> insert(const value_type& value)
    {
        return _tree.insert_node(value);
    }

    void erase(iterator pos)
    {
        _tree.delete_node(pos);
    }
};

} // namespace ft

#endif

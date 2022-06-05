#ifndef MAP_HPP
#define MAP_HPP

#include "_Rb_tree.hpp"
#include "pair.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"

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

        const Compare& get_key_compare() const
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

    explicit map(const Compare& comp, const Alloc& alloc = Alloc())
        : _tree(comp, alloc) {}

    template<class It>
    map(It start, It last, const Compare& comp = Compare(), const Alloc& alloc = Alloc())
        : _tree(start, last, comp, alloc) {}

    map(const map& other)
        : _tree(other._tree) {}

    allocator_type get_allocator() const
    {
        return _tree._alloc;
    }

    T& at(const Key& key)
    {
        try
        {
            return _tree.template search_node<key_type, mapped_type, Compare>(key);
        }
        catch(const std::exception& e)
        {
            throw std::out_of_range("map::at");
        }
    }

    const T& at(const Key& key) const
    {
        try
        {
            return _tree.template search_node<key_type, mapped_type, Compare>(key);
        }
        catch(const std::exception& e)
        {
            throw std::out_of_range("map::at");
        }
    }

    T& operator[](const Key& key)
    {
        return insert(pair<const Key, T>(key, T())).first->second;
    }

    iterator begin()
    {
        return iterator(_tree._begin);
    }

    const_iterator begin() const
    {
        return const_iterator(_tree._begin);
    }

    iterator end()
    {
        return iterator(_tree._end);
    }

    const_iterator end() const
    {
        return const_iterator(_tree._end);
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(iterator(_tree._end));
    }

    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(const_iterator(_tree._end));
    }

    reverse_iterator rend()
    {
        return reverse_iterator(iterator(_tree._begin));
    }

    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(const_iterator(_tree._begin));
    }

    bool empty() const
    {
        return _tree.empty();
    }

    size_type size() const
    {
        return _tree.size();
    }

    size_type max_size() const
    {
        return _tree.max_size();
    }

    void clear()
    {
        _tree.clear();
    }

    pair<iterator, bool> insert(const value_type& value)
    {
        return _tree.insert_node(value);
    }

    iterator insert(iterator hint, const value_type& value)
    {
        return _tree.insert_node(hint, value);
    }

    template< class It >
    void insert(It start, It last)
    {
        _tree.insert_iter(start, last);
    }

    void erase(iterator pos)
    {
        _tree.delete_node(pos);
    }

    void erase(iterator start, iterator last)
    {
        _tree.delete_node(start, last);
    }

    size_type erase(const Key& key)
    {
        return _tree.template delete_node<key_type, Compare>(key);
    }

    void swap(map& other)
    {
        _tree.swap(other._tree);
    }

    size_type count(const Key& key) const
    {
        return _tree.template count<key_type, Compare>(key);
    }

    iterator find(const Key& key)
    {
        return _tree.template find<key_type, Compare>(key);
    }

    const_iterator find(const Key& key) const
    {
        return _tree.template find<key_type, Compare>(key);
    }

    pair<iterator, iterator> equal_range(const Key& key)
    {
        return _tree.template equal_range<key_type, Compare>(key);
    }

    pair<const_iterator, const_iterator> equal_range(const Key& key) const
    {
        return _tree.template equal_range<key_type, Compare>(key);
    }

    iterator lower_bound(const Key& key)
    {
        return _tree.template lower_bound<key_type, Compare>(key);
    }

    const_iterator lower_bound(const Key& key) const
    {
        return _tree.template lower_bound<key_type, Compare>(key);
    }

    iterator upper_bound(const Key& key)
    {
        return _tree.template upper_bound<key_type, Compare>(key);
    }

    const_iterator upper_bound(const Key& key) const
    {
        return _tree.template upper_bound<key_type, Compare>(key);
    }

    key_compare key_comp() const
    {
        return _tree._comp.get_key_compare();
    }

    value_compare value_comp() const
    {
        return _tree._comp;
    }
};

template<class Key, class T, class Compare, class Alloc>
bool operator==(const map<Key, T, Compare, Alloc>& lhs,
                const map<Key, T, Compare, Alloc>& rhs)
{
    return (lhs.size() == rhs.size() &&
            ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template<class Key, class T, class Compare, class Alloc>
bool operator!=(const map<Key, T, Compare, Alloc>& lhs,
                const map<Key, T, Compare, Alloc>& rhs)
{
    return !(lhs == rhs);
}

template<class Key, class T, class Compare, class Alloc>
bool operator<(const map<Key, T, Compare, Alloc>& lhs,
                const map<Key, T, Compare, Alloc>& rhs)
{
    return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<class Key, class T, class Compare, class Alloc>
bool operator<=(const map<Key, T, Compare, Alloc>& lhs,
                const map<Key, T, Compare, Alloc>& rhs)
{
    return !(rhs < lhs);
}

template<class Key, class T, class Compare, class Alloc>
bool operator>(const map<Key, T, Compare, Alloc>& lhs,
                const map<Key, T, Compare, Alloc>& rhs)
{
    return rhs < lhs;
}

template<class Key, class T, class Compare, class Alloc>
bool operator>=(const map<Key, T, Compare, Alloc>& lhs,
                const map<Key, T, Compare, Alloc>& rhs)
{
    return !(lhs < rhs);
}

template<class Key, class T, class Compare, class Alloc>
void swap(map<Key, T, Compare, Alloc>& lhs,
          map<Key, T, Compare, Alloc>& rhs)
{
    lhs.swap(rhs);
}

} // namespace ft

#endif

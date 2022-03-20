#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "iterator.hpp"
#include "is_integral.hpp"
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
private:
    iterator _start;
    iterator _last;
    iterator _end_of_storage;
    Alloc _alloc;

    typename Alloc::template rebind<value_type>::other
    _get_alloc()
    {
        return typename Alloc::template rebind<value_type>::other();
    }

    template <typename Iter>
    typename Alloc::template rebind<typename iterator_traits<Iter>::value_type>::other
    _get_alloc_by_iter(Iter)
    {
        return typename Alloc::template rebind<typename iterator_traits<Iter>::value_type>::other();
    }

    // template <typename V>
    // typename Alloc::template rebind<V>::other
    // _get_alloc_by_value(const V&)
    // {
    //     return typename Alloc::template rebind<V>::other();
    // }

    template <typename Iter>
    void _destroy(Iter iter)
    {
        _get_alloc_by_iter(iter).destroy(iter);
    }

    void _destroy(iterator start, iterator last)
    {
        for (; start < last; ++start)
            _destroy(start);
    }

    pointer _allocate(size_type n)
    {
        if (n == 0)
            return pointer();
        return _get_alloc().allocate(n);
    }

    template <typename Iter, typename V>
    void _construct(Iter iter, const V& value)
    {
        _get_alloc_by_iter(iter).construct(iter, value);
    }

    template <typename Iter>
    void _deallocate(Iter iter, size_type n)
    {
        _get_alloc_by_iter(iter).deallocate(iter, n);
    }

    // void _create_storage(size_type n)
    // {
    //     _start = _allocate(n);
    //     _last = _start;
    //     _end_of_storage = _start + n;
    // }

    void _fill_value(iterator start,
                     size_type n,
                     const value_type& value)
    {
        iterator temp = start;
        try
        {
            for (; n > 0; --n, ++temp)
                _construct(temp, value);
        }
        catch(const std::exception& e)
        {
            _destroy(start, temp);
            throw;
        }
    }

    template<class Iter>
    void _copy(Iter start, Iter last, iterator dest)
    {
        iterator temp = dest;
        try
        {
            for (; start != last; ++start, ++temp)
                _construct(temp, *start);
        }
        catch(const std::exception& e)
        {
            _destroy(dest, temp);
            throw;
        }
    }

    void _value_init(size_type count, const T& value)
    {
        _start = _allocate(count);
        _fill_value(_start, count, value);
        _last = _start + count;
        _end_of_storage = _last;
    }

    template<class Integer>
    void _iter_init(Integer count, Integer value, true_type)
    {
        _value_init(count, value);
    }

    template<class Iter>
    void _iter_init(Iter start, Iter last, false_type)
    {
        typename iterator_traits<Iter>::difference_type dist = distance(start, last);
        _start = _allocate(dist);
        _copy(start, last, _start);
        _last = _start + dist;
        _end_of_storage = _last;
    }

public:
    vector(): _start(), _last(), _end_of_storage(), _alloc() {}

    explicit vector(const Alloc& alloc)
        : _start(), _last(), _end_of_storage(), _alloc(alloc) {}

    explicit vector(size_type count,
                    const T& value = T(),
                    const Alloc& alloc = Alloc())
        : _alloc(alloc)
    {
        _value_init(count, value);
    }

    template<class Iter>
    vector(Iter start, Iter last,
           const Alloc& alloc = Alloc())
        : _alloc(alloc)
    {
        typedef typename is_integral<Iter>::type Integral;
        _iter_init(start, last, Integral());
    }

    vector(const vector& other)
        : _alloc(other._alloc)
    {
        _iter_init(other.begin(), other.end(), false_type());
    }

    ~vector()
    {
        _destroy(_start, _last);
        if (size() > 0)
            _deallocate(_start, capacity());
    }

    Alloc get_allocator() const
    {
        return _alloc;
    }

    reference operator[](size_type n)
    {
        return *(_start + n);
    }

    const_reference operator[](size_type n) const
    {
        return *(_start + n);
    }

    iterator begin()
    {
        return _start;
    }

    const_iterator begin() const
    {
        return _start;
    }

    iterator end()
    {
        return _last;
    }

    const_iterator end() const
    {
        return _last;
    }

    size_type size() const
    {
        return _last - _start;
    }

    size_type capacity() const
    {
        return _end_of_storage - _start;
    }

    void push_back(const T& value)
    {
        if (_last != _end_of_storage)
        {
            _construct(_last, value);
            ++_last;
        }
        else
        {
            // not yet
        }
    }
};
} // namespace ft

#endif

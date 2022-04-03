#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <limits>
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
    _rebind_alloc(const Alloc& alloc) const
    {
        return typename Alloc::template rebind<value_type>::other(alloc);
    }

    typename Alloc::template rebind<value_type>::other
    _get_alloc() const
    {
        return _rebind_alloc(_alloc);
    }

    template <typename Iter>
    typename Alloc::template rebind<typename iterator_traits<Iter>::value_type>::other
    _get_alloc_by_iter(Iter) const
    {
        return typename Alloc::template rebind<typename iterator_traits<Iter>::value_type>::other(_alloc);
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

    template<class Iter>
    iterator _copy(Iter start, Iter last, iterator dest)
    {
        for (; start != last; ++start, ++dest)
            *dest = *start;
        return dest;
    }

    template<class Iter>
    Iter _copy(Iter start, Iter last, iterator dest, size_type n)
    {
        for (size_type i = 0; i < n && start != last; ++start, ++dest, ++i)
            *dest = *start;
        return start;
    }

    template<class Iter>
    iterator _reverse_copy(Iter start, Iter last, iterator dest)
    {
        --start;
        --dest;
        --last;
        for (; start != last; --dest, --last)
            *dest = *last;
        return dest;
    }

    iterator _fill_value(iterator dest,
                         size_type n,
                         const value_type& value)
    {
        for (size_type i = 0; i < n; ++i, ++dest)
            *dest = value;
        return dest;
    }

    void _destroy_and_deallocate()
    {
        _destroy(_start, _last);
        if (capacity() > 0)
            _deallocate(_start, capacity());
    }

    // void _create_storage(size_type n)
    // {
    //     _start = _allocate(n);
    //     _last = _start;
    //     _end_of_storage = _start + n;
    // }

    void _construct_by_value(iterator start,
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
    void _construct_by_iterator(Iter start, Iter last, iterator dest)
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

    template<class Iter>
    iterator _allocate_and_copy(size_type n, Iter start, Iter last)
    {
        iterator temp = _allocate(n);
        try
        {
            _construct_by_iterator(start, last, temp);
        }
        catch(const std::exception& e)
        {
            _deallocate(temp, n);
            throw;
        }
        return temp;
    }

    iterator _allocate_and_fill_value(size_type n, const value_type& value)
    {
        iterator temp = _allocate(n);
        try
        {
            _construct_by_value(temp, n, value);
        }
        catch(const std::exception& e)
        {
            _deallocate(temp, n);
            throw;
        }
        return temp;
    }

    void _value_init(size_type count, const T& value)
    {
        _start = _allocate(count);
        try
        {
            _construct_by_value(_start, count, value);
        }
        catch(const std::exception& e)
        {
            _deallocate(_start, count);
            throw;
        }
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
        _start = _allocate_and_copy(dist, start, last);
        _last = _start + dist;
        _end_of_storage = _last;
    }

    void _value_assign(size_type count, const T& value)
    {
        if (count > capacity())
        {
            iterator temp = _allocate_and_fill_value(count, value);
            _destroy_and_deallocate();
            _start = temp;
            _end_of_storage = _start + count;
        }
        else if (size() >= count)
        {
            _destroy(_fill_value(_start, count, value),
                     _last);
        }
        else
        {
            _fill_value(_start, size(), value);
            _construct_by_value(_last, count - size(), value);
        }
        _last = _start + count;
    }

    template<class Integer>
    void _iter_assign(Integer count, Integer value, true_type)
    {
        _value_assign(count, value);
    }

    template<class Iter>
    void _iter_assign(Iter start, Iter last, false_type)
    {
        size_type dist = size_type(distance(start, last));
        if (dist > capacity())
        {
            iterator temp = _allocate_and_copy(dist, start, last);
            _destroy_and_deallocate();
            _start = temp;
            _end_of_storage = _start + dist;
        }
        else if (size() >= dist)
        {
            _destroy(_copy(start, last, _start),
                     _last);
        }
        else
        {
            Iter temp = _copy(start, last, _start, size());
            _construct_by_iterator(temp, last, _last);
        }
        _last = _start + dist;
    }

    void _range_check(size_type n) const
    {
        if (n >= size())
            throw std::out_of_range("vector::_range_check n >= size()");
    }

    void _realloc_insert_by_value(size_type pos,
                                  const value_type& value,
                                  size_type n = 1)
    {
        size_type total_size = n + size();
        iterator temp = _allocate(total_size);
        iterator copied_pos = temp;
        try
        {
            _construct_by_iterator(_start, _start + pos, temp);
            copied_pos = temp + pos;
            _construct_by_value(copied_pos, n, value);
            copied_pos = copied_pos + n;
            _construct_by_iterator(_start + pos, _last, copied_pos);
        }
        catch(const std::exception& e)
        {
            _destroy(temp, copied_pos);
            _deallocate(temp, total_size);
            throw;
        }
        _destroy_and_deallocate();
        _start = temp;
        _last = _start + total_size;
        _end_of_storage = _last;
    }

    void _insert_by_value(size_type pos,
                          const value_type& value,
                          size_type n = 1)
    {
        size_type add_iter_num = std::min(n, size() - pos);
        size_type add_value_num = n - add_iter_num;
        iterator copied_pos = _last;
        try
        {
            _construct_by_value(_last, add_value_num, value);
            copied_pos = _last + add_value_num;
            _construct_by_iterator(_last - add_iter_num, _last, copied_pos);
        }
        catch(const std::exception& e)
        {
            _destroy(_last, copied_pos);
            throw;
        }
        size_type copy_iter_num = size() - pos > n ? size() - pos - n : 0;
        size_type copy_value_num = n - add_value_num;
        _reverse_copy(_start + pos,
                      _start + pos + copy_iter_num,
                      _last);
        _fill_value(_start + pos, copy_value_num, value);
        _last = _last + n;
    }

    template<class Iter>
    void _realloc_insert_by_iter(size_type pos,
                                 Iter start,
                                 Iter last,
                                 size_type count)
    {
        size_type total_size = size() + count;
        iterator temp = _allocate(total_size);
        iterator copied_pos = temp;
        try
        {
            _construct_by_iterator(_start, _start + pos, temp);
            copied_pos = temp + pos;
            _construct_by_iterator(start, last, copied_pos);
            copied_pos = copied_pos + count;
            _construct_by_iterator(_start + pos, _last, copied_pos);
        }
        catch(const std::exception& e)
        {
            _destroy(temp, copied_pos);
            _deallocate(temp, total_size);
            throw;
        }
        _destroy_and_deallocate();
        _start = temp;
        _last = _start + total_size;
        _end_of_storage = _last;
    }

    template<class Iter>
    void _insert_by_iter(size_type pos,
                        Iter start,
                        Iter last,
                        size_type count)
    {
        size_type add_origin_num = std::min(count, size() - pos);
        size_type add_iter_num = count - add_origin_num;
        size_type copy_iter_num = count - add_iter_num;
        iterator copied_pos = _last;
        try
        {
            Iter temp = start;
            for (size_type i = 0; i < copy_iter_num; ++i, ++temp) ;
            _construct_by_iterator(temp, last, copied_pos);
            copied_pos = _last + add_iter_num;
            _construct_by_iterator(_last - add_origin_num, _last, copied_pos);
        }
        catch(const std::exception& e)
        {
            _destroy(_last, copied_pos);
            throw;
        }
        size_type copy_origin_num = size() - pos > count ? size() - pos - count : 0;
        _reverse_copy(_start + pos,
                      _start + pos + copy_origin_num,
                      _last);
        _copy(start, last, _start + pos, copy_iter_num);
        _last = _last + count;
    }

    size_type _value_insert(iterator pos, size_type count, const T& value)
    {
        const size_type n = pos - _start;
        if (_last + count > _end_of_storage)
        {
            _realloc_insert_by_value(n, value, count);
        }
        else
        {
            _insert_by_value(n, value, count);
        }
        return n;
    }

    template<class Integer>
    void _iter_insert(iterator pos,
                      Integer count,
                      Integer value,
                      true_type)
    {
        if (count > 0)
        {
            _value_insert(pos, count, value);
        }
    }

    template<class Iter>
    void _iter_insert(iterator pos,
                      Iter start,
                      Iter last,
                      false_type)
    {
        typename iterator_traits<Iter>::difference_type count = distance(start, last);
        if (count > 0)
        {
            const size_type n = pos - _start;
            if (_last + count > _end_of_storage)
            {
                _realloc_insert_by_iter(n, start, last, count);
            }
            else
            {
                _insert_by_iter(n, start, last, count);
            }
        }
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
        _destroy_and_deallocate();
    }

    vector& operator=(const vector& other)
    {
        if (&other != this)
        {
            const size_type other_len = other.size();
            if (other_len > capacity())
            {
                iterator temp = _allocate_and_copy(other_len, other._start, other._last);
                _destroy_and_deallocate();
                _start = temp;
                _end_of_storage = temp + other_len;
            }
            else if (size() >= other_len)
            {
                _destroy(_copy(other._start, other._last, _start),
                         _last);
            }
            else
            {
                _copy(other._start, other._start + size(), _start);
                _construct_by_iterator(other._start + size(), other._last, _last);
            }
            _last = _start + other_len;
        }
        return *this;
    }

    void assign(size_type count, const T& value)
    {
        _value_assign(count, value);
    }

    template<class Iter>
    void assign(Iter start, Iter last)
    {
        typedef typename is_integral<Iter>::type Integral;
        _iter_assign(start, last, Integral());
    }

    Alloc get_allocator() const
    {
        return _alloc;
    }

    reference at(size_type pos)
    {
        _range_check(pos);
        return (*this)[pos];
    }

    const_reference at(size_type pos) const
    {
        _range_check(pos);
        return (*this)[pos];
    }

    reference operator[](size_type n)
    {
        return *(_start + n);
    }

    const_reference operator[](size_type n) const
    {
        return *(_start + n);
    }

    reference front()
    {
        return *begin();
    }

    const_reference front() const
    {
        return *begin();
    }

    reference back()
    {
        return *(end() - 1);
    }

    const_reference back() const
    {
        return *(end() - 1);
    }

    T* data()
    {
        return empty() ? NULL : _start;
    }

    const T* data() const
    {
        return empty() ? NULL : _start;
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

    reverse_iterator rbegin()
    {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend()
    {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(begin());
    }

    bool empty() const
    {
        return begin() == end();
    }

    size_type size() const
    {
        return _last - _start;
    }

    size_type max_size() const
    {
        const size_t diff_max = std::numeric_limits<std::ptrdiff_t>::max() / sizeof(value_type);
        const size_t alloc_max = _get_alloc().max_size();
        return std::min(diff_max, alloc_max);
    }

    void reserve(size_type new_cap)
    {
        if (new_cap > max_size())
            throw std::length_error("vector::reserve");
        if (new_cap > capacity())
        {
            const size_type old_size = size();
            iterator temp = _allocate_and_copy(new_cap, _start, _last);
            _destroy_and_deallocate();
            _start = temp;
            _last = temp + old_size;
            _end_of_storage = temp + new_cap;
        }
    }

    size_type capacity() const
    {
        return _end_of_storage - _start;
    }

    void clear()
    {
        _destroy(_start, _last);
        _last = _start;
    }

    iterator insert(iterator pos, const T& value)
    {
        const size_type n = _value_insert(pos, 1, value);
        return _start + n;
    }

    void insert(iterator pos, size_type count, const T& value)
    {
        if (count > 0)
        {
            _value_insert(pos, count, value);
        }
    }

    template<class Iter>
    void insert(iterator pos, Iter start, Iter last)
    {
        typedef typename is_integral<Iter>::type Integral;
        _iter_insert(pos, start, last, Integral());
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
            const size_type old_size = size();
            iterator temp = _allocate_and_copy(old_size + 1, _start, _last);
            _destroy_and_deallocate();
            _start = temp;
            _last = temp + old_size;
            _end_of_storage = temp + old_size + 1;
            _construct(_last, value);
            ++_last;
        }
    }
};
} // namespace ft

#endif

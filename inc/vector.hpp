#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <limits>
#include "iterator.hpp"
#include "is_integral.hpp"
#include "reverse_iterator.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"
#include "alloc_traits.hpp"

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

    class iterator
    {
    private:
        typedef iterator_traits<pointer> traits_type;

    public:
        pointer _current;

        typedef typename traits_type::iterator_category iterator_category;
        typedef typename traits_type::value_type value_type;
        typedef typename traits_type::difference_type difference_type;
        typedef typename traits_type::reference reference;
        typedef typename traits_type::pointer pointer;

        iterator() : _current(NULL) {}
        explicit iterator(const pointer ptr) : _current(ptr) {}

        reference operator*() const {return *_current;}
        pointer operator->() const {return _current;}

        iterator& operator++()
        {
            ++_current;
            return *this;
        }

        iterator operator++(int) {return iterator(_current++);}

        iterator& operator--()
        {
            --_current;
            return *this;
        }

        iterator operator--(int) {return iterator(_current--);}
        reference operator[](difference_type n) const {return _current[n];}

        iterator& operator+=(difference_type n)
        {
            _current += n;
            return *this;
        }

        iterator operator+(difference_type n) {return iterator(_current + n);}

        iterator& operator-=(difference_type n)
        {
            _current -= n;
            return *this;
        }

        iterator operator-(difference_type n) {return iterator(_current - n);}
        bool operator==(const iterator& other) const {return _current == other._current;}
        bool operator!=(const iterator& other) const {return _current != other._current;}
        bool operator<(const iterator& other) const {return _current < other._current;}
        bool operator<=(const iterator& other) const {return _current <= other._current;}
        bool operator>(const iterator& other) const {return _current > other._current;}
        bool operator>=(const iterator& other) const {return _current >= other._current;}
        difference_type operator-(const iterator& other) const {return _current - other._current;}
    };

    class const_iterator
    {
    private:
        typedef iterator_traits<const_pointer> traits_type;

    public:
        const_pointer _current;

        typedef typename traits_type::iterator_category iterator_category;
        typedef typename traits_type::value_type value_type;
        typedef typename traits_type::difference_type difference_type;
        typedef typename traits_type::reference reference;
        typedef typename traits_type::pointer pointer;

        const_iterator() : _current(NULL) {}
        explicit const_iterator(const_pointer ptr) : _current(ptr) {}
        const_iterator(const iterator& iter) : _current(iter._current) {}

        reference operator*() const {return *_current;}
        pointer operator->() const {return _current;}

        const_iterator& operator++()
        {
            ++_current;
            return *this;
        }

        const_iterator operator++(int) {return const_iterator(_current++);}

        const_iterator& operator--()
        {
            --_current;
            return *this;
        }

        const_iterator operator--(int) {return const_iterator(_current--);}
        reference operator[](difference_type n) const {return _current[n];}

        const_iterator& operator+=(difference_type n)
        {
            _current += n;
            return *this;
        }

        const_iterator operator+(difference_type n) {return const_iterator(_current + n);}

        const_iterator& operator-=(difference_type n)
        {
            _current -= n;
            return *this;
        }

        const_iterator operator-(difference_type n) {return const_iterator(_current - n);}
        bool operator==(const const_iterator& other) const {return _current == other._current;}
        bool operator!=(const const_iterator& other) const {return _current != other._current;}
        bool operator<(const const_iterator& other) const {return _current < other._current;}
        bool operator<=(const const_iterator& other) const {return _current <= other._current;}
        bool operator>(const const_iterator& other) const {return _current > other._current;}
        bool operator>=(const const_iterator& other) const {return _current >= other._current;}
        difference_type operator-(const const_iterator& other) const {return _current - other._current;}
    };

    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

private:
    typedef alloc_traits<Alloc> allocator;

    pointer _start;
    pointer _last;
    pointer _end_of_storage;
    Alloc _alloc;

    typename Alloc::template rebind<value_type>::other::size_type
    _alloc_max_size() const
    {
        return allocator::template max_size<value_type>(_alloc);
    }

    template <typename Iter>
    void _destroy(Iter iter)
    {
        allocator::destroy(_alloc, iter);
    }

    void _destroy(pointer start, pointer last)
    {
        for (; start < last; ++start)
            _destroy(start);
    }

    pointer _allocate(size_type n)
    {
        return allocator::template allocate<pointer, size_type>(_alloc, n);
    }

    template <typename Iter, typename V>
    void _construct(Iter iter, const V& value)
    {
        allocator::construct(_alloc, iter, value);
    }

    template <typename Iter>
    void _deallocate(Iter iter, size_type n)
    {
        allocator::deallocate(_alloc, iter, n);
    }

    template<class Iter1, class Iter2>
    Iter2 _copy(Iter1 start, Iter1 last, Iter2 dest)
    {
        for (; start != last; ++start, ++dest)
            *dest = *start;
        return dest;
    }

    template<class Iter1, class Iter2>
    Iter1 _copy(Iter1 start, Iter1 last, Iter2 dest, size_type n)
    {
        for (size_type i = 0; i < n && start != last; ++start, ++dest, ++i)
            *dest = *start;
        return start;
    }

    template<class Iter>
    pointer _reverse_copy(Iter start, Iter last, pointer dest)
    {
        --start;
        --dest;
        --last;
        for (; start != last; --dest, --last)
            *dest = *last;
        return dest;
    }

    pointer _fill_value(pointer dest,
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

    void _construct_by_value(pointer start,
                             size_type n,
                             const value_type& value)
    {
        pointer temp = start;
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
    void _construct_by_iterator(Iter start, Iter last, pointer dest)
    {
        pointer temp = dest;
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
    pointer _allocate_and_copy(size_type n, Iter start, Iter last)
    {
        pointer temp = _allocate(n);
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

    pointer _allocate_and_fill_value(size_type n, const value_type& value)
    {
        pointer temp = _allocate(n);
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
        typename iterator_traits<Iter>::difference_type dist = ft::distance(start, last);
        _start = _allocate_and_copy(dist, start, last);
        _last = _start + dist;
        _end_of_storage = _last;
    }

    void _value_assign(size_type count, const T& value)
    {
        if (count > capacity())
        {
            pointer temp = _allocate_and_fill_value(count, value);
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
        size_type dist = size_type(ft::distance(start, last));
        if (dist > capacity())
        {
            pointer temp = _allocate_and_copy(dist, start, last);
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
        size_type allocate_size = std::min(std::max(total_size, size() * 2), max_size());
        pointer temp = _allocate(allocate_size);
        pointer copied_pos = temp;
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
            _deallocate(temp, allocate_size);
            throw;
        }
        _destroy_and_deallocate();
        _start = temp;
        _last = _start + total_size;
        _end_of_storage = _start + allocate_size;
    }

    void _insert_by_value(size_type pos,
                          const value_type& value,
                          size_type n = 1)
    {
        size_type add_iter_num = std::min(n, size() - pos);
        size_type add_value_num = n - add_iter_num;
        pointer copied_pos = _last;
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
        pointer temp = _allocate(total_size);
        pointer copied_pos = temp;
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
        pointer copied_pos = _last;
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
        const size_type n = pos - iterator(_start);
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
        typename iterator_traits<Iter>::difference_type count = ft::distance(start, last);
        if (count > 0)
        {
            const size_type n = pos - iterator(_start);
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

    template<class U>
    void _swap(U& a, U&b)
    {
        U temp = a;
        a = b;
        b = temp;
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
                pointer temp = _allocate_and_copy(other_len, other._start, other._last);
                _destroy_and_deallocate();
                _start = temp;
                _end_of_storage = temp + other_len;
            }
            else if (size() >= other_len)
            {
                _destroy(_copy(other._start, other._last, _start), _last);
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
        return iterator(_start);
    }

    const_iterator begin() const
    {
        return const_iterator(_start);
    }

    iterator end()
    {
        return iterator(_last);
    }

    const_iterator end() const
    {
        return const_iterator(_last);
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
        const size_t alloc_max = _alloc_max_size();
        return std::min(diff_max, alloc_max);
    }

    void reserve(size_type new_cap)
    {
        if (new_cap > max_size())
            throw std::length_error("vector::reserve");
        if (new_cap > capacity())
        {
            const size_type old_size = size();
            pointer temp = _allocate_and_copy(new_cap, _start, _last);
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
        return iterator(_start + n);
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

    iterator erase(iterator pos)
    {
        _copy(pos + 1, iterator(_last), pos);
        --_last;
        _destroy(_last);
        return pos;
    }

    iterator erase(iterator start, iterator last)
    {
        if (start != last)
        {
            _copy(last, iterator(_last), start);
            _destroy(_last - (last - start), _last);
            _last = _last - (last - start);
        }
        return start;
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
            _realloc_insert_by_value(size(), value);
        }
    }

    void pop_back()
    {
        --_last;
        _destroy(_last);
    }

    void resize(size_type count, T value = T())
    {
        if (count > size())
        {
            _value_insert(iterator(_last), count - size(), value);
        }
        else if (count < size())
        {
            erase(iterator(_last) - (size() - count), iterator(_last));
        }
    }

    void swap(vector& other)
    {
        _swap(_start, other._start);
        _swap(_last, other._last);
        _swap(_end_of_storage, other._end_of_storage);
        _swap(_alloc, other._alloc);
    }
};

template<typename T, typename Alloc>
bool operator==(const vector<T, Alloc>& lhs,
                const vector<T, Alloc>& rhs)
{
    return (lhs.size() == rhs.size() &&
            equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template<typename T, typename Alloc>
bool operator!=(const vector<T, Alloc>& lhs,
                const vector<T, Alloc>& rhs)
{
    return !(lhs == rhs);
}

template<typename T, typename Alloc>
bool operator<(const vector<T, Alloc>& lhs,
               const vector<T, Alloc>& rhs)
{
    return lexicographical_compare(lhs.begin(), lhs.end(),
                                   rhs.begin(), rhs.end());
}

template<typename T, typename Alloc>
bool operator<=(const vector<T, Alloc>& lhs,
                const vector<T, Alloc>& rhs)
{
    return !(rhs < lhs);
}

template<typename T, typename Alloc>
bool operator>(const vector<T, Alloc>& lhs,
               const vector<T, Alloc>& rhs)
{
    return rhs < lhs;
}

template<typename T, typename Alloc>
bool operator>=(const vector<T, Alloc>& lhs,
                const vector<T, Alloc>& rhs)
{
    return !(lhs < rhs);
}

template<typename T, typename Alloc>
void swap(vector<T, Alloc>& lhs,
          vector<T, Alloc>& rhs)
{
    lhs.swap(rhs);
}

template<typename T, typename Alloc>
bool operator==(const typename vector<T, Alloc>::iterator& lhs, const typename vector<T, Alloc>::const_iterator& rhs)
{return lhs._current == rhs._current;}

template<typename T, typename Alloc>
bool operator!=(const typename vector<T, Alloc>::iterator& lhs, const typename vector<T, Alloc>::const_iterator& rhs)
{return lhs._current != rhs._current;}

template<typename T, typename Alloc>
bool operator<(const typename vector<T, Alloc>::iterator& lhs, const typename vector<T, Alloc>::const_iterator& rhs)
{return lhs._current < rhs._current;}

template<typename T, typename Alloc>
bool operator<=(const typename vector<T, Alloc>::iterator& lhs, const typename vector<T, Alloc>::const_iterator& rhs)
{return lhs._current <= rhs._current;}

template<typename T, typename Alloc>
bool operator>(const typename vector<T, Alloc>::iterator& lhs, const typename vector<T, Alloc>::const_iterator& rhs)
{return lhs._current > rhs._current;}

template<typename T, typename Alloc>
bool operator>=(const typename vector<T, Alloc>::iterator& lhs, const typename vector<T, Alloc>::const_iterator& rhs)
{return lhs._current >= rhs._current;}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator
operator+(typename vector<T, Alloc>::iterator::difference_type n, const typename vector<T, Alloc>::iterator& iter)
{return vector<T, Alloc>::iterator(iter._cuurent + n);}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator
operator+(typename vector<T, Alloc>::const_iterator::difference_type n, const typename vector<T, Alloc>::const_iterator& iter)
{return vector<T, Alloc>::const_iterator(iter._cuurent + n);}
} // namespace ft

#endif

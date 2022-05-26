#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <iterator>
#include "iterator_traits.hpp"

namespace ft
{
template<typename Iterator>
class reverse_iterator
    : public std::iterator<typename iterator_traits<Iterator>::iterator_category,
                           typename iterator_traits<Iterator>::value_type,
                           typename iterator_traits<Iterator>::difference_type,
                           typename iterator_traits<Iterator>::pointer,
                           typename iterator_traits<Iterator>::reference>
{
private:
    typedef iterator_traits<Iterator> _traits_type;

protected:
    Iterator current;

public:
    typedef Iterator iterator_type;
    typedef typename _traits_type::iterator_category iterator_category;
    typedef typename _traits_type::value_type value_type;
    typedef typename _traits_type::difference_type difference_type;
    typedef typename _traits_type::pointer pointer;
    typedef typename _traits_type::reference reference;

    reverse_iterator() : current() {}
    explicit reverse_iterator(iterator_type x) : current(x) {}
    template<typename Iter>
    reverse_iterator(const reverse_iterator<Iter>& x) : current(x.base()) {}

    iterator_type base() const
    {
        return current;
    }

    reference operator*() const
    {
        Iterator tmp = current;
        return *--tmp;
    }

    pointer operator->() const
    {
        Iterator tmp = current;
        --tmp;
        return _arrow_support(tmp);
    }

    reference operator[](difference_type n) const
    {
        return *(*this + n);
    }

    reverse_iterator& operator++()
    {
        --current;
        return *this;
    }

    reverse_iterator operator++(int)
    {
        reverse_iterator tmp = *this;
        --current;
        return tmp;
    }

    reverse_iterator& operator--()
    {
        ++current;
        return *this;
    }

    reverse_iterator operator--(int)
    {
        reverse_iterator tmp = *this;
        ++current;
        return tmp;
    }

    reverse_iterator operator+(difference_type n) const
    {
        return reverse_iterator(current - n);
    }

    reverse_iterator& operator+=(difference_type n)
    {
        current -= n;
        return *this;
    }

    reverse_iterator operator-(difference_type n) const
    {
        return reverse_iterator(current + n);
    }

    reverse_iterator& operator-=(difference_type n)
    {
        current += n;
        return *this;
    }

private:
    template<typename T>
    static T* _arrow_support(T* p)
    {
        return p;
    }

    template<typename T>
    static pointer _arrow_support(T t)
    {
        return t.operator->();
    }
};

template<typename Iterator1, typename Iterator2>
bool operator==(const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() == rhs.base();
}

template<typename Iterator1, typename Iterator2>
bool operator<(const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs)
{
    return rhs.base() < lhs.base();
}

template<typename Iterator1, typename Iterator2>
bool operator!=(const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs)
{
    return !(lhs == rhs);
}

template<typename Iterator1, typename Iterator2>
bool operator>(const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs)
{
    return rhs < lhs;
}

template<typename Iterator1, typename Iterator2>
bool operator<=(const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs)
{
    return !(rhs < lhs);
}

template<typename Iterator1, typename Iterator2>
bool operator>=(const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs)
{
    return !(lhs < rhs);
}

template<typename Iterator>
reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
                                     const reverse_iterator<Iterator>& x)
{
    return reverse_iterator<Iterator>(x.base() - n);
}

template<typename Iterator>
typename reverse_iterator<Iterator>::difference_type
    operator-(const reverse_iterator<Iterator>& lhs,
              const reverse_iterator<Iterator>& rhs)
{
    return rhs.base() - lhs.base();
}

} // namespace ft

#endif

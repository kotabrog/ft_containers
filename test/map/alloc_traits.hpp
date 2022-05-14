#ifndef ALLOC_TRAITS_HPP
#define ALLOC_TRAITS_HPP

#include "iterator_traits.hpp"

namespace ft
{
template<typename Alloc>
class alloc_traits
{
public:
    template<typename V>
    static typename Alloc::template rebind<V>::other
    rebind_alloc(const Alloc& alloc)
    {
        return typename Alloc::template rebind<V>::other(alloc);
    }

    template<typename Iter>
    static typename Alloc::template rebind<typename iterator_traits<Iter>::value_type>::other
    rebind_alloc_by_iter(const Alloc& alloc, Iter)
    {
        return typename Alloc::template rebind<typename iterator_traits<Iter>::value_type>::other(alloc);
    }

    template<typename V>
    static typename Alloc::template rebind<V>::other
    rebind_alloc_by_value(const Alloc& alloc, const V&)
    {
        return typename Alloc::template rebind<V>::other(alloc);
    }

    template<typename Pointer>
    static void destroy(const Alloc& alloc, Pointer p)
    {
        rebind_alloc_by_iter(alloc, p).destroy(p);
    }

    template<typename Pointer, typename Size_type>
    static Pointer allocate(const Alloc& alloc, Size_type n)
    {
        if (n == 0)
            return Pointer();
        return rebind_alloc<typename iterator_traits<Pointer>::value_type>(alloc).allocate(n);
    }

    template<typename Pointer, typename V>
    static void construct(const Alloc& alloc,
                          Pointer p,
                          const V& value)
    {
        rebind_alloc_by_iter(alloc, p).construct(p, value);
    }

    template<typename Pointer, typename Size_type>
    static void deallocate(const Alloc& alloc, Pointer p, Size_type n)
    {
        rebind_alloc_by_iter(alloc, p).deallocate(p, n);
    }

    template<typename V>
    static typename Alloc::template rebind<V>::other::size_type
    max_size(const Alloc& alloc)
    {
        return rebind_alloc<V>(alloc).max_size();
    }
};

} // namespace ft

#endif

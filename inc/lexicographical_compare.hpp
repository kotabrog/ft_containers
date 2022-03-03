#ifndef LEXICOGRAPHICAL_COMPARE_HPP
#define LEXICOGRAPHICAL_COMPARE_HPP

namespace ft
{
template <class Iter1, class Iter2>
bool lexicographical_compare(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
    for (; first1 != last1 && first2 != last2; ++first1, ++first2)
    {
        if (*first1 < *first2)
        {
            return true;
        }
        if (*first2 < *first1)
        {
            return false;
        }
    }
    return first1 == last1 && first2 != last2;
}

template <class Iter1, class Iter2, class Compare>
bool lexicographical_compare(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2, Compare comp)
{
    for (; first1 != last1 && first2 != last2; ++first1, ++first2)
    {
        if (comp(*first1, *first2))
        {
            return true;
        }
        if (comp(*first2, *first1))
        {
            return false;
        }
    }
    return first1 == last1 && first2 != last2;
}
} // namespace ft

#endif

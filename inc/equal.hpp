#ifndef EQUAL_HPP
#define EQUAL_HPP

namespace ft
{
template<class Iter1, class Iter2, class BinaryPredicate>
bool equal(Iter1 first1, Iter1 last1, Iter2 first2, BinaryPredicate pred)
{
    for (; first1 != last1; ++first1, ++first2)
    {
        if (!pred(*first1, *first2))
        {
            return false;
        }
    }
    return true;
}

template<class Iter1, class Iter2>
bool equal(Iter1 first1, Iter1 last1, Iter2 first2)
{
    for (; first1 != last1; ++first1, ++first2)
    {
        if (*first1 != *first2)
        {
            return false;
        }
    }
    return true;
}

template<class Iter1, class Iter2, class BinaryPredicate>
bool equal(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2, BinaryPredicate pred)
{
    for (; first1 != last1 && first2 != last2; ++first1, ++first2)
    {
        if (!pred(*first1, *first2))
        {
            return false;
        }
    }
    return first1 == last1 && first2 == last2;
}

template<class Iter1, class Iter2>
bool equal(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
    for (; first1 != last1 && first2 != last2; ++first1, ++first2)
    {
        if (*first1 != *first2)
        {
            return false;
        }
    }
    return first1 == last1 && first2 == last2;
}

} // namespace ft

#endif

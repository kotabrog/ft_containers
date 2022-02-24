#include <iostream>
#include <iterator>
#include <vector>
#include <list>

template<class BidirIt>
void my_reverse(BidirIt first, BidirIt last)
{
    typename std::iterator_traits<BidirIt>::difference_type n = std::distance(first, last);
    for (--n; n > 0; n -= 2) {
        typename std::iterator_traits<BidirIt>::value_type tmp = *first;
        *first++ = *--last;
        *last = tmp;
    }
}

template<class T>
void put_info(T obj)
{
    {
        typedef typename T::iterator Iterator;
        Iterator first = obj.begin();
        Iterator last = obj.end();
        typename std::iterator_traits<Iterator>::difference_type n = last - first;
        // typename std::iterator_traits<Iterator>::difference_type n = std::distance(first, last);
        typename std::iterator_traits<Iterator>::value_type v = *first;
        typename std::iterator_traits<Iterator>::pointer p = &(*first);
        typename std::iterator_traits<Iterator>::reference r = *first;
        typename std::iterator_traits<Iterator>::iterator_category t;
        std::cout << n << std::endl;
        std::cout << v << std::endl;
        std::cout << *p << std::endl;
        std::cout << r << std::endl;
        // std::cout << typeid(t).hash_code() << std::endl; -> プログラム間では同一でないか可能性があるらしい
        if (typeid(t) == typeid(std::random_access_iterator_tag)) std::cout << "t" << std::endl;
        if (typeid(t) == typeid(std::bidirectional_iterator_tag)) std::cout << "n" << std::endl;
    }

    {
        int first = 5;
        int last = 10;
        typename std::iterator_traits<int*>::difference_type n = std::distance(&first, &last);
        typename std::iterator_traits<int*>::value_type v = first;
        typename std::iterator_traits<int*>::pointer p = &first;
        typename std::iterator_traits<int*>::reference r = first;
        typename std::iterator_traits<int*>::iterator_category t;
        std::cout << n << std::endl;
        std::cout << v << std::endl;
        std::cout << *p << std::endl;
        std::cout << r << std::endl;
        if (typeid(t) == typeid(std::random_access_iterator_tag)) std::cout << "t" << std::endl;
        if (typeid(t) == typeid(std::bidirectional_iterator_tag)) std::cout << "n" << std::endl;
    }

    {
        const int first = 5;
        const int last = 10;
        const int dummy = 10;
        typename std::iterator_traits<const int*>::difference_type n = std::distance(&first, &last);
        typename std::iterator_traits<const int*>::value_type v = first;
        typename std::iterator_traits<const int*>::pointer p = &first;
        typename std::iterator_traits<const int*>::reference r = first;
        typename std::iterator_traits<const int*>::iterator_category t;
        std::cout << n << std::endl;
        std::cout << v << std::endl;
        std::cout << *p << std::endl;
        std::cout << r << std::endl;
        if (typeid(t) == typeid(std::random_access_iterator_tag)) std::cout << "t" << std::endl;
        if (typeid(t) == typeid(std::bidirectional_iterator_tag)) std::cout << "n" << std::endl;
        // typename std::iterator_traits<int*>::pointer p = &dummy; compile error
    }


}

int main()
{
    std::vector<int> v{1, 2, 3, 4, 5};
    my_reverse(v.begin(), v.end());
    for (int n : v) {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    std::list<int> l{1, 2, 3, 4, 5};
    my_reverse(l.begin(), l.end());
    for (int n : l) {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    int a[] = {1, 2, 3, 4, 5};
    // my_reverse(a, a + std::size(a));
    my_reverse(a, a + sizeof(a) / sizeof(a[0]));
    for (int n : a) {
        std::cout << n << ' ';
    }
    std::cout << '\n';

//    std::istreambuf_iterator<char> i1(std::cin), i2;
//    my_reverse(i1, i2); // compilation error

    std::vector<int> vec{1, 2, 3, 4, 5};
    put_info(vec);
}

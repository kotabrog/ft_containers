#if FT_EQUAL_STD//CREATE A REAL STL EXAMPLE
    #define STD_FLAG 1
    #include <map>
    #include <stack>
    #include <vector>
    namespace ft = std;
#else
    #define STD_FLAG 0
    #include <vector.hpp>
    #include "reverse_iterator.hpp"
    #include "pair.hpp"
    #include "lexicographical_compare.hpp"
    #include "equal.hpp"
    #include "is_integral.hpp"
    #include "enable_if.hpp"
    #include "iterator_traits.hpp"
    // #include <map.hpp>
    // #include <stack.hpp>
#endif

#include <iostream>
#include <string>
#include <deque>
#include <typeinfo>
#include <stdlib.h>
#include "Tester.hpp"

#include <vector>
#include <map>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
    int idx;
    char buff[BUFFER_SIZE];
};

#define COUNT (MAX_RAM / (int)sizeof(Buffer))

/*
template<typename T>
class MutantStack : public ft::stack<T>
{
public:
    MutantStack() {}
    MutantStack(const MutantStack<T>& src) { *this = src; }
    MutantStack<T>& operator=(const MutantStack<T>& rhs) 
    {
        this->c = rhs.c;
        return *this;
    }
    ~MutantStack() {}

    typedef typename ft::stack<T>::container_type::iterator iterator;

    iterator begin() { return this->c.begin(); }
    iterator end() { return this->c.end(); }
};

void default_test()
{
    tester.print("");
    std::cout << "----------------------" << std::endl;
    std::cout << "default test" << std::endl;
    ft::vector<std::string> vector_str;
    ft::vector<int> vector_int;
    ft::stack<int> stack_int;
    ft::vector<Buffer> vector_buffer;
    ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
    ft::map<int, int> map_int;

    for (int i = 0; i < COUNT; i++)
    {
        vector_buffer.push_back(Buffer());
    }

    for (int i = 0; i < COUNT; i++)
    {
        const int idx = rand() % COUNT;
        vector_buffer[idx].idx = 5;
    }
    ft::vector<Buffer>().swap(vector_buffer);

    try
    {
        for (int i = 0; i < COUNT; i++)
        {
            const int idx = rand() % COUNT;
            vector_buffer.at(idx);
            std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
        }
    }
    catch(const std::exception& e)
    {
        //NORMAL ! :P
    }

    for (int i = 0; i < COUNT; ++i)
    {
        map_int.insert(ft::make_pair(rand(), rand()));
    }

    int sum = 0;
    for (int i = 0; i < 10000; i++)
    {
        int access = rand();
        sum += map_int[access];
    }
    std::cout << "should be constant with the same seed: " << sum << std::endl;

    {
        ft::map<int, int> copy = map_int;
    }
    MutantStack<char> iterable_stack;
    for (char letter = 'a'; letter <= 'z'; letter++)
        iterable_stack.push(letter);
    for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
    {
        std::cout << *it;
    }
    std::cout << std::endl;
}
*/

void iterators_traits_test()
{
    Tester tester;
    tester.print("");
    tester.print("----------------------");
    tester.print("iterators_traits test");
    {
        tester.print("");
        tester.print("template< class Iter > struct iterator_traits");
        std::vector<int> vec;
        for (int i = 0; i < 5; i++)
        {
            vec.push_back(rand());
        }
        // typedef ft::vector<int>::iterator Iterator;
        typedef std::vector<int>::iterator Iterator;
        Iterator first = vec.begin();
        Iterator last = vec.end();
        ft::iterator_traits<Iterator>::difference_type n = last - first;
        ft::iterator_traits<Iterator>::value_type v = *first;
        ft::iterator_traits<Iterator>::pointer p = &(*first);
        ft::iterator_traits<Iterator>::reference r = *first;
        ft::iterator_traits<Iterator>::iterator_category t;
        tester.print("difference_type value:", n);
        tester.print("value_type value:", v);
        tester.print("pointer value:", *p);
        tester.print("reference value:", r);
        tester.if_print("iterator_category:",
                        typeid(t) == typeid(std::random_access_iterator_tag),
                        "random_access_iterator_tag",
                        "other type");
    }
    {
        tester.print("");
        tester.print("template< class T > struct iterator_traits<T*>");
        int vec[2];
        for (int i = 0; i < 2; i++)
        {
            vec[i] = rand();
        }
        ft::iterator_traits<int*>::difference_type n = &(vec[1]) - &(vec[0]);
        ft::iterator_traits<int*>::value_type v = vec[0];
        ft::iterator_traits<int*>::pointer p = &(vec[0]);
        ft::iterator_traits<int*>::reference r = vec[0];
        ft::iterator_traits<int*>::iterator_category t;
        tester.print("difference_type value:", n);
        tester.print("value_type value:", v);
        tester.print("pointer value:", *p);
        tester.print("reference value:", r);
        tester.if_print("iterator_category:",
                        typeid(t) == typeid(std::random_access_iterator_tag),
                        "random_access_iterator_tag",
                        "other type");
    }
    {
        tester.print("");
        tester.print("template< class T > struct iterator_traits<const T*>");
        const int value = rand();
        ft::iterator_traits<const int*>::value_type v = value;
        ft::iterator_traits<const int*>::pointer p = &(value);
        ft::iterator_traits<const int*>::reference r = value;
        ft::iterator_traits<const int*>::iterator_category t;
        tester.print("value_type value:", v);
        tester.print("pointer value:", *p);
        tester.print("reference value:", r);
        tester.if_print("iterator_category:",
                        typeid(t) == typeid(std::random_access_iterator_tag),
                        "random_access_iterator_tag",
                        "other type");
        // The following will result in a compilation error
        // const int dummy = rand();
        // ft::iterator_traits<int*>::reference error = dummy;
        // tester.print("compile error:", error);
    }
}

template<typename T>
void enable_if_test_support(T t1, typename ft::enable_if<true, T>::type t2, Tester& tester)
{
    tester.print("value1:", t1);
    tester.print("value2:", t2);

    if (typeid(int) == typeid(typename ft::enable_if<true, T>::type))
        tester.print("type: int");
    else if (typeid(std::string) == typeid(typename ft::enable_if<true, T>::type))
        tester.print("type: std::string");
}

template<typename T>
void enable_if_test_support(T t1, typename ft::enable_if<false, T>::type t2, Tester& tester)
{
    tester.print("error:", t1);
    tester.print("error:", t2);
}

void enable_if_test()
{
    Tester tester;
    tester.print("");
    tester.print("----------------------");
    tester.print("enable_if test");
    {
        tester.print("");
        enable_if_test_support(1, 2, tester);
    }
    {
        std::string str = "string";
        tester.print("");
        enable_if_test_support(str, str, tester);
    }
    {
        tester.print("");
        if (typeid(ft::enable_if<true>::type) == typeid(void))
            tester.print("enable_if default type: void");
        else
            tester.print("enable_if default type: other");
    }
}

void is_integral_test()
{
    Tester tester;
    tester.print("");
    tester.print("----------------------");
    tester.print("is_integral test");
    tester.print("ft::is_integral<int>::value:", ft::is_integral<int>::value);
    tester.print("ft::is_integral<int>():", ft::is_integral<int>());
    tester.print("ft::is_integral<int>::type::value:", ft::is_integral<int>::type::value);
    tester.if_print("ft::is_integral<int>::value_type:", (typeid(ft::is_integral<int>::value_type) == typeid(bool)), "bool", "other");
    tester.if_print("bool:", ft::is_integral<bool>::value, "true", "false");
    tester.if_print("char:", ft::is_integral<char>::value, "true", "false");
    tester.if_print("wchar_t:", ft::is_integral<wchar_t>::value, "true", "false");
    tester.if_print("short:", ft::is_integral<short>::value, "true", "false");
    tester.if_print("int:", ft::is_integral<int>::value, "true", "false");
    tester.if_print("long:", ft::is_integral<long>::value, "true", "false");
    tester.if_print("signed char:", ft::is_integral<signed char>::value, "true", "false");
    tester.if_print("unsigned char:", ft::is_integral<unsigned char>::value, "true", "false");
    tester.if_print("unsigned short:", ft::is_integral<unsigned short>::value, "true", "false");
    tester.if_print("unsigned int:", ft::is_integral<unsigned int>::value, "true", "false");
    tester.if_print("unsigned long:", ft::is_integral<unsigned long>::value, "true", "false");
    tester.if_print("bool:", ft::is_integral<bool>::value, "true", "false");
    tester.if_print("const unsigned long:", ft::is_integral<const unsigned long>::value, "true", "false");
    tester.if_print("volatile unsigned long:", ft::is_integral<volatile unsigned long>::value, "true", "false");
    tester.if_print("const volatile unsigned long:", ft::is_integral<const volatile unsigned long>::value, "true", "false");
    tester.if_print("Tester:", ft::is_integral<Tester>::value, "true", "false");
    tester.if_print("const Tester:", ft::is_integral<const Tester>::value, "true", "false");
    tester.if_print("int*:", ft::is_integral<int*>::value, "true", "false");
}

bool equal_test_support(int x, int y)
{
    return x - 1 <= y && y <= x + 1;
}

void equal_test()
{
    Tester tester;
    tester.print("");
    tester.print("----------------------");
    tester.print("equal test");
    std::vector<int> v1;
    std::vector<int> v2;
    for (int i = 0; i < 6; ++i)
    {
        v1.push_back(i);
        v2.push_back(i);
    }
    v2[5] += 1;
    tester.if_print("v1:[0,1,2,3,4,5], v2:[0,1,2,3,4,6], ft::equal(v1.begin(), v1.end(), v2.begin()):",
                    ft::equal(v1.begin(), v1.end(), v2.begin()), "true", "false");
    tester.if_print("equal_test_support: return x - 1 <= y && y <= x + 1;,\n\tft::equal(v1.begin(), v1.end(), v2.begin(), equal_test_support):",
                    ft::equal(v1.begin(), v1.end(), v2.begin(), equal_test_support), "true", "false");
    v2[5] -= 1;
    tester.if_print("v1:[0,1,2,3,4,5], v2:[0,1,2,3,4,5], ft::equal(v1.begin(), v1.end(), v2.begin()):",
                    ft::equal(v1.begin(), v1.end(), v2.begin()), "true", "false");
    tester.if_print("v1:[0,1,2,3,4,5], v2:[0,1,2,3,4,5], ft::equal(v1.begin(), v1.end(), v2.begin(), v2.end()):",
                    ft::equal(v1.begin(), v1.end(), v2.begin(), v2.end()), "true", "false");
    v2.push_back(6);
    tester.if_print("v1:[0,1,2,3,4,5], v2:[0,1,2,3,4,5,6], ft::equal(v1.begin(), v1.end(), v2.begin()):",
                    ft::equal(v1.begin(), v1.end(), v2.begin()), "true", "false");
    tester.if_print("v1:[0,1,2,3,4,5], v2:[0,1,2,3,4,5,6], ft::equal(v1.begin(), v1.end(), v2.begin(), v2.end()):",
                    ft::equal(v1.begin(), v1.end(), v2.begin(), v2.end()), "true", "false");
    tester.if_print("v1:[0,1,2,3,4,5], v2:[0,1,2,3,4,5,6], ft::equal(v2.begin(), v2.end(), v1.begin()):",
                    ft::equal(v2.begin(), v2.end(), v1.begin()), "true", "false");
}

void lexicographical_test()
{
    Tester tester;
    tester.print("");
    tester.print("----------------------");
    tester.print("lexicographical test");
    std::string str1 = "hello";
    std::string str2 = "hellO";
    std::string str3 = "hellooo";
    tester.if_print("hello and hellO default:",
                    std::lexicographical_compare(str1.begin(), str1.end(), str2.begin(), str2.end()),
                    "true", "false");
    tester.if_print("hello and hellooo default:",
                    std::lexicographical_compare(str1.begin(), str1.end(), str3.begin(), str3.end()),
                    "true", "false");
    tester.if_print("hellO and hello default:",
                    std::lexicographical_compare(str2.begin(), str2.end(), str1.begin(), str1.end()),
                    "true", "false");
    tester.if_print("hellooo and hello default:",
                    std::lexicographical_compare(str3.begin(), str3.end(), str1.begin(), str1.end()),
                    "true", "false");
    tester.if_print("hello and hellO greater:",
                    std::lexicographical_compare(str1.begin(), str1.end(), str2.begin(), str2.end(), std::greater<char>()),
                    "true", "false");
    tester.if_print("hello and hellooo greater:",
                    std::lexicographical_compare(str1.begin(), str1.end(), str3.begin(), str3.end(), std::greater<char>()),
                    "true", "false");
    tester.if_print("hellO and hello greater:",
                    std::lexicographical_compare(str2.begin(), str2.end(), str1.begin(), str1.end(), std::greater<char>()),
                    "true", "false");
    tester.if_print("hellooo and hello greater:",
                    std::lexicographical_compare(str3.begin(), str3.end(), str1.begin(), str1.end(), std::greater<char>()),
                    "true", "false");
}

void pair_test()
{
    Tester tester;
    tester.print("");
    tester.print("----------------------");
    tester.print("pair test");
    ft::pair<int, std::string> p1;
    ft::pair<int, std::string> p2(1, "hello");
    ft::pair<int, std::string> p3(p2);
    ft::pair<int, std::string> p4(1, "hoy");
    tester.if_print("first_type is int:", typeid(ft::pair<int, std::string>::first_type) == typeid(int), "true", "false");
    tester.if_print("second_type is string:", typeid(ft::pair<int, std::string>::second_type) == typeid(std::string), "true", "false");
    tester.print("ft::pair<int, std::string> p1");
    tester.print("p1.first:", p1.first);
    tester.print("p1.second:", p1.second);
    tester.print("ft::pair<int, std::string> p2(1, \"hello\")");
    tester.print("p2.first:", p2.first);
    tester.print("p2.second:", p2.second);
    tester.print("ft::pair<int, std::string> p3(p2)");
    tester.print("p3.first:", p3.first);
    tester.print("p3.second:", p3.second);
    tester.print("ft::pair<int, std::string> p4(1, \"hoy\")");
    tester.print("p4.first:", p4.first);
    tester.print("p4.second:", p4.second);
    p3 = p1;
    tester.print("p3 = p1");
    tester.print("p3.first:", p3.first);
    tester.print("p3.second:", p3.second);
    tester.print("compare");
    tester.if_print("p1 == p2:", p1 == p2, "true", "false");
    tester.if_print("p1 != p2:", p1 != p2, "true", "false");
    tester.if_print("p1 < p2:", p1 < p2, "true", "false");
    tester.if_print("p1 <= p2:", p1 <= p2, "true", "false");
    tester.if_print("p1 > p2:", p1 > p2, "true", "false");
    tester.if_print("p1 >= p2:", p1 >= p2, "true", "false");
    tester.if_print("p1 == p2:", p1 == p2, "true", "false");
    tester.if_print("p4 != p2:", p4 != p2, "true", "false");
    tester.if_print("p4 < p2:", p4 < p2, "true", "false");
    tester.if_print("p4 <= p2:", p4 <= p2, "true", "false");
    tester.if_print("p4 > p2:", p4 > p2, "true", "false");
    tester.if_print("p4 >= p2:", p4 >= p2, "true", "false");
    // The following will result in a compilation error
    // ft::pair<int, const std::string> p5(p1);
    // tester.if_print("p1 == p5:", p1 == p5, "true", "false");
}

void make_pair_test()
{
    Tester tester;
    tester.print("");
    tester.print("----------------------");
    tester.print("make_pair test");
    ft::pair<int, std::string> p1;
    p1 = ft::make_pair(1, "string");
    const int value = 10;
    ft::pair<const int, int> p2 = ft::make_pair(value, 10);
    tester.print("ft::make_pair(1, \"string\")");
    tester.print("first:", p1.first);
    tester.print("second:", p1.second);
    tester.print("ft::make_pair(value, 10), value(=10) is const int");
    tester.print("first:", p2.first);
    tester.print("second:", p2.second);
}

void reverse_iterator_test()
{
    Tester tester;
    tester.print("");
    tester.print("----------------------");
    tester.print("reverse_iterator test");
    tester.print("");
    tester.print("member types test");
    tester.print("std::reverse_iterator<std::vector<int>::iterator>");
    tester.if_print("iterator_type:",
                    typeid(ft::reverse_iterator<std::vector<int>::iterator>::iterator_type) == typeid(std::vector<int>::iterator),
                    "std::vector<int>::iterator", "other");
    tester.if_print("iterator_category:",
                    typeid(ft::reverse_iterator<std::vector<int>::iterator>::iterator_category) == typeid(std::iterator_traits<std::vector<int>::iterator>::iterator_category),
                    "std::iterator_traits<std::vector<int>::iterator>::iterator_category", "other");
    tester.if_print("value_type:",
                    typeid(ft::reverse_iterator<std::vector<int>::iterator>::value_type) == typeid(std::iterator_traits<std::vector<int>::iterator>::value_type),
                    "std::iterator_traits<std::vector<int>::iterator>::value_type", "other");
    tester.if_print("difference_type:",
                    typeid(ft::reverse_iterator<std::vector<int>::iterator>::difference_type) == typeid(std::iterator_traits<std::vector<int>::iterator>::difference_type),
                    "std::iterator_traits<std::vector<int>::iterator>::difference_type", "other");
    tester.if_print("pointer:",
                    typeid(ft::reverse_iterator<std::vector<int>::iterator>::pointer) == typeid(std::iterator_traits<std::vector<int>::iterator>::pointer),
                    "std::iterator_traits<std::vector<int>::iterator>::pointer", "other");
    tester.if_print("reference:",
                    typeid(ft::reverse_iterator<std::vector<int>::iterator>::reference) == typeid(std::iterator_traits<std::vector<int>::iterator>::reference),
                    "std::iterator_traits<std::vector<int>::iterator>::reference", "other");
    tester.print("");
    tester.print("member function test");
    std::vector<int> vec1;
    for (int i = 0; i < 5; ++i)
    {
        vec1.push_back(i);
        tester.print("vec", i, vec1[i]);
    }
    tester.print("");
    tester.print("constructor test");
    {
        ft::reverse_iterator<std::vector<int>::iterator> ri1;
        ft::reverse_iterator<std::vector<int>::iterator> ri2(vec1.begin());
        ft::reverse_iterator<std::vector<int>::iterator> ri3(vec1.end());
        ft::reverse_iterator<std::vector<int>::iterator> ri4(ri2);
        tester.print("std::reverse_iterator<std::vector<int>::iterator> ri(vec.rbegin())");
        int index = 0;
        for (; ri3 != ri4; ++ri3)
        {
            tester.print("*ri", index++, *ri3);
        }
    }
    tester.print("");
    tester.print("operator= test");
    {
        ft::reverse_iterator<std::vector<int>::iterator> ri1(vec1.end());
        ft::reverse_iterator<std::vector<int>::iterator> ri2;
        ri2 = ri1;
        tester.if_print("ri1 = vec.end(), ri2 = ri1 ->", ri2 == ri1, "ri2 == ri1", "ri2 != ri1");
    }
    tester.print("");
    tester.print("base test");
    {
        ft::reverse_iterator<std::vector<int>::iterator> ri(vec1.begin() + 1);
        tester.if_print("ri = vec.begin() + 1 ->", vec1.begin() + 1 == ri.base(), "ri.base() == vec.begin() + 1", "ri.base() != vec.begin() + 1");
    }
    tester.print("");
    tester.print("operator*, -> test");
    {

        ft::reverse_iterator<std::vector<int>::iterator> ri1(vec1.end());
        tester.print("ri = vec.end(), *ri", *ri1);
        std::map<int, int> map1;
        map1[0] = 1;
        ft::reverse_iterator<std::map<int, int>::iterator> ri2(map1.begin());
        tester.print("std::map<int, int> map1, map1[0] = 1");
        tester.print("map ri->first:", ri2->first);
        tester.print("map ri->second:", ri2->second);
    }
    tester.print("");
    tester.print("[] test");
    {
        ft::reverse_iterator<std::vector<int>::iterator> ri(vec1.end());
        for (std::size_t i = 0; i != vec1.size(); ++i)
        {
            tester.print("ri[i]:", i, ri[i]);
        }
    }
    tester.print("");
    tester.print("operator++, +=, +, --, -=, - test");
    {
        ft::reverse_iterator<std::vector<int>::iterator> ri(vec1.end());
        tester.print("*ri++:", *ri++);
        tester.print("*ri--:", *ri--);
        tester.print("*ri:", *ri);
        tester.print("*++ri:", *++ri);
        tester.print("*--ri:", *--ri);
        ri = ri + 2;
        tester.print("ri = ri + 2, *ri:", *ri);
        ri = ri - 1;
        tester.print("ri = ri - 1, *ri:", *ri);
        ri += 1;
        tester.print("ri += 1, *ri:", *ri);
        ri -= 2;
        tester.print("ri -= 2, *ri:", *ri);
    }
    tester.print("");
    tester.print("non member function test");
    tester.print("operator==, !=, <, <=, <, >= test");
    {
        ft::reverse_iterator<std::vector<int>::iterator> ri1(vec1.end());
        ft::reverse_iterator<std::vector<int>::iterator> x = ri1;
        ft::reverse_iterator<std::vector<int>::iterator> y = ri1;
        ft::reverse_iterator<std::vector<int>::iterator> z = ri1 + 2;
        std::vector<int> vec2(vec1);
        ft::reverse_iterator<std::vector<int>::const_iterator> ri2(vec2.end());
        ft::reverse_iterator<std::vector<int>::const_iterator> x2 = ri2;
        tester.print("ri1 = vec.end()");
        tester.print("x = ri1");
        tester.print("y = ri1");
        tester.print("z = ri1 + 2");
        tester.print("vec2 = vec");
        tester.print("ri2 = vec2.end()");
        tester.print("x2 = ri2");
        tester.print("*x ==", *x);
        tester.print("*y ==", *y);
        tester.print("*z ==", *z);
        tester.print("*x2 ==", *x2);
        tester.if_print("x == y:", x == y, "true", "false");
        tester.if_print("x != y:", x != y, "true", "false");
        tester.if_print("x <  y:", x <  y, "true", "false");
        tester.if_print("x <= y:", x <= y, "true", "false");
        tester.if_print("x == z:", x == z, "true", "false");
        tester.if_print("x != z:", x != z, "true", "false");
        tester.if_print("x <  z:", x <  z, "true", "false");
        tester.if_print("x <= z:", x <= z, "true", "false");
        tester.if_print("x2 == y:", x2 == y, "true", "false");
        tester.if_print("x2 != y:", x2 != y, "true", "false");
        tester.if_print("x2 <  y:", x2 <  y, "true", "false");
        tester.if_print("x2 <= y:", x2 <= y, "true", "false");
        tester.if_print("x2 == z:", x2 == z, "true", "false");
        tester.if_print("x2 != z:", x2 != z, "true", "false");
        tester.if_print("x2 <  z:", x2 <  z, "true", "false");
        tester.if_print("x2 <= z:", x2 <= z, "true", "false");
    }
    tester.print("");
    tester.print("operator+ test");
    {
        ft::reverse_iterator<std::vector<int>::iterator> ri(vec1.end());
        ri = 2 + ri;
        tester.print("ri = 2 + ri, *ri:", *ri);
    }
    tester.print("");
    tester.print("operator- test");
    {
        ft::reverse_iterator<std::vector<int>::iterator> ri1(vec1.begin());
        ft::reverse_iterator<std::vector<int>::iterator> ri2(vec1.end());
        tester.print("ri1 = vec.begin(), ri2 = vec1.end()");
        tester.print("ri1 - ri2:", ri1 - ri2);
    }
}

class Test
{
private:
    int data;
    Tester tester;
public:
    Test() : data(0) {tester.print("construct:", data);}
    Test(int x) : data(x) {tester.print("construct:", data);}
    Test(const Test& temp) : data(temp.data) {tester.print("construct:", data);}
    Test& operator=(const Test& temp) {this->data = temp.data; return *this;}
    ~Test() {tester.print("destruct:", data);}

    int get_data() const {return data;}
};

class ErrorTest
{
private:
    int data;
    Tester tester;
public:
    static int init_num;
    ErrorTest() : data(0)
    {
        if (init_num++ % 3 == 0)
            throw std::bad_alloc();
        tester.print("construct:", data);
    }
    ErrorTest(int x) : data(x)
    {
        if (init_num++ % 3 == 0)
            throw std::bad_alloc();
        tester.print("construct:", data);
    }
    ErrorTest(const ErrorTest& temp) : data(temp.data)
    {
        if (init_num++ % 3 == 0)
            throw std::bad_alloc();
        tester.print("construct:", data);
    }
    ErrorTest& operator=(const ErrorTest& temp) {this->data = temp.data; return *this;}
    ~ErrorTest() {tester.print("destruct:", data);}

    int get_data() const {return data;}
};

int ErrorTest::init_num = 0;

template<class T>
class ErrorAlocator : public std::allocator<T>
{
public:
    template <typename U>
    struct rebind {
        typedef ErrorAlocator<U> other;
    };

    static int construct_num;
    void construct(typename std::allocator<T>::pointer p, const T& value)
    {
        if (construct_num++ % 3 == 0)
            throw std::bad_alloc();
        new((void*)p) T(value);
    }
};

template<typename Test>
int ErrorAlocator<Test>::construct_num = 1;

void vector_test()
{
    Tester tester;
    tester.print("");
    tester.print("----------------------");
    tester.print("vector test");
    tester.print("");
    tester.print("member types test");
    tester.print("ft::vector<int>");
    tester.if_print("value_type:",
                    typeid(ft::vector<int>::value_type) == typeid(int), "int", "other");
    tester.if_print("allocator_type:",
                    typeid(ft::vector<int>::allocator_type) == typeid(std::allocator<int>),
                    "std::allocator<int>", "other");
    tester.if_print("allocator_type:",
                    typeid(ft::vector<int>::size_type) == typeid(std::size_t),
                    "std::size_t", "other");
    tester.if_print("difference_type:",
                    typeid(ft::vector<int>::difference_type) == typeid(std::ptrdiff_t),
                    "std::ptrdiff_t", "other");
    tester.if_print("reference:",
                    typeid(ft::vector<int>::reference) == typeid(ft::vector<int>::value_type&),
                    "ft::vector<int>::value_type&", "other");
    tester.if_print("const_reference:",
                    typeid(ft::vector<int>::const_reference) == typeid(const ft::vector<int>::value_type&),
                    "const ft::vector<int>::value_type&", "other");
    tester.if_print("pointer:",
                    typeid(ft::vector<int>::pointer) == typeid(std::allocator<int>::pointer),
                    "std::allocator<int>::pointer", "other");
    tester.if_print("const_pointer:",
                    typeid(ft::vector<int>::const_pointer) == typeid(std::allocator<int>::const_pointer),
                    "std::allocator<int>::const_pointer", "other");
    tester.print("std::vector<int>::iterator");
    tester.if_print("difference_type:",
                    typeid(ft::iterator_traits<ft::vector<int>::iterator>::difference_type) == typeid(std::ptrdiff_t),
                    "std::ptrdiff_t", "other");
    tester.if_print("value_type:",
                    typeid(ft::iterator_traits<ft::vector<int>::iterator>::value_type) == typeid(int),
                    "int", "other");
    tester.if_print("pointer:",
                    typeid(ft::iterator_traits<ft::vector<int>::iterator>::pointer) == typeid(int*),
                    "int*", "other");
    tester.if_print("reference:",
                    typeid(ft::iterator_traits<ft::vector<int>::iterator>::reference) == typeid(int&),
                    "int&", "other");
    tester.if_print("iterator_category:",
                    typeid(ft::iterator_traits<ft::vector<int>::iterator>::iterator_category) == typeid(std::random_access_iterator_tag),
                    "std::random_access_iterator_tag", "other");
    tester.print("std::vector<int>::const_iterator");
    tester.if_print("difference_type:",
                    typeid(ft::iterator_traits<ft::vector<int>::const_iterator>::difference_type) == typeid(std::ptrdiff_t),
                    "std::ptrdiff_t", "other");
    tester.if_print("value_type:",
                    typeid(ft::iterator_traits<ft::vector<int>::const_iterator>::value_type) == typeid(int),
                    "int", "other");
    tester.if_print("pointer:",
                    typeid(ft::iterator_traits<ft::vector<int>::const_iterator>::pointer) == typeid(const int*),
                    "int*", "other");
    tester.if_print("reference:",
                    typeid(ft::iterator_traits<ft::vector<int>::const_iterator>::reference) == typeid(const int&),
                    "int&", "other");
    tester.if_print("iterator_category:",
                    typeid(ft::iterator_traits<ft::vector<int>::const_iterator>::iterator_category) == typeid(std::random_access_iterator_tag),
                    "std::random_access_iterator_tag", "other");
    tester.if_print("reverse_iterator:",
                    typeid(ft::vector<int>::reverse_iterator) == typeid(ft::reverse_iterator<ft::vector<int>::iterator>),
                    "ft::reverse_iterator<ft::vector<int>::iterator>", "other");
    tester.if_print("const_reverse_iterator:",
                    typeid(ft::vector<int>::const_reverse_iterator) == typeid(ft::reverse_iterator<ft::vector<int>::const_iterator>),
                    "ft::reverse_iterator<ft::vector<int>::const_iterator>", "other");
    tester.print("");
    tester.print("member functions test\n");
    tester.print("test class is a wrapper for int\n");
    tester.print("constructor and destructor test");
    {
        ft::vector<Test> vec;
        tester.print("std::vector<Test> vec; vec.size() ->", vec.size());
    }
    tester.print("");
    {
        std::allocator<Test> alloc;
        ft::vector<Test> vec(alloc);
        std::allocator<Test> temp = vec.get_allocator();
        tester.if_print("ft::vector<Test> vec(alloc); vec.get_allocator() == alloc:",
                        alloc == temp, "true", "false");
    }
    tester.print("");
    {
        tester.print("ft::vector<Test> vec(count);");
        int count = 3;
        tester.print("count:", count);
#if STD_FLAG
        ft::vector<Test> vec(count, Test());
#else
        ft::vector<Test> vec(count);
#endif
        tester.print("vec.size():", vec.size());
        tester.print("vec.capacity():", vec.capacity());
        for (int i = 0; i < count; ++i)
            tester.set_stream(vec[i].get_data());
        tester.put_all_stream();
    }
    tester.print("");
    {
        tester.print("ft::vector<Test> vec(count, value);");
        int count = 3;
        Test value(1);
        tester.print("count:", count);
        tester.print("value:", value.get_data());
        ft::vector<Test> vec(count, value);
        tester.print("vec.size():", vec.size());
        tester.print("vec.capacity():", vec.capacity());
        for (int i = 0; i < count; ++i)
            tester.set_stream(vec[i].get_data());
        tester.put_all_stream();
    }
    tester.print("");
    {
        tester.print("ft::vector<Test> vec(count, value, alloc);");
        std::allocator<Test> alloc;
        int count = 3;
        Test value(1);
        tester.print("count:", count);
        tester.print("value:", value.get_data());
        ft::vector<Test> vec(count, value, alloc);
        tester.print("vec.size():", vec.size());
        tester.print("vec.capacity():", vec.capacity());
        tester.if_print("vec.get_allocator() == alloc:",
                        alloc == vec.get_allocator(), "true", "false");
        for (int i = 0; i < count; ++i)
            tester.set_stream(vec[i].get_data());
        tester.put_all_stream();
    }
    /*
    allocater.construct内でエラーが起きるためaborteで終了する
    tester.print("");
    {
        tester.print("ft::vector<ErrorTest> vec(count, value); error test");
        int count = 3;
        ErrorTest value(1);
        tester.print("count:", count);
        tester.print("value:", value.get_data());
        try
        {
            ft::vector<ErrorTest> vec(count, value);
        }
        catch (const std::exception& e)
        {
            tester.print(e.what());
        }
    }
    */
    tester.print("");
    {
        tester.print("ft::vector<Test> vec(count, value, alloc); error test");
        int count = 4;
        Test value(1);
        ErrorAlocator<Test> alloc;
        tester.print("count:", count);
        tester.print("value:", value.get_data());
        try
        {
            ft::vector<Test, ErrorAlocator<Test> > vec(count, value, alloc);
        }
        catch (const std::exception& e)
        {
            tester.print(e.what());
        }
    }
    tester.print("");
    {
        tester.print("ft::vector<Test> vec2(vec1.begin(), vec1.end());");
        tester.print("ft::vector<Test> vec1(5, Test(3));");
        ft::vector<Test> vec1(5, Test(3));
        ft::vector<Test> vec2(vec1.begin(), vec1.end());
        tester.print("vec2.size():", vec2.size());
        tester.print("vec2.capacity():", vec2.capacity());
        for (std::size_t i = 0; i < vec2.size(); ++i)
            tester.set_stream(vec2[i].get_data());
        tester.put_all_stream();
    }
    tester.print("");
    {
        tester.print("ft::vector<int> vec2(vec1.begin(), vec1.end());");
        tester.print("ft::vector<int> vec1(5, 3);");
        ft::vector<int> vec1(5, 3);
        ft::vector<int> vec2(vec1.begin(), vec1.end());
        tester.print("vec2.size():", vec2.size());
        tester.print("vec2.capacity():", vec2.capacity());
        for (std::size_t i = 0; i < vec2.size(); ++i)
            tester.set_stream(vec2[i]);
        tester.put_all_stream();
        vec2[0] = 4;
        tester.print("change value vec2[0] = 4 -> vec1[0] vec2[]", vec1[0], vec2[0]);
    }
    /*
    コンストラクタが余分に呼ばれてしまう。
    allocatorのconstructを使用する限り避けられない？
    tester.print("");
    {
        tester.print("ft::vector<Test> vec2(vec1.begin(), vec1.end());");
        tester.print("ft::vector<int> vec1(2, 3);");
        ft::vector<int> vec1(2, 3);
        ft::vector<Test> vec2(vec1.begin(), vec1.end());
        tester.print("vec2.size():", vec2.size());
        tester.print("vec2.capacity():", vec2.capacity());
        for (std::size_t i = 0; i < vec2.size(); ++i)
            tester.set_stream(vec2[i].get_data());
        tester.put_all_stream();
        vec2[0] = 4;
        tester.print("change value vec2[0] = 4 -> vec1[0] vec2[]", vec1[0], vec2[0].get_data());
    }
    */
    tester.print("");
    {
        tester.print("ft::vector<Test> vec2(vec1.begin(), vec1.end(), alloc);");
        tester.print("ft::vector<Test> vec1(5, Test(3));");
        ft::vector<Test> vec1(5, Test(3));
        std::allocator<Test> alloc;
        ft::vector<Test> vec2(vec1.begin(), vec1.end(), alloc);
        tester.print("vec2.size():", vec2.size());
        tester.print("vec2.capacity():", vec2.capacity());
        tester.if_print("vec2.get_allocator() == alloc:",
                        alloc == vec2.get_allocator(), "true", "false");
        for (std::size_t i = 0; i < vec2.size(); ++i)
            tester.set_stream(vec2[i].get_data());
        tester.put_all_stream();
    }
    tester.print("");
    {
        tester.print("ft::vector<Test> vec2(vec1);");
        tester.print("ft::vector<Test> vec1(2, Test(3));");
        ft::vector<Test> vec1(2, Test(3));
        ft::vector<Test> vec2(vec1);
        tester.print("vec2.size():", vec2.size());
        tester.print("vec2.capacity():", vec2.capacity());
        for (std::size_t i = 0; i < vec2.size(); ++i)
            tester.set_stream(vec2[i].get_data());
        tester.put_all_stream();
        vec2[0] = 4;
        tester.print("change value vec2[0] = 4 -> vec1[0] vec2[]", vec1[0].get_data(), vec2[0].get_data());
        tester.if_print("vec1.get_allocator() == vec2.get_allocator():",
                        vec1.get_allocator() == vec2.get_allocator(), "true", "false");
    }
    tester.print("");
    {
        tester.print("ft::vector<Test> vec2(vec1);");
        tester.print("const ft::vector<Test> vec1(2, Test(3));");
        const ft::vector<Test> vec1(2, Test(3));
        ft::vector<Test> vec2(vec1);
        tester.print("vec2.size():", vec2.size());
        tester.print("vec2.capacity():", vec2.capacity());
        for (std::size_t i = 0; i < vec2.size(); ++i)
            tester.set_stream(vec2[i].get_data());
        tester.put_all_stream();
        vec2[0] = 4;
        tester.print("change value vec2[0] = 4 -> vec1[0] vec2[]", vec1[0].get_data(), vec2[0].get_data());
        tester.if_print("vec1.get_allocator() == vec2.get_allocator():",
                        vec1.get_allocator() == vec2.get_allocator(), "true", "false");
    }
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./test seed" << std::endl;
        std::cerr << "Provide a seed please" << std::endl;
        std::cerr << "Count value:" << COUNT << std::endl;
        return 1;
    }
    const int seed = atoi(argv[1]);
    srand(seed);

    Tester tester;
    tester.print("test start");

    // default_test();
    // iterators_traits_test();
    // enable_if_test();
    // is_integral_test();
    // equal_test();
    // lexicographical_test();
    // pair_test();
    // make_pair_test();
    // reverse_iterator_test();
    vector_test();
}

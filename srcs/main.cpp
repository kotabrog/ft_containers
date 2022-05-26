#if FT_EQUAL_STD//CREATE A REAL STL EXAMPLE
    #define STD_FLAG 1
    #include <map>
    #include <stack>
    #include <vector>
    namespace ft = std;
#else
    #define STD_FLAG 0
    #include <map.hpp>
    #include <vector.hpp>
    #include "reverse_iterator.hpp"
    #include "pair.hpp"
    #include "lexicographical_compare.hpp"
    #include "equal.hpp"
    #include "is_integral.hpp"
    #include "enable_if.hpp"
    #include "iterator_traits.hpp"
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

#define NOT_VALGRIND_FLAG 1

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
*/

void default_test()
{
    std::cout << "----------------------" << std::endl;
    std::cout << "default test" << std::endl;
    ft::vector<std::string> vector_str;
    ft::vector<int> vector_int;
    // ft::stack<int> stack_int;
    ft::vector<Buffer> vector_buffer;
    // ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
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
    /*
    MutantStack<char> iterable_stack;
    for (char letter = 'a'; letter <= 'z'; letter++)
        iterable_stack.push(letter);
    for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
    {
        std::cout << *it;
    }
    std::cout << std::endl;
    */
}


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
    /*
    Because v2 is longer, it accesses places that v1 should not
    tester.if_print("v1:[0,1,2,3,4,5], v2:[0,1,2,3,4,5,6], ft::equal(v2.begin(), v2.end(), v1.begin()):",
                    ft::equal(v2.begin(), v2.end(), v1.begin()), "true", "false");
    */
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
                    ft::lexicographical_compare(str1.begin(), str1.end(), str2.begin(), str2.end()),
                    "true", "false");
    tester.if_print("hello and hellooo default:",
                    ft::lexicographical_compare(str1.begin(), str1.end(), str3.begin(), str3.end()),
                    "true", "false");
    tester.if_print("hellO and hello default:",
                    ft::lexicographical_compare(str2.begin(), str2.end(), str1.begin(), str1.end()),
                    "true", "false");
    tester.if_print("hellooo and hello default:",
                    ft::lexicographical_compare(str3.begin(), str3.end(), str1.begin(), str1.end()),
                    "true", "false");
    tester.if_print("hello and hellO greater:",
                    ft::lexicographical_compare(str1.begin(), str1.end(), str2.begin(), str2.end(), std::greater<char>()),
                    "true", "false");
    tester.if_print("hello and hellooo greater:",
                    ft::lexicographical_compare(str1.begin(), str1.end(), str3.begin(), str3.end(), std::greater<char>()),
                    "true", "false");
    tester.if_print("hellO and hello greater:",
                    ft::lexicographical_compare(str2.begin(), str2.end(), str1.begin(), str1.end(), std::greater<char>()),
                    "true", "false");
    tester.if_print("hellooo and hello greater:",
                    ft::lexicographical_compare(str3.begin(), str3.end(), str1.begin(), str1.end(), std::greater<char>()),
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
        tester.print("ri1 = vec.end()");
        tester.print("x = ri1");
        tester.print("y = ri1");
        tester.print("z = ri1 + 2");
        tester.print("*x ==", *x);
        tester.print("*y ==", *y);
        tester.print("*z ==", *z);
        tester.if_print("x == y:", x == y, "true", "false");
        tester.if_print("x != y:", x != y, "true", "false");
        tester.if_print("x <  y:", x <  y, "true", "false");
        tester.if_print("x <= y:", x <= y, "true", "false");
        tester.if_print("x == z:", x == z, "true", "false");
        tester.if_print("x != z:", x != z, "true", "false");
        tester.if_print("x <  z:", x <  z, "true", "false");
        tester.if_print("x <= z:", x <= z, "true", "false");
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
#if NOT_VALGRIND_FLAG
        if (init_num++ % 3 == 0)
            throw std::bad_alloc();
#endif
        tester.print("construct:", data);
    }
    ErrorTest(int x) : data(x)
    {
#if NOT_VALGRIND_FLAG
        if (init_num++ % 3 == 0)
            throw std::bad_alloc();
#endif
        tester.print("construct:", data);
    }
    ErrorTest(const ErrorTest& temp) : data(temp.data)
    {
#if NOT_VALGRIND_FLAG
        if (init_num++ % 3 == 0)
            throw std::bad_alloc();
#endif
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

    typename std::allocator<T>::pointer
    allocate(typename std::allocator<T>::size_type n, const void * hint = 0)
    {
#if NOT_VALGRIND_FLAG
        if (n >= 100)
            throw std::bad_alloc();
#endif
        return std::allocator<T>::allocate(n, hint);
    }

    static int construct_num;
    void construct(typename std::allocator<T>::pointer p, const T& value)
    {
#if NOT_VALGRIND_FLAG
        if (construct_num++ % 3 == 0)
            throw std::bad_alloc();
#endif
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
    tester.print("Test class is a wrapper for int\n");
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
    Exit with aborte due to an error in allocater.construct
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
    tester.print("");
    tester.print("operator= test");
    {
        tester.print("ft::vector<Test> vec1(2, Test(3));");
        tester.print("ft::vector<Test> vec2;");
        ft::vector<Test> vec1(2, Test(3));
        ft::vector<Test> vec2;
        tester.if_print("vec1.get_allocator() == vec2.get_allocator():",
                        vec1.get_allocator() == vec2.get_allocator(), "true", "false");
        tester.print("vec2 = vec1;");
        vec2 = vec1;
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
        tester.print("ft::vector<Test> vec1(2, Test(3));");
        tester.print("ft::vector<Test> vec2(1, Test(2));");
        ft::vector<Test> vec1(2, Test(3));
        ft::vector<Test> vec2(1, Test(2));
        tester.print("vec2 = vec1;");
        vec2 = vec1;
        tester.print("vec2.size():", vec2.size());
        tester.print("vec2.capacity():", vec2.capacity());
        for (std::size_t i = 0; i < vec2.size(); ++i)
            tester.set_stream(vec2[i].get_data());
        tester.put_all_stream();
        vec2[0] = 4;
        tester.print("change value vec2[0] = 4 -> vec1[0] vec2[]", vec1[0].get_data(), vec2[0].get_data());
    }
    tester.print("");
    {
        tester.print("ft::vector<Test> vec1(2, Test(3));");
        tester.print("ft::vector<Test> vec2(3, Test(2));");
        ft::vector<Test> vec1(2, Test(3));
        ft::vector<Test> vec2(3, Test(2));
        tester.print("vec2 = vec1;");
        vec2 = vec1;
        tester.print("vec2.size():", vec2.size());
        tester.print("vec2.capacity():", vec2.capacity());
        for (std::size_t i = 0; i < vec2.size(); ++i)
            tester.set_stream(vec2[i].get_data());
        tester.put_all_stream();
        vec2[0] = 4;
        tester.print("change value vec2[0] = 4 -> vec1[0] vec2[]", vec1[0].get_data(), vec2[0].get_data());
    }
    tester.print("");
    {
        tester.print("ft::vector<Test> vec1(2, Test(3));");
        tester.print("ft::vector<Test> vec2(1, Test(2));");
        tester.print("vec2.reserve(10)");
        ft::vector<Test> vec1(2, Test(3));
        ft::vector<Test> vec2(1, Test(2));
        vec2.reserve(10);
        tester.print("vec2 = vec1;");
        vec2 = vec1;
        tester.print("vec2.size():", vec2.size());
        tester.print("vec2.capacity():", vec2.capacity());
        for (std::size_t i = 0; i < vec2.size(); ++i)
            tester.set_stream(vec2[i].get_data());
        tester.put_all_stream();
        vec2[0] = 4;
        tester.print("change value vec2[0] = 4 -> vec1[0] vec2[]", vec1[0].get_data(), vec2[0].get_data());
    }
    tester.print("");
    {
        tester.print("ft::vector<Test> vec1(2, Test(3));");
        tester.print("ft::vector<Test> vec2(1, Test(2));");
        tester.print("vec1.reserve(10)");
        ft::vector<Test> vec1(2, Test(3));
        ft::vector<Test> vec2(1, Test(2));
        vec1.reserve(10);
        tester.print("vec2 = vec1;");
        vec2 = vec1;
        tester.print("vec2.size():", vec2.size());
        tester.print("vec2.capacity():", vec2.capacity());
        for (std::size_t i = 0; i < vec2.size(); ++i)
            tester.set_stream(vec2[i].get_data());
        tester.put_all_stream();
        vec2[0] = 4;
        tester.print("change value vec2[0] = 4 -> vec1[0] vec2[]", vec1[0].get_data(), vec2[0].get_data());
    }
    tester.print("");
    {
        tester.print("const ft::vector<Test> vec1(2, Test(3));");
        tester.print("ft::vector<Test> vec2(1, Test(2));");
        const ft::vector<Test> vec1(2, Test(3));
        ft::vector<Test> vec2(1, Test(2));
        tester.print("vec2 = vec1;");
        vec2 = vec1;
        tester.print("vec2.size():", vec2.size());
        tester.print("vec2.capacity():", vec2.capacity());
        for (std::size_t i = 0; i < vec2.size(); ++i)
            tester.set_stream(vec2[i].get_data());
        tester.put_all_stream();
        vec2[0] = 4;
        tester.print("change value vec2[0] = 4 -> vec1[0] vec2[]", vec1[0].get_data(), vec2[0].get_data());
    }
    tester.print("");
    tester.print("assign test");
    {
        tester.print("ft::vector<Test> vec;");
        tester.print("vec.assign(3, Test(2));");
        ft::vector<Test> vec;
        vec.assign(3, Test(2));
        tester.print("vec.size():", vec.size());
        tester.print("vec.capacity():", vec.capacity());
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i].get_data());
        tester.put_all_stream();
    }
    tester.print("");
    {
        tester.print("ft::vector<Test> vec(1, Test(2));");
        tester.print("vec.assign(2, Test(3));");
        ft::vector<Test> vec(1, Test(2));
        vec.assign(2, Test(3));
        tester.print("vec.size():", vec.size());
        tester.print("vec.capacity():", vec.capacity());
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i].get_data());
        tester.put_all_stream();
    }
    tester.print("");
    {
        tester.print("ft::vector<Test> vec(3, Test(2));");
        tester.print("vec.assign(2, Test(3));");
        ft::vector<Test> vec(3, Test(2));
        vec.assign(2, Test(3));
        tester.print("vec.size():", vec.size());
        tester.print("vec.capacity():", vec.capacity());
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i].get_data());
        tester.put_all_stream();
    }
    tester.print("");
    {
        tester.print("ft::vector<Test> vec(1, Test(2));");
        tester.print("vec.reserve(3);");
        tester.print("vec.assign(2, Test(3));");
        ft::vector<Test> vec(1, Test(2));
        vec.reserve(3);
        vec.assign(2, Test(3));
        tester.print("vec.size():", vec.size());
        tester.print("vec.capacity():", vec.capacity());
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i].get_data());
        tester.put_all_stream();
    }
    tester.print("");
    {
        tester.print("ft::vector<Test> vec(1, Test(2));");
        tester.print("vec.reserve(3);");
        tester.print("vec.assign(2, Test(3));");
        ft::vector<Test> vec(1, Test(2));
        vec.reserve(3);
        vec.assign(2, Test(3));
        tester.print("vec.size():", vec.size());
        tester.print("vec.capacity():", vec.capacity());
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i].get_data());
        tester.put_all_stream();
    }
    tester.print("");
    {
        tester.print("ft::vector<Test> vec1(2, Test(3));");
        tester.print("ft::vector<Test> vec2(1, Test(2));");
        tester.print("vec2.assign(vec1.begin(), vec1.end());");
        ft::vector<Test> vec1(2, Test(3));
        ft::vector<Test> vec2(1, Test(2));
        vec2.assign(vec1.begin(), vec1.end());
        tester.print("vec2.size():", vec2.size());
        tester.print("vec2.capacity():", vec2.capacity());
        for (std::size_t i = 0; i < vec2.size(); ++i)
            tester.set_stream(vec2[i].get_data());
        tester.put_all_stream();
        vec2[0] = 4;
        tester.print("change value vec2[0] = 4 -> vec1[0] vec2[]", vec1[0].get_data(), vec2[0].get_data());
    }
    tester.print("");
    {
        tester.print("ft::vector<Test> vec(1, Test(2));");
        tester.print("vec.assign(2, 3);");
        ft::vector<Test> vec(1, Test(2));
        vec.assign(2, 3);
        tester.print("vec.size():", vec.size());
        tester.print("vec.capacity():", vec.capacity());
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i].get_data());
        tester.put_all_stream();
    }
    tester.print("");
    {
        tester.print("ft::vector<Test> vec1(1, Test(3));");
        tester.print("ft::vector<Test> vec2(2, Test(2));");
        tester.print("vec2.assign(vec1.begin(), vec1.end());");
        ft::vector<Test> vec1(1, Test(3));
        ft::vector<Test> vec2(2, Test(2));
        vec2.assign(vec1.begin(), vec1.end());
        tester.print("vec2.size():", vec2.size());
        tester.print("vec2.capacity():", vec2.capacity());
        for (std::size_t i = 0; i < vec2.size(); ++i)
            tester.set_stream(vec2[i].get_data());
        tester.put_all_stream();
        vec2[0] = 4;
        tester.print("change value vec2[0] = 4 -> vec1[0] vec2[]", vec1[0].get_data(), vec2[0].get_data());
    }
    tester.print("");
    {
        tester.print("ft::vector<Test> vec1(2, Test(3));");
        tester.print("ft::vector<Test> vec2(1, Test(2));");
        tester.print("vec2.reserve(3);");
        tester.print("vec2.assign(vec1.begin(), vec1.end());");
        ft::vector<Test> vec1(2, Test(3));
        ft::vector<Test> vec2(1, Test(2));
        vec2.reserve(3);
        vec2.assign(vec1.begin(), vec1.end());
        tester.print("vec2.size():", vec2.size());
        tester.print("vec2.capacity():", vec2.capacity());
        for (std::size_t i = 0; i < vec2.size(); ++i)
            tester.set_stream(vec2[i].get_data());
        tester.put_all_stream();
        vec2[0] = 4;
        tester.print("change value vec2[0] = 4 -> vec1[0] vec2[]", vec1[0].get_data(), vec2[0].get_data());
    }
    tester.print("");
    tester.print("get_allocator test");
    {
        tester.print("std::allocator<Test> alloc;");
        tester.print("ft::vector<Test> vec(alloc);");
        std::allocator<Test> alloc;
        ft::vector<Test> vec(alloc);
        tester.if_print("vec.get_allocator() == alloc:",
                        alloc == vec.get_allocator(), "true", "false");
    }
    tester.print("");
    tester.print("at test");
    {
        tester.print("ft::vector<int> vec <- 0 1 2 3 4");
        ft::vector<int> vec;
        for (int i = 0; i < 5; ++i)
            vec.push_back(i);
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec.at(i));
        tester.put_all_stream();
        tester.print("access at(5)");
        try
        {
            vec.at(5) = 1;
        }
        catch(const std::out_of_range& e)
        {
            // tester.print(e.what());
            tester.print("std::out_of_range error");
        }
        vec.at(0) = 1;
        tester.print("vec.at(0) = 1 -> vec.at(0):", vec.at(0));
    }
    tester.print("");
    {
        tester.print("const ft::vector<int> vec(2, 3)");
        const ft::vector<int> vec(2, 3);
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec.at(i));
        tester.put_all_stream();
        tester.print("access at(2)");
        try
        {
            tester.print("at(2):", vec.at(2));
        }
        catch(const std::out_of_range& e)
        {
            // tester.print(e.what());
            tester.print("std::out_of_range error");
        }
    }
    tester.print("");
    tester.print("operator[] test");
    {
        tester.print("ft::vector<int> vec <- 0 1 2 3 4");
        ft::vector<int> vec;
        for (int i = 0; i < 5; ++i)
            vec.push_back(i);
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i]);
        tester.put_all_stream();
        vec[0] = 1;
        tester.print("vec[0] = 1 -> vec[0]:", vec[0]);
    }
    tester.print("");
    {
        tester.print("const ft::vector<int> vec(2, 3)");
        const ft::vector<int> vec(2, 3);
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i]);
        tester.put_all_stream();
    }
    tester.print("");
    tester.print("front and back test");
    {
        tester.print("ft::vector<int> vec <- 0 1 2 3 4");
        ft::vector<int> vec;
        for (int i = 0; i < 5; ++i)
            vec.push_back(i);
        tester.print("vec.front():", vec.front());
        tester.print("vec.back():", vec.back());
        vec.front() = 1;
        vec.back() = 1;
        tester.print("vec.front() = 1 -> vec.front():", vec.front());
        tester.print("vec.back() = 1 -> vec.back():", vec.back());
    }
    tester.print("");
    {
        tester.print("const ft::vector<int> vec(2, 3)");
        const ft::vector<int> vec(2, 3);
        tester.print("vec.front():", vec.front());
        tester.print("vec.back():", vec.back());
    }
    tester.print("");
    tester.print("data test");
    {
        tester.print("ft::vector<int> vec <- 0 1 2 3 4");
        tester.print("int* data = vec.data()");
        tester.print("print data[i]");
        ft::vector<int> vec;
        for (int i = 0; i < 5; ++i)
            vec.push_back(i);
        int* data = vec.data();
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(data[i]);
        tester.put_all_stream();
        data[1] = 0;
        tester.print("data[1] = 0 -> vec[1]:", vec[1]);
    }
    tester.print("");
    {
        tester.print("const ft::vector<int> vec(3, 1);");
        tester.print("const int* data = vec.data()");
        tester.print("print data[i]");
        const ft::vector<int> vec(3, 1);
        const int* data = vec.data();
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(data[i]);
        tester.put_all_stream();
    }
    tester.print("");
    {
        tester.print("ft::vector<int> vec");
        ft::vector<int> vec;
        tester.if_print("vec is NULL:", vec.data() == NULL, "true", "false");
    }
    tester.print("");
    {
        tester.print("ft::vector<Test> vec(2, Test(3))");
        ft::vector<Test> vec(2, Test(3));
        tester.print("vec.data()->get_data():", vec.data()->get_data());
    }
    tester.print("");
    tester.print("begin and end test");
    {
        tester.print("ft::vector<int> vec <- 0 1 2 3 4");
        tester.print("ft::vector<int>::iterator begin = vec.begin()");
        tester.print("ft::vector<int>::iterator end = vec.end()");
        ft::vector<int> vec;
        for (int i = 0; i < 5; ++i)
            vec.push_back(i);
        ft::vector<int>::iterator begin = vec.begin();
        ft::vector<int>::iterator end = vec.end();
        for (; begin != end; ++begin)
            tester.set_stream(*begin);
        tester.put_all_stream();
        begin = vec.begin();
        *begin = 2;
        tester.print("*begin = 2 -> vec[0]:", vec[0]);
    }
    tester.print("");
    {
        tester.print("const ft::vector<int> vec(6, 1)");
        tester.print("ft::vector<int>::const_iterator begin = vec.begin()");
        tester.print("ft::vector<int>::const_iterator end = vec.end()");
        const ft::vector<int> vec(6, 1);
        ft::vector<int>::const_iterator begin = vec.begin();
        ft::vector<int>::const_iterator end = vec.end();
        for (; begin != end; ++begin)
            tester.set_stream(*begin);
        tester.put_all_stream();
        begin = vec.begin();
    }
    tester.print("");
    {
        tester.print("ft::vector<int> vec");
        ft::vector<int> vec;
        tester.if_print("vec.begin() == vec.end():", vec.begin() == vec.end(), "true", "false");
    }
    tester.print("");
    tester.print("rbegin and rend test");
    {
        tester.print("ft::vector<int> vec <- 0 1 2 3 4");
        tester.print("ft::vector<int>::reverse_iterator begin = vec.begin()");
        tester.print("ft::vector<int>::reverse_iterator end = vec.end()");
        ft::vector<int> vec;
        for (int i = 0; i < 5; ++i)
            vec.push_back(i);
        ft::vector<int>::reverse_iterator rbegin = vec.rbegin();
        ft::vector<int>::reverse_iterator rend = vec.rend();
        for (; rbegin != rend; ++rbegin)
            tester.set_stream(*rbegin);
        tester.put_all_stream();
        rbegin = vec.rbegin();
        *rbegin = 2;
        tester.print("*rbegin = 2 -> vec[4]:", vec[4]);
    }
    tester.print("");
    {
        tester.print("const ft::vector<int> vec(6, 1)");
        tester.print("ft::vector<int>::const_reverse_iterator rbegin = vec.rbegin()");
        tester.print("ft::vector<int>::const_reverse_iterator rend = vec.rend()");
        const ft::vector<int> vec(6, 1);
        ft::vector<int>::const_reverse_iterator rbegin = vec.rbegin();
        ft::vector<int>::const_reverse_iterator rend = vec.rend();
        for (; rbegin != rend; ++rbegin)
            tester.set_stream(*rbegin);
        tester.put_all_stream();
        rbegin = vec.rbegin();
    }
    tester.print("");
    {
        tester.print("ft::vector<int> vec");
        ft::vector<int> vec;
        tester.if_print("vec.rbegin() == vec.rend():", vec.rbegin() == vec.rend(), "true", "false");
    }
    tester.print("");
    tester.print("empty test");
    {
        ft::vector<int> vec;
        tester.print("ft::vector<int> vec;");
        tester.if_print("vec.empty():", vec.empty(), "true", "false");
        vec.reserve(10);
        tester.print("vec.reserve(10);");
        tester.if_print("vec.empty():", vec.empty(), "true", "false");
        vec.push_back(1);
        tester.print("vec.push_back(1);");
        tester.if_print("vec.empty():", vec.empty(), "true", "false");
    }
    tester.print("");
    tester.print("size test");
    {
        ft::vector<int> vec;
        tester.print("ft::vector<int> vec;");
        tester.print("vec.size()", vec.size());
        vec.reserve(10);
        tester.print("vec.reserve(10);");
        tester.print("vec.size()", vec.size());
        vec.push_back(1);
        tester.print("vec.push_back(1);");
        tester.print("vec.size()", vec.size());
    }
    {
        ft::vector<int> vec(100, 1);
        tester.print("ft::vector<int> vec(100, 1);");
        tester.print("vec.size()", vec.size());
    }
    tester.print("");
    tester.print("max_size test");
    {
        ft::vector<char> vec;
        tester.print("ft::vector<char> vec;");
        tester.print("vec.max_size()", vec.max_size());
    }
    tester.print("");
    {
        ft::vector<int> vec;
        tester.print("ft::vector<int> vec;");
        tester.print("vec.max_size()", vec.max_size());
    }
    tester.print("");
    {
        ft::vector<Test> vec;
        tester.print("ft::vector<Test> vec;");
        tester.print("vec.max_size()", vec.max_size());
    }
    tester.print("");
    tester.print("reserve and capacity test");
    {
        tester.print("ft::vector<Test> vec;");
        ft::vector<Test> vec;
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.reserve(10);");
        vec.reserve(10);
        tester.print("vec.capacity():", vec.capacity());
    }
    tester.print("");
    {
        tester.print("ft::vector<Test> vec(3, 1);");
        ft::vector<Test> vec(3, 1);
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        tester.print("vec.reserve(2);");
        vec.reserve(2);
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        tester.print("vec.reserve(3);");
        vec.reserve(3);
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        tester.print("vec.reserve(10);");
        vec.reserve(10);
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        try
        {
            vec.reserve(vec.max_size() + 1);
        }
        catch(const std::length_error& e)
        {
            tester.print("std::length_error: ", e.what());
        }
        catch(const std::exception& e)
        {
            tester.print("std::exception: ", e.what());
        }
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        tester.print("vec[0]:", vec[0].get_data());
    }
    tester.print("");
    {
        tester.print("ErrorAlocator<Test> alloc;");
        ErrorAlocator<int> alloc;
        tester.print("ft::vector<int> vec(alloc);");
        ft::vector<int, ErrorAlocator<int> > vec(alloc);
        tester.print("vec.push_back(1);");
        vec.push_back(1);
        tester.print("vec.reserve(1000);");
        try
        {
            vec.reserve(1000);
        }
        catch(const std::bad_alloc& e)
        {
            tester.print("std::bad_alloc: ", e.what());
        }
        catch(const std::exception& e)
        {
            tester.print("std::exception: ", e.what());
        }
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        tester.print("vec[0]:", vec[0]);
    }
    tester.print("");
    tester.print("clear test");
    {
        tester.print("ft::vector<Test> vec(3, Test(1));");
        ft::vector<Test> vec(3, Test(1));
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        tester.print("vec.clear();");
        vec.clear();
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
    }
    tester.print("");
    tester.print("insert test");
    {
        tester.print("ft::vector<Test> vec;");
        ft::vector<Test> vec;
        tester.print("ft::vector<Test>::iterator pos = vec.insert(vec.begin(), Test(1));");
        ft::vector<Test>::iterator pos = vec.insert(vec.begin(), Test(1));
        tester.if_print("pos == vec.begin():", pos == vec.begin(), "true", "false");
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i].get_data());
        tester.put_all_stream();
        tester.print("pos = vec.insert(vec.begin(), Test(2));");
        pos = vec.insert(vec.begin(), Test(2));
        tester.if_print("pos == vec.begin():", pos == vec.begin(), "true", "false");
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i].get_data());
        tester.put_all_stream();
        tester.print("vec.reserve(10);");
        vec.reserve(10);
        tester.print("pos = vec.insert(vec.begin() + 1, Test(3));");
        pos = vec.insert(vec.begin() + 1, Test(3));
        tester.if_print("pos == vec.begin() + 1:", pos == vec.begin() + 1, "true", "false");
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i].get_data());
        tester.put_all_stream();
        tester.print("pos = vec.insert(vec.end(), Test(4));");
        pos = vec.insert(vec.end(), Test(4));
        tester.if_print("pos == vec.end() - 1:", pos == vec.end() - 1, "true", "false");
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i].get_data());
        tester.put_all_stream();
    }
    tester.print("");
    {
        tester.print("ErrorAlocator<int> alloc;");
        ErrorAlocator<int> alloc;
        tester.print("ft::vector<int> vec(alloc);");
        ft::vector<int, ErrorAlocator<int> > vec(alloc);
        tester.print("vec.reserve(10);");
        vec.reserve(10);
        tester.print("vec.insert(vec.end(), 1);");
        vec.insert(vec.end(), 1);
        try
        {
            tester.print("vec.insert(vec.end(), 1);");
            vec.insert(vec.end(), 1);
        }
        catch(const std::bad_alloc& e)
        {
            tester.print("std::bad_alloc: ", e.what());
        }
        catch(const std::exception& e)
        {
            tester.print("std::exception: ", e.what());
        }
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        tester.print("vec[0]:", vec[0]);
    }
    // int instead of Test because of the different number of times the constructor is called.
    tester.print("");
    {
        tester.print("ft::vector<int> vec;");
        ft::vector<int> vec;
        tester.print("vec.insert(vec.begin(), 2, 1);");
        vec.insert(vec.begin(), 2, 1);
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i]);
        tester.put_all_stream();
        tester.print("vec.insert(vec.begin() + 1, 2, 2);");
        vec.insert(vec.begin() + 1, 2, 2);
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i]);
        tester.put_all_stream();
        tester.print("vec.reserve(100);");
        vec.reserve(100);
        tester.print("vec.insert(vec.begin() + 1, 2, 3);");
        vec.insert(vec.begin() + 1, 2, 3);
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i]);
        tester.put_all_stream();
        tester.print("vec.insert(vec.begin() + 4, 2, 4);");
        vec.insert(vec.begin() + 4, 2, 4);
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i]);
        tester.put_all_stream();
    }
    tester.print("");
    {
        tester.print("ft::vector<Test> vec;");
        ft::vector<Test> vec;
        tester.print("vec.insert(vec.begin(), 0, Test(1));");
        vec.insert(vec.begin(), 0, Test(1));
    }
    tester.print("");
    {
        tester.print("ErrorAlocator<int> alloc;");
        ErrorAlocator<int> alloc;
        tester.print("ft::vector<int> vec(1, 1, alloc);");
        ft::vector<int, ErrorAlocator<int> > vec(1, 1, alloc);
        tester.print("vec.reserve(10);");
        vec.reserve(10);
        try
        {
            tester.print("vec.insert(vec.end(), 10, 1);");
            vec.insert(vec.end(), 10, 1);
        }
        catch(const std::bad_alloc& e)
        {
            tester.print("std::bad_alloc: ", e.what());
        }
        catch(const std::exception& e)
        {
            tester.print("std::exception: ", e.what());
        }
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        tester.print("vec[0]:", vec[0]);
    }
#if NOT_VALGRIND_FLAG
    tester.print("");
    {
        tester.print("ft::vector<Test> vec(1, 1);");
        ft::vector<int> vec(1, 1);
        try
        {
            vec.insert(vec.begin(), vec.max_size() - 1, 3);
        }
        catch(const std::length_error& e)
        {
            tester.print("std::length_error: ", e.what());
        }
        catch(const std::exception& e)
        {
            tester.print("std::exception: ", e.what());
        }
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        tester.print("vec[0]:", vec[0]);
    }
#endif
    tester.print("");
    {
        tester.print("ft::vector<int> vec;");
        ft::vector<int> vec;
        tester.print("ft::vector<int> vec2; <- 0, 1, 2, 3, 4");
        ft::vector<int> vec2;
        for (std::size_t i = 0; i < 5; ++i)
            vec2.push_back(i);
        tester.print("vec.insert(vec.begin(), vec2.begin(), vec2.begin() + 2);");
        vec.insert(vec.begin(), vec2.begin(), vec2.begin() + 2);
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i]);
        tester.put_all_stream();
        tester.print("vec.insert(vec.begin() + 1, vec2.begin() + 2, vec2.begin() + 4);");
        vec.insert(vec.begin() + 1, vec2.begin() + 2, vec2.begin() + 4);
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i]);
        tester.put_all_stream();
        tester.print("vec.reserve(100);");
        vec.reserve(100);
        tester.print("vec.insert(vec.begin() + 1, vec2.begin() + 1, vec2.begin() + 3);");
        vec.insert(vec.begin() + 1, vec2.begin() + 1, vec2.begin() + 3);
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i]);
        tester.put_all_stream();
        tester.print("vec.insert(vec.begin() + 4, vec2.begin() + 3, vec2.begin() + 5);");
        vec.insert(vec.begin() + 4, vec2.begin() + 3, vec2.begin() + 5);
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i]);
        tester.put_all_stream();
    }
    tester.print("");
    {
        tester.print("ft::vector<Test> vec;");
        ft::vector<Test> vec;
        tester.print("ft::vector<int> vec2; <- 0, 1, 2, 3, 4");
        ft::vector<int> vec2;
        for (std::size_t i = 0; i < 5; ++i)
            vec2.push_back(i);
        tester.print("vec.insert(vec.begin(), vec2.begin(), vec2.begin());");
        vec.insert(vec.begin(), vec2.begin(), vec2.begin());
    }
    tester.print("");
    {
        tester.print("ErrorAlocator<int> alloc;");
        ErrorAlocator<int> alloc;
        tester.print("ft::vector<int> vec(1, 1, alloc);");
        ft::vector<int, ErrorAlocator<int> > vec(1, 1, alloc);
        tester.print("ft::vector<int> vec2; <- 0, 1, 2, 3, 4");
        ft::vector<int> vec2;
        for (std::size_t i = 0; i < 5; ++i)
            vec2.push_back(i);
        tester.print("vec.reserve(10);");
        vec.reserve(10);
        try
        {
            tester.print("vec.insert(vec.end(), vec2.begin(), vec2.end());");
            vec.insert(vec.end(), vec2.begin(), vec2.end());
        }
        catch(const std::bad_alloc& e)
        {
            tester.print("std::bad_alloc: ", e.what());
        }
        catch(const std::exception& e)
        {
            tester.print("std::exception: ", e.what());
        }
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        tester.print("vec[0]:", vec[0]);
    }
    /*
    The std::vector implementation calls the constructor one more time
    tester.print("");
    {
        tester.print("ft::vector<Test> vec(4, Test(1));");
        ft::vector<Test> vec(4, Test(1));
        tester.print("vec.reserve(10);");
        vec.reserve(10);
        tester.print("vec.insert(vec.begin() + 1, 2, Test(2));");
        vec.insert(vec.begin() + 1, 2, Test(2));
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i].get_data());
        tester.put_all_stream();
    }
    */
    tester.print("");
    tester.print("erase test");
    {
        tester.print("ft::vector<int> vec; <- 0, 1, 2, 3, 4");
        ft::vector<int> vec;
        tester.print("vec.reserve(10);");
        vec.reserve(10);
        for (std::size_t i = 0; i < 5; ++i)
            vec.push_back(i);
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i]);
        tester.put_all_stream();
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        tester.print("ft::vector<int>::iterator iter1 = vec.erase(vec.begin())");
        ft::vector<int>::iterator iter = vec.erase(vec.begin());
        tester.if_print("iter == vec.begin():", iter == vec.begin(), "true", "false");
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        iter = vec.erase(vec.end() - 1);
        tester.if_print("iter == vec.end():", iter == vec.end(), "true", "false");
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i]);
        tester.put_all_stream();
    }
    tester.print("");
    {
        tester.print("ft::vector<int> vec; <- 0, 1, 2, 3, 4");
        ft::vector<int> vec;
        tester.print("vec.reserve(10);");
        vec.reserve(10);
        for (std::size_t i = 0; i < 5; ++i)
            vec.push_back(i);
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i]);
        tester.put_all_stream();
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        tester.print("ft::vector<int>::iterator iter = vec.erase(vec.begin() + 1, vec.begin() + 3);");
        ft::vector<int>::iterator iter = vec.erase(vec.begin() + 1, vec.begin() + 3);
        tester.if_print("iter == vec.begin() + 1:", iter == vec.begin() + 1, "true", "false");
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i]);
        tester.put_all_stream();
        tester.print("iter = vec.erase(vec.begin(), vec.begin());");
        iter = vec.erase(vec.begin(), vec.begin());
        tester.if_print("iter == vec.begin():", iter == vec.begin(), "true", "false");
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        tester.print("iter = vec.erase(vec.begin() + 1, vec.end());");
        iter = vec.erase(vec.begin() + 1, vec.end());
        tester.if_print("iter == vec.begin() + 1:", iter == vec.begin() + 1, "true", "false");
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i]);
        tester.put_all_stream();
    }
    tester.print("");
    tester.print("push_back test");
    {
        tester.print("ft::vector<Test> vec;");
        ft::vector<Test> vec;
        tester.print("vec.push_back(0);");
        vec.push_back(0);
        tester.print("vec.capacity():", vec.capacity());
        /*
        Commented out because constructor is called at different times
        tester.print("vec.push_back(1);");
        vec.push_back(1);
        tester.print("vec.capacity():", vec.capacity());
        */
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i].get_data());
        tester.put_all_stream();
        tester.print("vec.reserve(10);");
        vec.reserve(10);
        tester.print("vec.push_back(2);");
        vec.push_back(2);
        tester.print("vec.push_back(3);");
        vec.push_back(3);
        tester.print("vec.capacity():", vec.capacity());
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i].get_data());
        tester.put_all_stream();
    }
    tester.print("");
    {
        tester.print("ErrorAlocator<Test> alloc;");
        ErrorAlocator<int> alloc;
        tester.print("ft::vector<int> vec(alloc);");
        ft::vector<int, ErrorAlocator<int> > vec(alloc);
        tester.print("vec.push_back(1);");
        vec.push_back(1);
        tester.print("vec.push_back(2);");
        try
        {
            vec.push_back(2);
        }
        catch(const std::bad_alloc& e)
        {
            tester.print("std::bad_alloc: ", e.what());
        }
        catch(const std::exception& e)
        {
            tester.print("std::exception: ", e.what());
        }
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        tester.print("vec[0]:", vec[0]);
    }
    tester.print("");
    tester.print("pop_back test");
    {
        tester.print("ft::vector<Test> vec; <- 0, 1, 2");
        ft::vector<Test> vec;
        vec.reserve(10);
        for (int i = 0; i < 3; ++i)
            vec.push_back(Test(i));
        tester.print("vec.pop_back();");
        vec.pop_back();
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        tester.print("vec.pop_back();");
        vec.pop_back();
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        tester.print("vec.pop_back();");
        vec.pop_back();
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
    }
    tester.print("");
    tester.print("resize test");
    {
        // The number of times the constructor is called is different, so check int
        tester.print("ft::vector<int> vec;");
        ft::vector<int> vec;
        tester.print("vec.resize(2);");
        vec.resize(2);
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i]);
        tester.put_all_stream();
        tester.print("vec.resize(1, 1);");
        vec.resize(1, 1);
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i]);
        tester.put_all_stream();
        tester.print("vec.resize(1, 2);");
        vec.resize(1, 2);
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i]);
        tester.put_all_stream();
        tester.print("vec.resize(2, 3);");
        vec.resize(2, 3);
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i]);
        tester.put_all_stream();
        tester.print("vec.resize(3, 4);");
        vec.resize(3, 4);
        // Because of the different increase in capacities
        // tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        for (std::size_t i = 0; i < vec.size(); ++i)
            tester.set_stream(vec[i]);
        tester.put_all_stream();
    }
    tester.print("");
    {
        tester.print("ErrorAlocator<Test> alloc;");
        ErrorAlocator<int> alloc;
        tester.print("ft::vector<int> vec(alloc);");
        ft::vector<int, ErrorAlocator<int> > vec(alloc);
        tester.print("vec.push_back(1);");
        vec.push_back(1);
        tester.print("vec.resize(3, 1);");
        try
        {
            vec.resize(3, 1);
        }
        catch(const std::bad_alloc& e)
        {
            tester.print("std::bad_alloc: ", e.what());
        }
        catch(const std::exception& e)
        {
            tester.print("std::exception: ", e.what());
        }
        tester.print("vec.capacity():", vec.capacity());
        tester.print("vec.size():", vec.size());
        tester.print("vec[0]:", vec[0]);
    }
    tester.print("");
    tester.print("swap test");
    {
        tester.print("ft::vector<Test> vec1(2, 1);");
        ft::vector<Test> vec1(2, 1);
        tester.print("ft::vector<Test> vec2(3, 2);");
        ft::vector<Test> vec2(3, 2);
        tester.print("ft::vector<Test>::iterator iter1 = vec1.begin();");
        ft::vector<Test>::iterator iter1 = vec1.begin();
        tester.print("ft::vector<Test>::iterator iter2 = vec2.begin();");
        ft::vector<Test>::iterator iter2 = vec2.begin();
        tester.print("ft::vector<Test>::reference value1 = vec1.front();");
        ft::vector<Test>::reference value1 = vec1.front();
        tester.print("ft::vector<Test>::reference value2 = vec2.front();");
        ft::vector<Test>::reference value2 = vec2.front();
        tester.print("vec1");
        for (std::size_t i = 0; i < vec1.size(); ++i)
            tester.set_stream(vec1[i].get_data());
        tester.put_all_stream();
        tester.print("vec2");
        for (std::size_t i = 0; i < vec2.size(); ++i)
            tester.set_stream(vec2[i].get_data());
        tester.put_all_stream();
        tester.print("iter1:", iter1->get_data());
        tester.print("iter2:", iter2->get_data());
        tester.print("value1:", value1.get_data());
        tester.print("value2:", value2.get_data());
        tester.print("vec1.capacity():", vec1.capacity());
        tester.print("vec2.capacity():", vec2.capacity());
        tester.print("vec1.swap(vec2);");
        vec1.swap(vec2);
        tester.print("vec1");
        for (std::size_t i = 0; i < vec1.size(); ++i)
            tester.set_stream(vec1[i].get_data());
        tester.put_all_stream();
        tester.print("vec2");
        for (std::size_t i = 0; i < vec2.size(); ++i)
            tester.set_stream(vec2[i].get_data());
        tester.put_all_stream();
        tester.print("iter1:", iter1->get_data());
        tester.print("iter2:", iter2->get_data());
        tester.print("value1:", value1.get_data());
        tester.print("value2:", value2.get_data());
        tester.print("vec1.capacity():", vec1.capacity());
        tester.print("vec2.capacity():", vec2.capacity());
    }
    tester.print("");
    tester.print("operator==,!=,<,<=,>,>= test");
    {
        ft::vector<int> vec1;
        ft::vector<int> vec2;
        ft::vector<int> vec3;
        ft::vector<int> vec4;
    
        for (int i = 0; i < 3; ++i)
            vec1.push_back(i);
        for (int i = 0; i < 4; ++i)
            vec2.push_back(i);
        for (int i = 0; i < 3; ++i)
            vec3.push_back(i + 1);
        for (int i = 0; i < 3; ++i)
            vec4.push_back(i);

        tester.if_print("vec1 == vec2:", vec1 == vec2, "true", "false");
        tester.if_print("vec1 != vec2:", vec1 != vec2, "true", "false");
        tester.if_print("vec1 < vec2:", vec1 < vec2, "true", "false");
        tester.if_print("vec1 <= vec2:", vec1 <= vec2, "true", "false");
        tester.if_print("vec1 > vec2:", vec1 > vec2, "true", "false");
        tester.if_print("vec1 >= vec2:", vec1 >= vec2, "true", "false");
        tester.if_print("vec1 == vec3:", vec1 == vec3, "true", "false");
        tester.if_print("vec1 != vec3:", vec1 != vec3, "true", "false");
        tester.if_print("vec1 < vec3:", vec1 < vec3, "true", "false");
        tester.if_print("vec1 <= vec3:", vec1 <= vec3, "true", "false");
        tester.if_print("vec1 > vec3:", vec1 > vec3, "true", "false");
        tester.if_print("vec1 >= vec3:", vec1 >= vec3, "true", "false");
        tester.if_print("vec1 == vec4:", vec1 == vec4, "true", "false");
        tester.if_print("vec1 != vec4:", vec1 != vec4, "true", "false");
        tester.if_print("vec1 < vec4:", vec1 < vec4, "true", "false");
        tester.if_print("vec1 <= vec4:", vec1 <= vec4, "true", "false");
        tester.if_print("vec1 > vec4:", vec1 > vec4, "true", "false");
        tester.if_print("vec1 >= vec4:", vec1 >= vec4, "true", "false");
    }
    tester.print("");
    tester.print("ft::swap test");
    {
        tester.print("ft::vector<Test> vec1(2, 1);");
        ft::vector<Test> vec1(2, 1);
        tester.print("ft::vector<Test> vec2(3, 2);");
        ft::vector<Test> vec2(3, 2);
        tester.print("ft::vector<Test>::iterator iter1 = vec1.begin();");
        ft::vector<Test>::iterator iter1 = vec1.begin();
        tester.print("ft::vector<Test>::iterator iter2 = vec2.begin();");
        ft::vector<Test>::iterator iter2 = vec2.begin();
        tester.print("ft::vector<Test>::reference value1 = vec1.front();");
        ft::vector<Test>::reference value1 = vec1.front();
        tester.print("ft::vector<Test>::reference value2 = vec2.front();");
        ft::vector<Test>::reference value2 = vec2.front();
        tester.print("vec1");
        for (std::size_t i = 0; i < vec1.size(); ++i)
            tester.set_stream(vec1[i].get_data());
        tester.put_all_stream();
        tester.print("vec2");
        for (std::size_t i = 0; i < vec2.size(); ++i)
            tester.set_stream(vec2[i].get_data());
        tester.put_all_stream();
        tester.print("iter1:", iter1->get_data());
        tester.print("iter2:", iter2->get_data());
        tester.print("value1:", value1.get_data());
        tester.print("value2:", value2.get_data());
        tester.print("vec1.capacity():", vec1.capacity());
        tester.print("vec2.capacity():", vec2.capacity());
        tester.print("ft::swap(vec1, vec2);");
        ft::swap(vec1, vec2);
        tester.print("vec1");
        for (std::size_t i = 0; i < vec1.size(); ++i)
            tester.set_stream(vec1[i].get_data());
        tester.put_all_stream();
        tester.print("vec2");
        for (std::size_t i = 0; i < vec2.size(); ++i)
            tester.set_stream(vec2[i].get_data());
        tester.put_all_stream();
        tester.print("iter1:", iter1->get_data());
        tester.print("iter2:", iter2->get_data());
        tester.print("value1:", value1.get_data());
        tester.print("value2:", value2.get_data());
        tester.print("vec1.capacity():", vec1.capacity());
        tester.print("vec2.capacity():", vec2.capacity());
    }
    tester.print("");
    tester.print("other test");
    {
        tester.print("ft::vector<int> vec <- 0, 1, 2");
        ft::vector<int> vec;
        for (int i = 0; i < 3; ++i)
            vec.push_back(i);
        tester.print("ft::vector<int>::const_iterator citer = vec.begin();");
        tester.print("ft::vector<int>::iterator iter = vec.begin();");
        ft::vector<int>::const_iterator citer = vec.begin();
        ft::vector<int>::iterator iter = vec.begin();
        tester.if_print("*iter < *(citer + 1):", *iter < *(citer + 1), "true", "false");
    }
    tester.print("");
    {
        tester.print("ft::vector<ft::vector<int>> vec(3);");
        ft::vector<ft::vector<int> > vec(3);
        tester.print("vec[1] <- 0, 1, 2");
        for (int i = 0; i < 3; ++i)
            vec[1].push_back(i);
        for (std::size_t i = 0; i < vec[1].size(); ++i)
            tester.set_stream(vec[1][i]);
        tester.put_all_stream();
    }
}

class MapTest
{
private:
    ft::pair<const int, double> data;
    Tester tester;
public:
    MapTest() : data(0, 0) {tester.print("construct:", data.first, data.second);}
    MapTest(int x, double y) : data(x, y) {tester.print("construct:", data.first, data.second);}
    MapTest(const MapTest& temp) : data(temp.data) {tester.print("construct:", data.first, data.second);}
    MapTest& operator=(const MapTest& temp) {this->data.second = temp.data.second; return *this;}
    ~MapTest() {tester.print("destruct:", data.first, data.second);}

    ft::pair<const int, double> get_data() const {return data;}
};

void map_test()
{
    Tester tester;
    tester.print("");
    tester.print("----------------------");
    tester.print("map test");
    tester.print("");
    tester.print("member types test");
    tester.print("ft::map<int, double>");
    tester.if_print("key_type:",
                    typeid(ft::map<int, double>::key_type) == typeid(int), "int", "other");
    tester.if_print("mapped_type:",
                    typeid(ft::map<int, double>::mapped_type) == typeid(double), "double", "other");
    tester.if_print("value_type:",
                    typeid(ft::map<int, double>::value_type) == typeid(ft::pair<const int, double>), "pair<const int, double>", "other");
    tester.if_print("size_type:",
                    typeid(ft::map<int, double>::size_type) == typeid(std::size_t), "std::size_t", "other");
    tester.if_print("difference_type:",
                    typeid(ft::map<int, double>::difference_type) == typeid(std::ptrdiff_t), "std::ptrdiff_t", "other");
    tester.if_print("key_compare:",
                    typeid(ft::map<int, double>::key_compare) == typeid(std::less<int>), "std::less<int>", "other");
    tester.if_print("allocator_type:",
                    typeid(ft::map<int, double>::allocator_type) == typeid(std::allocator<ft::pair<const int, double> >), "std::allocator<ft::pair<const int, double>>", "other");
    tester.if_print("reference:",
                    typeid(ft::map<int, double>::reference) == typeid(ft::pair<const int, double>&), "ft::pair<const int, double>&", "other");
    tester.if_print("const_reference:",
                    typeid(ft::map<int, double>::const_reference) == typeid(const ft::pair<const int, double>&), "const ft::pair<const int, double>&", "other");
    tester.if_print("pointer:",
                    typeid(ft::map<int, double>::pointer) == typeid(std::allocator<ft::pair<const int, double> >::pointer), "std::allocator<ft::pair<const int, double> >::pointer", "other");
    tester.if_print("const_pointer:",
                    typeid(ft::map<int, double>::const_pointer) == typeid(std::allocator<ft::pair<const int, double> >::const_pointer), "std::allocator<ft::pair<const int, double> >::const_pointer", "other");
    tester.print("std::map<int, double>::iterator");
    tester.if_print("difference_type:",
                    typeid(ft::iterator_traits<ft::map<int, double>::iterator>::difference_type) == typeid(std::ptrdiff_t),
                    "std::ptrdiff_t", "other");
    tester.if_print("value_type:",
                    typeid(ft::iterator_traits<ft::map<int, double>::iterator>::value_type) == typeid(ft::pair<const int, double>),
                    "ft::pair<const int, double>", "other");
    tester.if_print("pointer:",
                    typeid(ft::iterator_traits<ft::map<int, double>::iterator>::pointer) == typeid(ft::pair<const int, double>*),
                    "ft::pair<const int, double>*", "other");
    tester.if_print("reference:",
                    typeid(ft::iterator_traits<ft::map<int, double>::iterator>::reference) == typeid(ft::pair<const int, double>&),
                    "ft::pair<const int, double>&", "other");
    tester.if_print("iterator_category:",
                    typeid(ft::iterator_traits<ft::map<int, double>::iterator>::iterator_category) == typeid(std::bidirectional_iterator_tag),
                    "std::bidirectional_iterator_tag", "other");
    tester.print("std::map<int, double>::const_iterator");
    tester.if_print("difference_type:",
                    typeid(ft::iterator_traits<ft::map<int, double>::const_iterator>::difference_type) == typeid(std::ptrdiff_t),
                    "std::ptrdiff_t", "other");
    tester.if_print("value_type:",
                    typeid(ft::iterator_traits<ft::map<int, double>::const_iterator>::value_type) == typeid(ft::pair<const int, double>),
                    "ft::pair<const int, double>", "other");
    tester.if_print("pointer:",
                    typeid(ft::iterator_traits<ft::map<int, double>::const_iterator>::pointer) == typeid(const ft::pair<const int, double>*),
                    "ft::pair<const int, double>*", "other");
    tester.if_print("reference:",
                    typeid(ft::iterator_traits<ft::map<int, double>::const_iterator>::reference) == typeid(const ft::pair<const int, double>&),
                    "ft::pair<const int, double>&", "other");
    tester.if_print("iterator_category:",
                    typeid(ft::iterator_traits<ft::map<int, double>::const_iterator>::iterator_category) == typeid(std::bidirectional_iterator_tag),
                    "std::bidirectional_iterator_tag", "other");
    tester.if_print("reverse_iterator:",
                    typeid(ft::map<int, double>::reverse_iterator) == typeid(ft::reverse_iterator<ft::map<int, double>::iterator>),
                    "ft::reverse_iterator<ft::map<int, double>::iterator>", "other");
    tester.if_print("const_reverse_iterator:",
                    typeid(ft::map<int, double>::const_reverse_iterator) == typeid(ft::reverse_iterator<ft::map<int, double>::const_iterator>),
                    "ft::reverse_iterator<ft::map<int, double>::const_iterator>", "other");
    tester.print("");
    tester.print("basic test");
    {
        tester.print("ft::map<int, char> ma;");
        ft::map<int, char> ma;
        tester.print("ft::pair<ft::map<int, char>::iterator, bool> iter_and_bool = ma.insert(ft::pair<const int, char>(1, 'a'));");
        ft::pair<ft::map<int, char>::iterator, bool> iter_and_bool = ma.insert(ft::pair<const int, char>(1, 'a'));
        tester.if_print("insert ok:", iter_and_bool.second);
        ft::map<int, char>::iterator iter = iter_and_bool.first;
        tester.print("index:", (*iter).first);
        tester.print("value:", (*iter).second);
        tester.print("iter_and_bool = ma.insert(ft::pair<const int, char>(3, 'c'));");
        iter_and_bool = ma.insert(ft::pair<const int, char>(3, 'c'));
        tester.if_print("insert ok:", iter_and_bool.second);
        iter = iter_and_bool.first;
        tester.print("index:", (*iter).first);
        tester.print("value:", (*iter).second);
        tester.print("iter_and_bool = ma.insert(ft::pair<const int, char>(2, 'b'));");
        iter_and_bool = ma.insert(ft::pair<const int, char>(2, 'b'));
        tester.if_print("insert ok:", iter_and_bool.second);
        iter = iter_and_bool.first;
        tester.print("index:", (*iter).first);
        tester.print("value:", (*iter).second);

        iter = ma.begin();
        ft::map<int, char>::iterator end = ma.end();
        tester.print("for (iter = ma.begin(); iter != ma.end; ++iter)...");
        for (; iter != end; ++iter)
        {
            tester.print("index:", (*iter).first);
            tester.print("value:", (*iter).second);
        }

        tester.print("ma.erase(++(ma.begin()));");
        ma.erase(++(ma.begin()));
        iter = ma.begin();
        end = ma.end();
        tester.print("for (iter = ma.begin(); iter != ma.end; ++iter)...");
        for (; iter != end; ++iter)
        {
            tester.print("index:", (*iter).first);
            tester.print("value:", (*iter).second);
        }
    }
    tester.print("");
    tester.print("iterator test");
    {
        tester.print("ft::map<int, char> ma <- (1, 'a'), (2, 'b'), (3, 'c');");
        ft::map<int, char> ma;
        ft::pair<ft::map<int, char>::iterator, bool> iter_and_bool = ma.insert(ft::pair<const int, char>(1, 'a'));
        iter_and_bool = ma.insert(ft::pair<const int, char>(3, 'c'));
        iter_and_bool = ma.insert(ft::pair<const int, char>(2, 'b'));

        tester.print("ft::map<int, char>::iterator it_copy(ma.begin());");
        ft::map<int, char>::iterator it_copy1(ma.begin());
        tester.print("index:", it_copy1->first);
        tester.print("value:", it_copy1->second);

        tester.print("ft::map<int, char>::iterator it_copy(ma.begin());");
        ft::map<int, char>::iterator it_copy2 = ma.begin();
        tester.print("index:", (*it_copy2).first);
        tester.print("value:", (*it_copy2).second);

        it_copy1 = ++it_copy2;
        tester.print("it_copy1 = ++it_copy2");
        tester.print("it_copy1");
        tester.print("index:", (*it_copy1).first);
        tester.print("value:", (*it_copy1).second);
        tester.print("it_copy2");
        tester.print("index:", (*it_copy2).first);
        tester.print("value:", (*it_copy2).second);

        it_copy1 = it_copy2++;
        tester.print("it_copy1 = it_copy2++");
        tester.print("it_copy1");
        tester.print("index:", (*it_copy1).first);
        tester.print("value:", (*it_copy1).second);
        tester.print("it_copy2");
        tester.print("index:", (*it_copy2).first);
        tester.print("value:", (*it_copy2).second);

        it_copy1 = --it_copy2;
        tester.print("it_copy1 = --it_copy2");
        tester.print("it_copy1");
        tester.print("index:", (*it_copy1).first);
        tester.print("value:", (*it_copy1).second);
        tester.print("it_copy2");
        tester.print("index:", (*it_copy2).first);
        tester.print("value:", (*it_copy2).second);

        it_copy1 = it_copy2--;
        tester.print("it_copy1 = it_copy2--");
        tester.print("it_copy1");
        tester.print("index:", (*it_copy1).first);
        tester.print("value:", (*it_copy1).second);
        tester.print("it_copy2");
        tester.print("index:", (*it_copy2).first);
        tester.print("value:", (*it_copy2).second);

        tester.print("it_copy1 = --ma.end();");
        it_copy1 = --ma.end();
        tester.print("it_copy1");
        tester.print("index:", (*it_copy1).first);
        tester.print("value:", (*it_copy1).second);

        tester.print("ft::map<int, char>::const_iterator c_iter1 = ma.begin();");
        ft::map<int, char>::const_iterator c_iter1 = ma.begin();
        tester.print("index:", (*c_iter1).first);
        tester.print("value:", (*c_iter1).second);

        tester.print("ft::map<int, char>::const_iterator c_iter2 = ma.begin();");
        ft::map<int, char>::const_iterator c_iter2(c_iter1);

        c_iter1 = ++c_iter2;
        tester.print("c_iter1 = ++c_iter2");
        tester.print("c_iter1");
        tester.print("index:", (*c_iter1).first);
        tester.print("value:", (*c_iter1).second);
        tester.print("c_iter2");
        tester.print("index:", (*c_iter2).first);
        tester.print("value:", (*c_iter2).second);

        c_iter1 = c_iter2++;
        tester.print("c_iter1 = c_iter2++");
        tester.print("c_iter1");
        tester.print("index:", (*c_iter1).first);
        tester.print("value:", (*c_iter1).second);
        tester.print("c_iter2");
        tester.print("index:", (*c_iter2).first);
        tester.print("value:", (*c_iter2).second);

        c_iter1 = --c_iter2;
        tester.print("c_iter1 = --c_iter2");
        tester.print("c_iter1");
        tester.print("index:", (*c_iter1).first);
        tester.print("value:", (*c_iter1).second);
        tester.print("c_iter2");
        tester.print("index:", (*c_iter2).first);
        tester.print("value:", (*c_iter2).second);

        c_iter1 = c_iter2--;
        tester.print("c_iter1 = c_iter2--");
        tester.print("c_iter1");
        tester.print("index:", (*c_iter1).first);
        tester.print("value:", (*c_iter1).second);
        tester.print("c_iter2");
        tester.print("index:", (*c_iter2).first);
        tester.print("value:", (*c_iter2).second);

        tester.if_print("it_copy1 != c_iter2", it_copy1 != c_iter2);
        tester.if_print("ma.begin() == c_iter2", ma.begin() == c_iter2);
        tester.if_print("c_iter2 != it_copy1", c_iter2 != it_copy1);
        tester.if_print("c_iter2 == ma.begin()", c_iter2 == ma.begin());

        tester.print("ft::map<int, char>::reverse_iterator r_iter1 = ma.rbegin();");
        ft::map<int, char>::reverse_iterator r_iter1 = ma.rbegin();
        for (; r_iter1 != ma.rend(); ++r_iter1)
        {
            tester.print("index:", (*r_iter1).first);
            tester.print("value:", (*r_iter1).second);
        }

        tester.print("r_iter1 = ma.rbegin();");
        r_iter1 = ma.rbegin();
        tester.print("ft::map<int, char>::reverse_iterator r_iter2(r_iter1);");
        ft::map<int, char>::reverse_iterator r_iter2(r_iter1);

        r_iter1 = ++r_iter2;
        tester.print("r_iter1 = ++r_iter2");
        tester.print("r_iter1");
        tester.print("index:", (*r_iter1).first);
        tester.print("value:", (*r_iter1).second);
        tester.print("r_iter2");
        tester.print("index:", (*r_iter2).first);
        tester.print("value:", (*r_iter2).second);

        r_iter1 = r_iter2++;
        tester.print("r_iter1 = r_iter2++");
        tester.print("r_iter1");
        tester.print("index:", (*r_iter1).first);
        tester.print("value:", (*r_iter1).second);
        tester.print("r_iter2");
        tester.print("index:", (*r_iter2).first);
        tester.print("value:", (*r_iter2).second);

        r_iter1 = --r_iter2;
        tester.print("r_iter1 = --r_iter2");
        tester.print("r_iter1");
        tester.print("index:", (*r_iter1).first);
        tester.print("value:", (*r_iter1).second);
        tester.print("r_iter2");
        tester.print("index:", (*r_iter2).first);
        tester.print("value:", (*r_iter2).second);

        tester.print("ft::map<int, char>::const_reverse_iterator cr_iter(r_iter2);");
        ft::map<int, char>::const_reverse_iterator cr_iter(r_iter2);

        tester.if_print("r_iter2 != cr_iter", r_iter2 != cr_iter);
        tester.if_print("r_iter2 == cr_iter", r_iter2 == cr_iter);
        tester.if_print("cr_iter != r_iter2", cr_iter != r_iter2);
        tester.if_print("cr_iter == r_iter2", cr_iter == r_iter2);
    }
    tester.print("");
    tester.print("member classes test");
    tester.print("value_compare test");
    {
        tester.if_print("value_compare::result_type:",
            typeid(ft::map<int, char>::value_compare::result_type) == typeid(bool), "bool", "other");
        tester.if_print("value_compare::first_argument_type:",
            typeid(ft::map<int, char>::value_compare::first_argument_type) == typeid(ft::map<int, char>::value_type), "ft::map<int, char>::value_type", "other");
        tester.if_print("value_compare::result_type:",
            typeid(ft::map<int, char>::value_compare::second_argument_type) == typeid(ft::map<int, char>::value_type), "ft::map<int, char>::value_type", "other");
    }
    tester.print("");
    tester.print("construct and operator= test");
    {
        tester.print("ft::map<int, double> ma;");
        ft::map<int, double> ma;
        tester.print("ma.insert(ft::pair<int, double>(1, 1.5));");
        ma.insert(ft::pair<int, double>(1, 1.5));
        tester.print("ma.insert(ft::pair<int, double>(3, 3.5));");
        ma.insert(ft::pair<int, double>(3, 3.5));
        tester.print("for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);
    }
    tester.print("");
    {
        tester.print("std::greater<int> comp = std::greater<int>();");
        std::greater<int> comp = std::greater<int>();
        tester.print("ft::map<int, double, std::greater<int> > ma(comp);");
        ft::map<int, double, std::greater<int> > ma(comp);
        tester.print("ma.insert(ft::pair<int, double>(1, 1.5));");
        ma.insert(ft::pair<int, double>(1, 1.5));
        tester.print("ma.insert(ft::pair<int, double>(3, 3.5));");
        ma.insert(ft::pair<int, double>(3, 3.5));
        tester.print("for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);
    }
    tester.print("");
    {
        tester.print("std::greater<int> comp = std::greater<int>();");
        std::greater<int> comp = std::greater<int>();
        tester.print("std::allocator<ft::pair<const int, double> > allocator;");
        std::allocator<ft::pair<const int, double> > allocator;
        tester.print("ft::map<int, double, std::greater<int>, std::allocator<ft::pair<const int, double> > > ma(comp, allocator);");
        ft::map<int, double, std::greater<int>, std::allocator<ft::pair<const int, double> > > ma(comp, allocator);
        tester.print("ma.insert(ft::pair<int, double>(1, 1.5));");
        ma.insert(ft::pair<int, double>(1, 1.5));
        tester.print("ma.insert(ft::pair<int, double>(3, 3.5));");
        ma.insert(ft::pair<int, double>(3, 3.5));
        tester.print("for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.print("ft::map<int, double> copy_ma(ma.begin(), ma.end());");
        ft::map<int, double> copy_ma(ma.begin(), ma.end());
        tester.print("for (ft::map<int, double>::iterator iter = copy_ma.begin(); iter != copy_ma.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = copy_ma.begin(); iter != copy_ma.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.print("ft::map<int, double, std::greater<int>, std::allocator<ft::pair<const int, double> > > copy2_ma(ma);");
        ft::map<int, double, std::greater<int>, std::allocator<ft::pair<const int, double> > > copy2_ma(ma);
        tester.print("for (ft::map<int, double>::iterator iter = copy2_ma.begin(); iter != copy2_ma.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = copy2_ma.begin(); iter != copy2_ma.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.print("ft::map<int, double, std::greater<int>, std::allocator<ft::pair<const int, double> > > copy3_ma;");
        ft::map<int, double, std::greater<int>, std::allocator<ft::pair<const int, double> > > copy3_ma;
        tester.print("copy3_ma = ma;");
        copy3_ma = ma;
        tester.print("for (ft::map<int, double>::iterator iter = copy3_ma.begin(); iter != copy3_ma.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = copy3_ma.begin(); iter != copy3_ma.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);
    }
    tester.print("");
    tester.print("get_allocator test");
    {
        tester.print("ft::map<int, double> ma;");
        ft::map<int, double> ma;
        tester.print("ft::map<int, double>::allocator_type allocator = ma.get_allocator();");
        ft::map<int, double>::allocator_type allocator = ma.get_allocator();
        tester.print("ft::pair<const int, double>* data = allocator.allocate(1);");
        ft::pair<const int, double>* data = allocator.allocate(1);
        tester.print("allocator.construct(data, ft::pair<const int, double>(1, 1.5));");
        allocator.construct(data, ft::pair<const int, double>(1, 1.5));
        tester.print("data index, value:", data->first, data->second);
        tester.print("allocator.destroy(data);");
        allocator.destroy(data);
        tester.print("allocator.deallocate(data, 1);");
        allocator.deallocate(data, 1);
    }
    tester.print("");
    tester.print("at test");
    {
        tester.print("ft::map<int, double> ma;");
        ft::map<int, double> ma;
        tester.print("ma.insert(ft::pair<int, double>(1, 1.5));");
        ma.insert(ft::pair<int, double>(1, 1.5));
        tester.print("ma.insert(ft::pair<int, double>(3, 3.5));");
        ma.insert(ft::pair<int, double>(3, 3.5));
        tester.print("ma.at(1):", ma.at(1));
        tester.print("ma.at(3):", ma.at(3));
        try
        {
            tester.print("ma.at(2)", ma.at(2));
        }
        catch(const std::exception& e)
        {
            tester.print("ma.at(2):", e.what());
        }

        tester.print("const ft::map<int, double> ma_copy(ma);");
        const ft::map<int, double> ma_copy(ma);
        tester.print("ma_copy.at(1):", ma_copy.at(1));
        tester.print("ma_copy.at(3):", ma_copy.at(3));
        try
        {
            tester.print("ma_copy.at(2):", ma_copy.at(2));
        }
        catch(const std::exception& e)
        {
            tester.print("ma_copy.at(2):", e.what());
        }
    }
    tester.print("");
    tester.print("operator[] test");
    {
        tester.print("ft::map<int, double> ma;");
        ft::map<int, double> ma;
        tester.print("ma.insert(ft::pair<int, double>(1, 1.5));");
        ma.insert(ft::pair<int, double>(1, 1.5));
        tester.print("ma.insert(ft::pair<int, double>(3, 3.5));");
        ma.insert(ft::pair<int, double>(3, 3.5));
        tester.print("ma[1]:", ma[1]);
        tester.print("ma[3]:", ma[3]);
        tester.print("ma[2]", ma[2]);
        tester.print("ma[1] = 5;");
        ma[1] = 5;
        tester.print("for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);
    }
    tester.print("");
    tester.print("begin, end test");
    {
        tester.print("ft::map<int, double> ma;");
        ft::map<int, double> ma;
        tester.if_print("ma.begin() == ma.end():", ma.begin() == ma.end());

        tester.print("ma.insert(ft::pair<int, double>(1, 1.5));");
        ma.insert(ft::pair<int, double>(1, 1.5));
        tester.print("ma.insert(ft::pair<int, double>(3, 3.5));");
        ma.insert(ft::pair<int, double>(3, 3.5));

        tester.print("for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.print("for end to begin...");
        for (ft::map<int, double>::iterator iter = ma.end();;)
        {
            if (iter == ma.begin())
                break;
            --iter;
            tester.print("index, value:", iter->first, iter->second);
        }

        tester.print("const ft::map<int, double> const_empty_ma;");
        const ft::map<int, double> const_empty_ma;
        tester.if_print("const_empty_ma.begin() == const_empty_ma.end():", const_empty_ma.begin() == const_empty_ma.end());

        tester.print("const ft::map<int, double> const_ma(ma);");
        const ft::map<int, double> const_ma(ma);

        tester.print("for (ft::map<int, double>::const_iterator iter = const_ma.begin(); iter != const_ma.end(); ++iter)...");
        for (ft::map<int, double>::const_iterator iter = const_ma.begin(); iter != const_ma.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.print("for end to begin...");
        for (ft::map<int, double>::const_iterator iter = const_ma.end();;)
        {
            if (iter == const_ma.begin())
                break;
            --iter;
            tester.print("index, value:", iter->first, iter->second);
        }
    }
    tester.print("");
    tester.print("rbegin, rend test");
    {
        tester.print("ft::map<int, double> ma;");
        ft::map<int, double> ma;
        tester.if_print("ma.rbegin() == ma.rend():", ma.rbegin() == ma.rend());

        tester.print("ma.insert(ft::pair<int, double>(1, 1.5));");
        ma.insert(ft::pair<int, double>(1, 1.5));
        tester.print("ma.insert(ft::pair<int, double>(3, 3.5));");
        ma.insert(ft::pair<int, double>(3, 3.5));

        tester.print("for (ft::map<int, double>::reverse_iterator iter = ma.begin(); iter != ma.end(); ++iter)...");
        for (ft::map<int, double>::reverse_iterator iter = ma.rbegin(); iter != ma.rend(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.print("for end to begin...");
        for (ft::map<int, double>::reverse_iterator iter = ma.rend();;)
        {
            if (iter == ma.rbegin())
                break;
            --iter;
            tester.print("index, value:", iter->first, iter->second);
        }

        tester.print("const ft::map<int, double> const_empty_ma;");
        const ft::map<int, double> const_empty_ma;
        tester.if_print("const_empty_ma.begin() == const_empty_ma.end():", const_empty_ma.rbegin() == const_empty_ma.rend());

        tester.print("const ft::map<int, double> const_ma(ma);");
        const ft::map<int, double> const_ma(ma);

        tester.print("for (ft::map<int, double>::const_reverse_iterator iter = const_ma.rbegin(); iter != const_ma.rend(); ++iter)...");
        for (ft::map<int, double>::const_reverse_iterator iter = const_ma.rbegin(); iter != const_ma.rend(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.print("for rend to rbegin...");
        for (ft::map<int, double>::const_reverse_iterator iter = const_ma.rend();;)
        {
            if (iter == const_ma.rbegin())
                break;
            --iter;
            tester.print("index, value:", iter->first, iter->second);
        }
    }
    tester.print("");
    tester.print("empty test");
    {
        tester.print("ft::map<int, double> ma;");
        ft::map<int, double> ma;
        tester.if_print("ma.empty():", ma.empty());
        tester.print("ma.insert(ft::pair<int, double>(1, 1.5));");
        ma.insert(ft::pair<int, double>(1, 1.5));
        tester.if_print("ma.empty():", ma.empty());

        tester.print("const ft::map<int, double> const_empty_ma;");
        const ft::map<int, double> const_empty_ma;
        tester.if_print("const_empty_ma.empty():", const_empty_ma.empty());

        tester.print("const ft::map<int, double> const_ma(ma);");
        const ft::map<int, double> const_ma(ma);
        tester.if_print("const_ma.empty():", const_ma.empty());
    }
    tester.print("");
    tester.print("size test");
    {
        tester.print("ft::map<int, double> ma;");
        ft::map<int, double> ma;
        tester.print("ma.size():", ma.size());

        tester.print("insert (i, -i) i = 0 to 1000");
        for (int i = 0; i < 10000; ++i)
            ma.insert(ft::pair<const int, double>(i, -i));

        tester.print("ma.size():", ma.size());

        tester.print("const ft::map<int, double> ec_ma;");
        const ft::map<int, double> ec_ma;
        tester.print("ma.size():", ec_ma.size());

        tester.print("const ft::map<int, double> c_ma(ma);");
        const ft::map<int, double> c_ma(ma);
        tester.print("ma.size():", c_ma.size());
    }
    tester.print("");
    tester.print("max_size test");
    {
        // Commented out because the values do not match
        tester.print("ft::map<int, char> ma;");
        ft::map<int, char> ma;
        tester.if_print("ma.max_size():", ma.max_size());
        // tester.print("ma.max_size():", ma.max_size());

        tester.print("ft::map<int, double> ma2;");
        ft::map<int, double> ma2;
        tester.if_print("ma.max_size():", ma2.max_size());
        // tester.print("ma.max_size():", ma2.max_size());

        tester.print("ft::map<int, char> c_ma;");
        ft::map<int, char> c_ma;
        tester.if_print("ma.max_size():", c_ma.max_size());
        // tester.print("ma.max_size():", c_ma.max_size());
    }
    tester.print("");
    tester.print("max_size test");
    {
        tester.print("ft::map<int, double> ma;");
        ft::map<int, double> ma;

        tester.print("insert (i, -i) i = 0 to 1000");
        for (int i = 0; i < 10000; ++i)
            ma.insert(ft::pair<const int, double>(i, -i));

        tester.print("ma.size():", ma.size());
        ma.clear();
        tester.print("ma.size():", ma.size());

        tester.print("for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);
    }
    tester.print("");
    tester.print("insert test");
    {
        tester.print("ft::map<int, double> ma;");
        ft::map<int, double> ma;

        tester.print("ft::pair<ft::map<int, double>::iterator, bool> iter_and_bool = ma.insert(ft::pair<const int, double>(3, 1));");
        ft::pair<ft::map<int, double>::iterator, bool> iter_and_bool = ma.insert(ft::pair<const int, double>(3, 1));
        tester.print("iter_and_bool.first:", iter_and_bool.first->first, iter_and_bool.first->second);
        tester.if_print("iter_and_bool.second:", iter_and_bool.second);

        tester.print("iter_and_bool = ma.insert(ft::pair<const int, double>(3, 1));");
        iter_and_bool = ma.insert(ft::pair<const int, double>(3, 1));
        tester.print("iter_and_bool.first:", iter_and_bool.first->first, iter_and_bool.first->second);
        tester.if_print("iter_and_bool.second:", iter_and_bool.second);

        tester.print("ft::map<int, double>::iterator insert_iter = ma.insert(ma.begin(), ft::pair<const int, double>(2, 1));");
        ft::map<int, double>::iterator insert_iter = ma.insert(ma.begin(), ft::pair<const int, double>(2, 1));
        tester.print("insert_iter:", insert_iter->first, insert_iter->second);

        tester.print("insert_iter = ma.insert(ma.begin(), ft::pair<const int, double>(2, 1));");
        insert_iter = ma.insert(ma.begin(), ft::pair<const int, double>(2, 1));
        tester.print("insert_iter:", insert_iter->first, insert_iter->second);

        tester.print("insert_iter = ma.insert(ma.end(), ft::pair<const int, double>(2, 1));");
        insert_iter = ma.insert(ma.end(), ft::pair<const int, double>(4, 1));
        tester.print("insert_iter:", insert_iter->first, insert_iter->second);

        tester.print("ft::vector<ft::pair<int, double>> vec;");
        ft::vector<ft::pair<int, double> > vec;
        tester.print("vec.push_back(ft::pair<int, double>(-1, 2));");
        vec.push_back(ft::pair<int, double>(-1, 2));
        tester.print("vec.push_back(ft::pair<int, double>(-3, 2));");
        vec.push_back(ft::pair<int, double>(-3, 2));
        tester.print("vec.push_back(ft::pair<int, double>(-2, 2));");
        vec.push_back(ft::pair<int, double>(-2, 2));
        tester.print("vec.push_back(ft::pair<int, double>(-2, 2));");
        vec.push_back(ft::pair<int, double>(-2, 3));
        tester.print("ma.insert(vec.begin(), vec.end());");
        ma.insert(vec.begin(), vec.end());

        tester.print("ft::map<int, double> ma2;");
        ft::map<int, double> ma2;
        tester.print("ma2[0] = 2;");
        ma2[0] = 2;
        tester.print("ma2[10] = 2;");
        ma2[10] = 2;
        tester.print("ma2[100] = 2;");
        ma2[100] = 2;
        tester.print("ma.insert(ma2.begin(), ma2.end());");
        ma.insert(ma2.begin(), ma2.end());

        tester.print("for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        // The following is commented out due to error
        // tester.print("ft::map<int, double> ma2;");
        // ft::map<int, double> ma2;
        // ma.insert(ma2.end(), ft::pair<const int, double>(2, 1));
    }
    tester.print("");
    {
        tester.print("ft::map<int, double> ma;");
        ft::map<int, double> ma;

        tester.print("test with 2000 node insert(const value_type& value)");
        for (int i = 0; i < 1000; ++i)
        {
            ma.insert(ft::pair<int, double>((i % 2 ? -1 : 1) * i * 2, i));
        }
        for (int i = 0; i < 1000; ++i)
        {
            ma.insert(ft::pair<int, double>((i % 2 ? -1 : 1) * (i * 2 + 1), i));
        }
        tester.print("ma.size():", ma.size());
        tester.print("test to see if it is sorted");
        ft::map<int, double>::iterator pre_iter;
        bool flag = true;
        for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)
        {
            if (iter != ma.begin())
            {
                if (pre_iter->first >= iter->first)
                {
                    flag = false;
                    break;
                }
            }
            pre_iter = iter;
        }
        if (flag)
            tester.print("Success");
        else
            tester.print("Failure");
    }
    tester.print("");
    {
        tester.print("ft::map<int, double> ma;");
        ft::map<int, double> ma;

        tester.print("test with 2000 node insert(iterator hint, const value_type& value)");
        ft::map<int, double>::iterator pre_iter;
        for (int i = 0; i < 1000; ++i)
        {
            if (i != 0)
                pre_iter = ma.insert(pre_iter, ft::pair<int, double>((i % 2 ? -1 : 1) * i * 2, i));
            else
                pre_iter = ma.insert(ma.end(), ft::pair<int, double>((i % 2 ? -1 : 1) * i * 2, i));
        }
        for (int i = 0; i < 1000; ++i)
        {
            if (i != 0)
                pre_iter = ma.insert(pre_iter, ft::pair<int, double>((i % 2 ? -1 : 1) * (i * 2 + 1), i));
            else
                pre_iter = ma.insert(ma.end(), ft::pair<int, double>((i % 2 ? -1 : 1) * (i * 2 + 1), i));
        }
        tester.print("ma.size():", ma.size());
        tester.print("test to see if it is sorted");
        bool flag = true;
        for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)
        {
            if (iter != ma.begin())
            {
                if (pre_iter->first >= iter->first)
                {
                    flag = false;
                    break;
                }
            }
            pre_iter = iter;
        }
        if (flag)
            tester.print("Success");
        else
            tester.print("Failure");
    }
    tester.print("");
    {
        tester.print("ft::map<int, double> ma;");
        ft::map<int, double> ma;

        tester.print("ma[0] = 2;");
        ma[0] = 2;
        tester.print("ma[2] = 4;");
        ma[2] = 4;

        tester.print("ft::map<int, double>::iterator begin = ma.begin();");
        ft::map<int, double>::iterator begin = ma.begin();
        tester.print("ft::map<int, double>::iterator end = ma.end();");
        ft::map<int, double>::iterator end = ma.end();

        tester.print("ma.insert(ft::pair<int, double>(4, 8));");
        ma.insert(ft::pair<int, double>(4, 8));

        tester.print("for (ft::map<int, double>::iterator iter = begin; iter != end; ++iter)...");
        for (ft::map<int, double>::iterator iter = begin; iter != end; ++iter)
            tester.print("index, value:", iter->first, iter->second);
    }
    tester.print("");
    tester.print("erase test");
    {
        tester.print("ft::map<int, double> ma;");
        ft::map<int, double> ma;

        tester.print("insert 0~4");
        ma[0] = 1;
        ma[1] = 2;
        ma[2] = 3;
        ma[3] = 4;
        ma[4] = 5;
        tester.print("for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.print("ma.erase(ma.begin());");
        ma.erase(ma.begin());
        tester.print("for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.print("ma.erase(3);");
        tester.if_print("removed:", ma.erase(3));
        tester.print("for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.print("ma.erase(0);");
        tester.if_print("removed:", ma.erase(0));

        tester.print("ma.erase(++(ma.begin()), ma.end());");
        ma.erase(++(ma.begin()), ma.end());
        tester.print("for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.print("ma.erase(ma.begin(), ma.begin());");
        ma.erase(ma.begin(), ma.begin());
        tester.print("for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);
    }
    tester.print("");
    {
        tester.print("ft::map<int, double> ma;");
        ft::map<int, double> ma;

        tester.print("ma[0] = 2;");
        ma[0] = 2;
        tester.print("ma[2] = 4;");
        ma[2] = 4;
        tester.print("ma[2] = 4;");
        ma[4] = 8;

        tester.print("ft::map<int, double>::iterator begin = ma.begin();");
        ft::map<int, double>::iterator begin = ma.begin();
        tester.print("ft::map<int, double>::iterator end = ma.end();");
        ft::map<int, double>::iterator end = ma.end();

        tester.print("ma.erase(2);");
        ma.erase(2);

        tester.print("for (ft::map<int, double>::iterator iter = begin; iter != end; ++iter)...");
        for (ft::map<int, double>::iterator iter = begin; iter != end; ++iter)
            tester.print("index, value:", iter->first, iter->second);
    }
    tester.print("");
    tester.print("swap test");
    {
        tester.print("ft::map<int, double> ma1;");
        ft::map<int, double> ma1;
        tester.print("ft::map<int, double> ma2;");
        ft::map<int, double> ma2;

        ma1[0] = 2;
        ma1[2] = 3;
        ma1[4] = 4;
        ma1[6] = 5;
        ma2[1] = 2;
        ma2[3] = 3;
        ma2[5] = 4;
        ma2[6] = 5;

        tester.print("for (ft::map<int, double>::iterator iter = ma1.begin(); iter != ma1.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma1.begin(); iter != ma1.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);
        tester.print("for (ft::map<int, double>::iterator iter = ma2.begin(); iter != ma2.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma2.begin(); iter != ma2.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);
        ma1.swap(ma2);
        tester.print("for (ft::map<int, double>::iterator iter = ma1.begin(); iter != ma1.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma1.begin(); iter != ma1.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);
        tester.print("for (ft::map<int, double>::iterator iter = ma2.begin(); iter != ma2.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma2.begin(); iter != ma2.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);
    }
    tester.print("");
    tester.print("count test");
    {
        tester.print("ft::map<int, double> ma;");
        ft::map<int, double> ma;
        ma[0] = 2;
        ma[2] = 3;
        ma[4] = 4;
        ma[6] = 5;
        tester.print("for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);
        tester.if_print("ma.count(2) == 1", ma.count(2) == 1);
        tester.if_print("ma.count(3) == 0", ma.count(3) == 0);

        tester.print("const ft::map<int, double> ma_copy(ma);");
        const ft::map<int, double> ma_copy(ma);
        tester.if_print("ma_copy.count(2) == 1", ma_copy.count(2) == 1);
        tester.if_print("ma_copy.count(3) == 0", ma_copy.count(3) == 0);
    }
    tester.print("");
    tester.print("find test");
    {
        tester.print("ft::map<int, double> ma;");
        ft::map<int, double> ma;

        ma[0] = 2;
        ma[2] = 3;
        ma[4] = 4;
        ma[6] = 5;
        tester.print("for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.print("ft::map<int, double>::iterator find_iter = ma.find(2);");
        ft::map<int, double>::iterator find_iter = ma.find(2);
        tester.print("find_iter:", find_iter->first, find_iter->second);

        tester.print("find_iter->second = 5;");
        find_iter->second = 5;
        tester.print("find_iter:", find_iter->first, find_iter->second);

        tester.print("find_iter = ma.find(3);");
        find_iter = ma.find(3);
        tester.if_print("find_iter == ma.end()", find_iter == ma.end());

        tester.print("const ft::map<int, double> copy_ma(ma);");
        const ft::map<int, double> copy_ma(ma);
        tester.print("for (ft::map<int, double>::const_iterator iter = copy_ma.begin(); iter != copy_ma.end(); ++iter)...");
        for (ft::map<int, double>::const_iterator iter = copy_ma.begin(); iter != copy_ma.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.print("ft::map<int, double>::const_iterator const_iter = copy_ma.find(2);");
        ft::map<int, double>::const_iterator const_iter = copy_ma.find(2);
        tester.print("const_iter:", const_iter->first, const_iter->second);

        tester.print("const_iter = copy_ma.find(3);");
        const_iter = copy_ma.find(3);
        tester.if_print("const_iter == copy_ma.end()", const_iter == copy_ma.end());
    }
    tester.print("");
    tester.print("equal_range test");
    {
        tester.print("ft::map<int, double> ma;");
        ft::map<int, double> ma;

        ma[0] = 2;
        ma[2] = 3;
        ma[4] = 4;
        ma[6] = 5;
        tester.print("for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.print("ft::pair<ft::map<int, double>::iterator, ft::map<int, double>::iterator> iter_pair = ma.equal_range(2);");
        ft::pair<ft::map<int, double>::iterator, ft::map<int, double>::iterator> iter_pair = ma.equal_range(2);
        for (ft::map<int, double>::iterator iter = iter_pair.first; iter != iter_pair.second; ++iter)
            tester.print("index, value:", iter->first, iter->second);
        tester.print("iter_pair.first->second = 6;");
        iter_pair.first->second = 6;

        tester.print("iter_pair = ma.equal_range(3);");
        iter_pair = ma.equal_range(3);
        tester.if_print("iter_pair.first == iter_pair.second", iter_pair.first == iter_pair.second);
        tester.print("iter_pair.first:", iter_pair.first->first, iter_pair.first->second);

        tester.print("iter_pair = ma.equal_range(100);");
        iter_pair = ma.equal_range(100);
        tester.if_print("iter_pair.first == iter_pair.second", iter_pair.first == iter_pair.second);
        tester.if_print("iter_pair.first == ma.end():", iter_pair.first == ma.end());

        tester.print("const ft::map<int, double> copy_ma(ma);");
        const ft::map<int, double> copy_ma(ma);

        tester.print("ft::pair<ft::map<int, double>::const_iterator, ft::map<int, double>::const_iterator> const_pair = copy_ma.equal_range(2);");
        ft::pair<ft::map<int, double>::const_iterator, ft::map<int, double>::const_iterator> const_pair = copy_ma.equal_range(2);
        for (ft::map<int, double>::const_iterator iter = const_pair.first; iter != const_pair.second; ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.print("const_pair = copy_ma.equal_range(3);");
        const_pair = copy_ma.equal_range(3);
        tester.if_print("const_pair.first == const_pair.second", const_pair.first == const_pair.second);
        tester.print("const_pair.first:", const_pair.first->first, const_pair.first->second);

        tester.print("iter_pair = copy_ma.equal_range(100);");
        const_pair = copy_ma.equal_range(100);
        tester.if_print("const_pair.first == const_pair.second", const_pair.first == const_pair.second);
        tester.if_print("const_pair.first == const_pair.end():", const_pair.first == copy_ma.end());
    }
    tester.print("");
    tester.print("lower_bound test");
    {
        tester.print("ft::map<int, double> ma;");
        ft::map<int, double> ma;

        ma[0] = 2;
        ma[2] = 3;
        ma[4] = 4;
        ma[6] = 5;
        tester.print("for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.print("ft::map<int, double>::iterator lower_iter = ma.lower_bound(2);");
        ft::map<int, double>::iterator lower_iter = ma.lower_bound(2);
        tester.print("index, value:", lower_iter->first, lower_iter->second);
        tester.print("lower_iter->second = 6;");
        lower_iter->second = 6;

        tester.print("lower_iter = ma.lower_bound(3);");
        lower_iter = ma.lower_bound(3);
        tester.print("index, value:", lower_iter->first, lower_iter->second);

        tester.print("lower_iter = ma.lower_bound(100);");
        lower_iter = ma.lower_bound(100);
        tester.if_print("lower_iter == ma.end():", lower_iter == ma.end());

        tester.print("const ft::map<int, double> copy_ma(ma);");
        const ft::map<int, double> copy_ma(ma);

        tester.print("ft::map<int, double>::const_iterator const_pair = copy_ma.lower_bound(2);");
        ft::map<int, double>::const_iterator const_iter = copy_ma.lower_bound(2);
        tester.print("index, value:", const_iter->first, const_iter->second);

        tester.print("const_iter = copy_ma.lower_bound(3);");
        const_iter = copy_ma.lower_bound(3);
        tester.print("index, value:", const_iter->first, const_iter->second);

        tester.print("const_iter = copy_ma.lower_bound(100);");
        const_iter = copy_ma.lower_bound(100);
        tester.if_print("const_iter == const_iter.end():", const_iter == copy_ma.end());
    }
    tester.print("");
    tester.print("upper_bound test");
    {
        tester.print("ft::map<int, double> ma;");
        ft::map<int, double> ma;

        ma[0] = 2;
        ma[2] = 3;
        ma[4] = 4;
        ma[6] = 5;
        tester.print("for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma.begin(); iter != ma.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.print("ft::map<int, double>::iterator lower_iter = ma.upper_bound(2);");
        ft::map<int, double>::iterator lower_iter = ma.upper_bound(2);
        tester.print("index, value:", lower_iter->first, lower_iter->second);
        tester.print("lower_iter->second = 6;");
        lower_iter->second = 6;

        tester.print("lower_iter = ma.upper_bound(3);");
        lower_iter = ma.upper_bound(3);
        tester.print("index, value:", lower_iter->first, lower_iter->second);

        tester.print("lower_iter = ma.upper_bound(100);");
        lower_iter = ma.upper_bound(100);
        tester.if_print("lower_iter == ma.end():", lower_iter == ma.end());

        tester.print("const ft::map<int, double> copy_ma(ma);");
        const ft::map<int, double> copy_ma(ma);

        tester.print("ft::map<int, double>::const_iterator const_pair = copy_ma.upper_bound(2);");
        ft::map<int, double>::const_iterator const_iter = copy_ma.upper_bound(2);
        tester.print("index, value:", const_iter->first, const_iter->second);

        tester.print("const_iter = copy_ma.upper_bound(3);");
        const_iter = copy_ma.upper_bound(3);
        tester.print("index, value:", const_iter->first, const_iter->second);

        tester.print("const_iter = copy_ma.upper_bound(100);");
        const_iter = copy_ma.upper_bound(100);
        tester.if_print("const_iter == const_iter.end():", const_iter == copy_ma.end());
    }
    tester.print("");
    tester.print("key_comp test");
    {
        tester.print("ft::map<char, int, std::greater<char>> ma;");
        ft::map<char, int, std::greater<char> > ma;
        tester.print("ft::pair<const char, int> a('a', 2);");
        ft::pair<const char, int> a('a', 2);
        tester.print("ft::pair<const char, int> b('b', 0);");
        ft::pair<const char, int> b('b', 0);
        tester.print("ft::pair<const char, int> c('c', 4);");
        ft::pair<const char, int> c('c', 4);
        tester.if_print("ma.key_comp()(a.first, b.first):", ma.key_comp()(a.first, b.first));
        tester.if_print("ma.key_comp()(b.first, c.first):", ma.key_comp()(b.first, c.first));
        tester.if_print("ma.key_comp()(c.first, a.first):", ma.key_comp()(c.first, a.first));
    }
    tester.print("");
    tester.print("value_comp test");
    {
        tester.print("ft::map<char, int, std::greater<char>> ma;");
        ft::map<char, int, std::greater<char> > ma;
        tester.print("ft::pair<const char, int> a('a', 2);");
        ft::pair<const char, int> a('a', 2);
        tester.print("ft::pair<const char, int> b('b', 0);");
        ft::pair<const char, int> b('b', 0);
        tester.print("ft::pair<const char, int> c('c', 4);");
        ft::pair<const char, int> c('c', 4);
        tester.if_print("ma.value_comp()(a, b):", ma.value_comp()(a, b));
        tester.if_print("ma.value_comp()(b, c):", ma.value_comp()(b, c));
        tester.if_print("ma.value_comp()(c, a):", ma.value_comp()(c, a));
    }
    tester.print("");
    tester.print("non member classes test");
    tester.print("operator==, !=, <, <=, >, >= test");
    {
        tester.print("ft::map<int, double, std::greater<int> > ma1;");
        ft::map<int, double, std::greater<int> > ma1;
        ma1[0] = 2;
        ma1[2] = 3;
        ma1[4] = 4;
        ma1[6] = 5;
        tester.print("for (ft::map<int, double, std::greater<int> >::iterator iter = ma1.begin(); iter != ma1.end(); ++iter)...");
        for (ft::map<int, double, std::greater<int> >::iterator iter = ma1.begin(); iter != ma1.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.print("ft::map<int, double, std::greater<int> > ma2(ma1);");
        ft::map<int, double, std::greater<int> > ma2(ma1);
        tester.print("for (ft::map<int, double, std::greater<int> >::iterator iter = ma2.begin(); iter != ma2.end(); ++iter)...");
        for (ft::map<int, double, std::greater<int> >::iterator iter = ma2.begin(); iter != ma2.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.print("ft::map<int, double, std::greater<int> > ma3;");
        ft::map<int, double, std::greater<int> > ma3;
        ma3[0] = 2;
        ma3[3] = 3;
        ma3[4] = 4;
        ma3[6] = 5;
        tester.print("for (ft::map<int, double, std::greater<int> >::iterator iter = ma3.begin(); iter != ma3.end(); ++iter)...");
        for (ft::map<int, double, std::greater<int> >::iterator iter = ma3.begin(); iter != ma3.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.print("ft::map<int, double, std::greater<int> > ma4;");
        ft::map<int, double, std::greater<int> > ma4;
        ma4[0] = 2;
        ma4[2] = 3;
        ma4[4] = 5;
        ma4[6] = 5;
        tester.print("for (ft::map<int, double, std::greater<int> >::iterator iter = ma4.begin(); iter != ma4.end(); ++iter)...");
        for (ft::map<int, double, std::greater<int> >::iterator iter = ma4.begin(); iter != ma4.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.print("ft::map<int, double, std::greater<int> > ma5(ma1);");
        const ft::map<int, double, std::greater<int> > ma5(ma1);
        tester.print("for (ft::map<int, double, std::greater<int> >::const_iterator iter = ma5.begin(); iter != ma5.end(); ++iter)...");
        for (ft::map<int, double, std::greater<int> >::const_iterator iter = ma5.begin(); iter != ma5.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.print("ft::map<int, double, std::greater<int> > ma6;");
        ft::map<int, double, std::greater<int> > ma6;
        ma6[0] = 2;
        ma6[2] = 3;
        ma6[4] = 4;
        ma6[6] = 5;
        ma6[7] = 6;
        tester.print("for (ft::map<int, double, std::greater<int> >::iterator iter = ma6.begin(); iter != ma6.end(); ++iter)...");
        for (ft::map<int, double, std::greater<int> >::iterator iter = ma6.begin(); iter != ma6.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.print("ft::map<int, double, std::greater<int> > ma7;");
        ft::map<int, double, std::greater<int> > ma7;
        ma7[-1] = 0;
        ma7[0] = 2;
        ma7[2] = 3;
        ma7[4] = 4;
        ma7[6] = 5;
        tester.print("for (ft::map<int, double, std::greater<int> >::iterator iter = ma7.begin(); iter != ma7.end(); ++iter)...");
        for (ft::map<int, double, std::greater<int> >::iterator iter = ma7.begin(); iter != ma7.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);

        tester.if_print("ma1 == ma2", ma1 == ma2);
        tester.if_print("ma1 == ma3", ma1 == ma3);
        tester.if_print("ma1 == ma4", ma1 == ma4);
        tester.if_print("ma1 == ma5", ma1 == ma5);
        tester.if_print("ma1 == ma6", ma1 == ma6);
        tester.if_print("ma1 == ma7", ma1 == ma7);
        tester.if_print("ma2 == ma1", ma2 == ma1);
        tester.if_print("ma3 == ma1", ma3 == ma1);
        tester.if_print("ma4 == ma1", ma4 == ma1);
        tester.if_print("ma5 == ma1", ma5 == ma1);
        tester.if_print("ma6 == ma1", ma6 == ma1);
        tester.if_print("ma7 == ma1", ma7 == ma1);

        tester.if_print("ma1 != ma2", ma1 != ma2);
        tester.if_print("ma1 != ma3", ma1 != ma3);
        tester.if_print("ma1 != ma4", ma1 != ma4);
        tester.if_print("ma1 != ma5", ma1 != ma5);
        tester.if_print("ma1 != ma6", ma1 != ma6);
        tester.if_print("ma1 != ma7", ma1 != ma7);
        tester.if_print("ma2 != ma1", ma2 != ma1);
        tester.if_print("ma3 != ma1", ma3 != ma1);
        tester.if_print("ma4 != ma1", ma4 != ma1);
        tester.if_print("ma5 != ma1", ma5 != ma1);
        tester.if_print("ma6 != ma1", ma6 != ma1);
        tester.if_print("ma7 != ma1", ma7 != ma1);

        tester.if_print("ma1 < ma2", ma1 < ma2);
        tester.if_print("ma1 < ma3", ma1 < ma3);
        tester.if_print("ma1 < ma4", ma1 < ma4);
        tester.if_print("ma1 < ma5", ma1 < ma5);
        tester.if_print("ma1 < ma6", ma1 < ma6);
        tester.if_print("ma1 < ma7", ma1 < ma7);
        tester.if_print("ma2 < ma1", ma2 < ma1);
        tester.if_print("ma3 < ma1", ma3 < ma1);
        tester.if_print("ma4 < ma1", ma4 < ma1);
        tester.if_print("ma5 < ma1", ma5 < ma1);
        tester.if_print("ma6 < ma1", ma6 < ma1);
        tester.if_print("ma7 < ma1", ma7 < ma1);

        tester.if_print("ma1 <= ma2", ma1 <= ma2);
        tester.if_print("ma1 <= ma3", ma1 <= ma3);
        tester.if_print("ma1 <= ma4", ma1 <= ma4);
        tester.if_print("ma1 <= ma5", ma1 <= ma5);
        tester.if_print("ma1 <= ma6", ma1 <= ma6);
        tester.if_print("ma1 <= ma7", ma1 <= ma7);
        tester.if_print("ma2 <= ma1", ma2 <= ma1);
        tester.if_print("ma3 <= ma1", ma3 <= ma1);
        tester.if_print("ma4 <= ma1", ma4 <= ma1);
        tester.if_print("ma5 <= ma1", ma5 <= ma1);
        tester.if_print("ma6 <= ma1", ma6 <= ma1);
        tester.if_print("ma7 <= ma1", ma7 <= ma1);

        tester.if_print("ma1 > ma2", ma1 > ma2);
        tester.if_print("ma1 > ma3", ma1 > ma3);
        tester.if_print("ma1 > ma4", ma1 > ma4);
        tester.if_print("ma1 > ma5", ma1 > ma5);
        tester.if_print("ma1 > ma6", ma1 > ma6);
        tester.if_print("ma1 > ma7", ma1 > ma7);
        tester.if_print("ma2 > ma1", ma2 > ma1);
        tester.if_print("ma3 > ma1", ma3 > ma1);
        tester.if_print("ma4 > ma1", ma4 > ma1);
        tester.if_print("ma5 > ma1", ma5 > ma1);
        tester.if_print("ma6 > ma1", ma6 > ma1);
        tester.if_print("ma7 > ma1", ma7 > ma1);

        tester.if_print("ma1 >= ma2", ma1 >= ma2);
        tester.if_print("ma1 >= ma3", ma1 >= ma3);
        tester.if_print("ma1 >= ma4", ma1 >= ma4);
        tester.if_print("ma1 >= ma5", ma1 >= ma5);
        tester.if_print("ma1 >= ma6", ma1 >= ma6);
        tester.if_print("ma1 >= ma7", ma1 >= ma7);
        tester.if_print("ma2 >= ma1", ma2 >= ma1);
        tester.if_print("ma3 >= ma1", ma3 >= ma1);
        tester.if_print("ma4 >= ma1", ma4 >= ma1);
        tester.if_print("ma5 >= ma1", ma5 >= ma1);
        tester.if_print("ma6 >= ma1", ma6 >= ma1);
        tester.if_print("ma7 >= ma1", ma7 >= ma1);
    }
    tester.print("swap test");
    {
        tester.print("ft::map<int, double> ma1;");
        ft::map<int, double> ma1;
        tester.print("ft::map<int, double> ma2;");
        ft::map<int, double> ma2;

        ma1[0] = 2;
        ma1[2] = 3;
        ma1[4] = 4;
        ma1[6] = 5;
        ma2[1] = 2;
        ma2[3] = 3;
        ma2[5] = 4;
        ma2[6] = 5;

        tester.print("for (ft::map<int, double>::iterator iter = ma1.begin(); iter != ma1.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma1.begin(); iter != ma1.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);
        tester.print("for (ft::map<int, double>::iterator iter = ma2.begin(); iter != ma2.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma2.begin(); iter != ma2.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);
        ft::swap(ma1, ma2);
        tester.print("for (ft::map<int, double>::iterator iter = ma1.begin(); iter != ma1.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma1.begin(); iter != ma1.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);
        tester.print("for (ft::map<int, double>::iterator iter = ma2.begin(); iter != ma2.end(); ++iter)...");
        for (ft::map<int, double>::iterator iter = ma2.begin(); iter != ma2.end(); ++iter)
            tester.print("index, value:", iter->first, iter->second);
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

    default_test();
    iterators_traits_test();
    enable_if_test();
    is_integral_test();
    equal_test();
    lexicographical_test();
    pair_test();
    make_pair_test();
    reverse_iterator_test();
    vector_test();
    map_test();
}

#if 0 //CREATE A REAL STL EXAMPLE
    #include <map>
    #include <stack>
    #include <vector>
    namespace ft = std;
#else
    #include "is_integral.hpp"
    #include "enable_if.hpp"
    #include "iterator_traits.hpp"
    // #include <map.hpp>
    // #include <stack.hpp>
    // #include <vector.hpp>
#endif

#include <iostream>
#include <string>
#include <deque>
#include <typeinfo>
#include <stdlib.h>
#include "Tester.hpp"

// 仮
#include <vector>

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
        // ft::vector<int> vec;
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

int main(int argc, char** argv) {
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
    is_integral_test();
}

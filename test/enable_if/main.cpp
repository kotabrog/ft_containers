#include <iostream>
#include <vector>
#include <type_traits>

// template<typename T, typename std::enable_if<typeid(T) == typeid(std::vector<int>), T>::type* = nullptr>
template<typename T, typename std::enable_if<std::is_integral<T>::value, T>::type* = nullptr>
void print(T t)
{
    std::cout << "true" << std::endl;
}

template<typename T, typename std::enable_if<!std::is_integral<T>::value, T>::type* = nullptr>
void print(T t)
{
    std::cout << "false" << std::endl;
}


template<typename T, typename std::enable_if<true, T>::type* = nullptr>
void print2(T t)
{
    if (typeid(T) == typeid(typename std::enable_if<true, T>::type))
        std::cout << "typeid true" << std::endl;
    std::cout << "true" << std::endl;
}

template<typename T, typename std::enable_if<false, T>::type* = nullptr>
void print2(T t)
{
    std::cout << "false" << std::endl;
}

int main()
{
    print(1);
    std::vector<int> vec;
    print(vec);
    std::enable_if<true, int>::type x = 1;
    // std::enable_if<false, int>::type x = 1;
    std::cout << x << std::endl;

    print2(1);
    print2(1.5);
}

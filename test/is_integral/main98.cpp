#include <iostream>
#include <iomanip>
#include <typeinfo>

class A {};

template<typename _Tp, _Tp __v>
struct integral_constant
{
    static const _Tp                  value = __v;
    typedef _Tp                           value_type;
    typedef integral_constant<_Tp, __v>   type;
    operator value_type() const { return value; }
};

int main()
{
    std::cout << std::boolalpha;
    std::cout << integral_constant<bool, true>::value << std::endl;
    std::cout << integral_constant<bool, true>() << std::endl;
    std::cout << integral_constant<bool, true>::type::value << std::endl;
}

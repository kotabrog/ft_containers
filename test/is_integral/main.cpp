#include <iostream>
#include <iomanip>
#include <type_traits>

class A {};

#define SHOW(...) std::cout << std::setw(29) << #__VA_ARGS__ << " == " << __VA_ARGS__ << '\n'

int main()
{
    std::cout << std::boolalpha;
    SHOW( std::is_integral<int>::value );
    SHOW( std::is_integral<A>::value );
    SHOW( std::is_integral<int>() );
    SHOW( (std::is_integral<int>() == std::is_integral<int>::value) );
    SHOW( std::is_integral<A>() );

}

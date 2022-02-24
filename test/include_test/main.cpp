#include "main.hpp"
#include <iostream>

int main()
{
    std::cout << "hello" << std::endl;
    test t;
    t.str = "hello";
    std::cout << t.str << std::endl;
}

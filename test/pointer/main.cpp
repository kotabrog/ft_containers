#include <iostream>

int main()
{
    int* arr = new int[3];
    std::cout << arr << std::endl;
    std::cout << ++arr << std::endl;
    std::cout << ++arr << std::endl;
}
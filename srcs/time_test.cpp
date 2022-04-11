#include <vector.hpp>

#include "Tester.hpp"

void push_back_allocate_test()
{
    std::vector<int> vec;
    size_t capacity = 0;

    for (int i = 0; i < 1000; ++i)
    {
        vec.push_back(i);
        if (vec.capacity() != capacity)
        {
            capacity = vec.capacity();
            std::cout << i << ": " << capacity << std::endl;
        }
    }
}

int main()
{
    push_back_allocate_test();
    /*
    Tester tester;

    ft::vector<int> vec1;
    tester.set_time("ft push_back start");
    for (int i = 0; i < 10000; ++i)
    {
        vec1.push_back(i);
    }
    tester.set_time("ft push_back end 10000");

    std::vector<int> vec2;
    tester.set_time("std push_back start", true);
    for (int i = 0; i < 10000; ++i)
    {
        vec2.push_back(i);
    }
    tester.set_time("std push_back end 10000");
    tester.put_all_time();
    */
}

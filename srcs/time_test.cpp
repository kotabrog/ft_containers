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


void push_back_allocate_test2()
{
    size_t capacity = 0;
    for (int i = 0; i < 1000; ++i)
    {
        std::vector<int> vec;
        vec.resize(i);
        vec.push_back(i);
        if (vec.capacity() != capacity)
        {
            capacity = vec.capacity();
            std::cout << i << ": " << capacity << std::endl;
        }
    }
}


void insert_allocate_test()
{
    std::vector<int> vec;
    size_t capacity = 0;

    for (int i = 0; i < 1000; ++i)
    {
        vec.insert(vec.end(), i);
        if (vec.capacity() != capacity)
        {
            capacity = vec.capacity();
            std::cout << i << ": " << capacity << std::endl;
        }
    }
}


void insert_allocate_test2()
{
    size_t capacity = 0;

    for (int i = 1; i < 1000; ++i)
    {
        std::vector<int> vec;
        std::vector<int> vec2(i, 1);
        vec.insert(vec.end(), vec2.begin(), vec2.end());
        if (vec.capacity() != capacity)
        {
            capacity = vec.capacity();
            std::cout << i << ": " << capacity << std::endl;
        }
    }
}


void resize_allocate_test()
{
    std::vector<int> vec;
    size_t capacity = 0;

    for (int i = 0; i < 1000; ++i)
    {
        vec.resize(i);
        if (vec.capacity() != capacity)
        {
            capacity = vec.capacity();
            std::cout << i << ": " << capacity << std::endl;
        }
    }
}


void check_2function_time(void (*func1)(Tester&), void (*func2)(Tester&))
{
    Tester tester1;
    Tester tester2;
    func1(tester1);
    func2(tester2);
    size_t test_size = tester1.get_saved_time_size();
    if (test_size != tester2.get_saved_time_size())
    {
        std::cout << "check_2function_time: size error" << std::endl;
        return ;
    }
    for (size_t i = 1; i < test_size; ++i)
    {
        double time1 = tester1.get_elapsed_time(i);
        double time2 = tester2.get_elapsed_time(i);
        if (time1 < time2 * 20)
            std::cout << "ok: " << time1 << " " << time2 << std::endl;
        else
            std::cout << "no: " << time1 << " " << time2 << std::endl;
    }
}


void test_push_back_ft(Tester& tester)
{
    ft::vector<int> vec;
    tester.set_time("ft push_back start");
    for (int i = 0; i < 10000; ++i)
    {
        vec.push_back(i);
    }
    tester.set_time("ft push_back end 10000");
}


void test_push_back_std(Tester& tester)
{
    std::vector<int> vec;
    tester.set_time("std push_back start");
    for (int i = 0; i < 10000; ++i)
    {
        vec.push_back(i);
    }
    tester.set_time("std push_back end 10000");
}


void test_copy_ft(Tester& tester)
{
    ft::vector<int> vec1(1000);
    ft::vector<ft::vector<int> > vec2;
    vec2.resize(10000, ft::vector<int>(1000));
    tester.set_time("ft copy start");
    for (int i = 0; i < 10000; ++i)
    {
        vec2[i] = vec1;
    }
    tester.set_time("ft copy end 10000");
}


void test_copy_std(Tester& tester)
{
    std::vector<int> vec1(1000);
    std::vector<std::vector<int> > vec2;
    vec2.resize(10000, std::vector<int>());
    tester.set_time("std copy start");
    for (int i = 0; i < 10000; ++i)
    {
        vec2[i] = vec1;
    }
    tester.set_time("std copy end 10000");
}


int main()
{
    // push_back_allocate_test();
    // push_back_allocate_test2();
    // insert_allocate_test();
    // insert_allocate_test2();
    // resize_allocate_test();
    Tester tester;
    tester.print("test_push_back");
    check_2function_time(test_push_back_ft, test_push_back_std);
    tester.print("test_copy");
    check_2function_time(test_copy_ft, test_copy_std);
}

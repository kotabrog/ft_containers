#include <iostream>
#include <typeinfo>
#include <iterator>
#include <vector>

int main()
{
    if (typeid(std::vector<int>::value_type) == typeid(int))
        std::cout << "value_type: ok" << std::endl;
    if (typeid(std::vector<int>::allocator_type) == typeid(std::allocator<int>))
        std::cout << "allocator_type: ok" << std::endl;
    if (typeid(std::vector<int>::size_type) == typeid(std::size_t))
        std::cout << "size_type: ok" << std::endl;
    if (typeid(std::vector<int>::difference_type) == typeid(std::ptrdiff_t))
        std::cout << "difference_type: ok" << std::endl;
    if (typeid(std::vector<int>::reference) == typeid(std::vector<int>::value_type&))
        std::cout << "reference: ok" << std::endl;
    if (typeid(std::vector<int>::const_reference) == typeid(const std::vector<int>::value_type&))
        std::cout << "const_reference: ok" << std::endl;
    if (typeid(std::vector<int>::pointer) == typeid(std::allocator<int>::pointer))
        std::cout << "pointer: ok" << std::endl;
    if (typeid(std::vector<int>::const_pointer) == typeid(std::allocator<int>::const_pointer))
        std::cout << "const_pointer: ok" << std::endl;
    if (typeid(std::iterator_traits<std::vector<int>::iterator>::difference_type) == typeid(std::ptrdiff_t))
        std::cout << "iterator difference_type: ok" << std::endl;
    if (typeid(std::iterator_traits<std::vector<int>::iterator>::value_type) == typeid(int))
        std::cout << "iterator value_type: ok" << std::endl;
    if (typeid(std::iterator_traits<std::vector<int>::iterator>::pointer) == typeid(int*))
        std::cout << "iterator pointer: ok" << std::endl;
    if (typeid(std::iterator_traits<std::vector<int>::iterator>::reference) == typeid(int&))
        std::cout << "iterator reference: ok" << std::endl;
    if (typeid(std::iterator_traits<std::vector<int>::iterator>::iterator_category) == typeid(std::random_access_iterator_tag))
        std::cout << "iterator iterator_category: ok" << std::endl;
    if (typeid(std::iterator_traits<std::vector<int>::const_iterator>::difference_type) == typeid(std::ptrdiff_t))
        std::cout << "const_iterator difference_type: ok" << std::endl;
    if (typeid(std::iterator_traits<std::vector<int>::const_iterator>::value_type) == typeid(int))
        std::cout << "const_iterator value_type: ok" << std::endl;
    if (typeid(std::iterator_traits<std::vector<int>::const_iterator>::pointer) == typeid(const int*))
        std::cout << "const_iterator pointer: ok" << std::endl;
    if (typeid(std::iterator_traits<std::vector<int>::const_iterator>::reference) == typeid(const int&))
        std::cout << "const_iterator reference: ok" << std::endl;
    if (typeid(std::iterator_traits<std::vector<int>::const_iterator>::iterator_category) == typeid(std::random_access_iterator_tag))
        std::cout << "const_iterator iterator_category: ok" << std::endl;
    if (typeid(std::vector<int>::reverse_iterator) == typeid(std::reverse_iterator<std::vector<int>::iterator>))
        std::cout << "reverse_iterator: ok" << std::endl;
    if (typeid(std::vector<int>::const_reverse_iterator) == typeid(std::reverse_iterator<std::vector<int>::const_iterator>))
        std::cout << "const_reverse_iterator: ok" << std::endl;
    
    {
        std::vector<int> vec;
        std::cout << "std::vector<int> vec: size: " << vec.size() << std::endl;
    }
    {
        std::allocator<int> alloc;
        std::vector<int> vec(alloc);
        std::allocator<int> temp = vec.get_allocator();
        if (alloc == temp)
            std::cout << "constructor vec(alloc): ok" << std::endl;
    }
    {
        int count = 10;
        int value = 1;
        std::vector<int> vec(count, value);
        int i = 0;
        for (; i < count; ++i)
        {
            if (vec[i] != value)
                break;
        }
        if (i == count)
            std::cout << "constructor vec(count, value): ok" << std::endl;
    }
    {
        std::allocator<int> alloc;
        int count = 10;
        int value = 1;
        std::vector<int> vec(count, value, alloc);
        int i = 0;
        for (; i < count; ++i)
        {
            if (vec[i] != value)
                break;
        }
        if (i == count)
            std::cout << "constructor vec(count, value, alloc): ok" << std::endl;

        std::vector<int> vec2(vec.begin(), vec.end());
        for (; i < count; ++i)
        {
            if (vec2[i] != value)
                break;
        }
        if (i == count)
            std::cout << "vec2(vec.begin(), vec.end()): ok" << std::endl;

        std::vector<int> vec3(vec.begin(), vec.end(), alloc);
        for (; i < count; ++i)
        {
            if (vec3[i] != value)
                break;
        }
        if (i == count)
            std::cout << "vec3(vec.begin(), vec.end(), alloc): ok" << std::endl;

        std::vector<int> vec4(vec);
        for (; i < count; ++i)
        {
            if (vec4[i] != value)
                break;
        }
        if (i == count)
            std::cout << "vec4(vec): ok" << std::endl;

        std::vector<int> vec5;
        vec5 = vec;
        for (; i < count; ++i)
        {
            if (vec5[i] != value)
                break;
        }
        if (i == count)
            std::cout << "vec5 = vec: ok" << std::endl;

        vec[0] = 2;
        std::cout << "vec:" << vec[0] << std::endl;
        std::cout << "vec2:" << vec2[0] << std::endl;
        std::cout << "vec3:" << vec3[0] << std::endl;
        std::cout << "vec4:" << vec4[0] << std::endl;
        std::cout << "vec5:" << vec5[0] << std::endl;
    }
    {
        std::vector<char> vec;
        vec.assign(5, 'a');
        for (int i = 0; i < vec.size(); ++i)
            std::cout << vec[i] << " ";
        std::cout << std::endl;
        std::string str(6, 'b');
        vec.assign(str.begin(), str.end());
        for (int i = 0; i < vec.size(); ++i)
            std::cout << vec[i] << " ";
        std::cout << std::endl;
    }
    {
        std::vector<int> vec(6, 1);
        for (int i = 0; i < vec.size(); ++i)
            std::cout << vec.at(i) << " ";
        std::cout << std::endl;
        try
        {
            vec.at(vec.size()) = 1;
        }
        catch(const std::exception& e)
        {
            std::cout << "vec[vec.size()] = 1 is error" << std::endl;
            std::cout << e.what() << std::endl;
        }
        vec.at(1) = 10;
        std::cout << "vec[1] = 10 -> " << vec.at(1) << std::endl;
    }
    {
        const std::vector<int> vec(6, 1);
        for (int i = 0; i < vec.size(); ++i)
            std::cout << vec.at(i) << " ";
        std::cout << std::endl;
    }
    {
        std::vector<int> vec(6, 1);
        std::cout << vec[0] << std::endl;
        vec[0] = 2;
        std::cout << vec[0] << std::endl;
    }
    {
        const std::vector<int> vec(6, 1);
        std::cout << vec[0] << std::endl;
    }
    {
        std::vector<char> str(5, 'c');
        if (&str.front() == &(str[0]))
            std::cout << "str.front() is front" << std::endl;
        std::cout << str.front() << std::endl;
        str.front() = 'a';
        std::cout << str.front() << std::endl;
    }
    {
        const std::vector<char> str(5, 'c');
        std::cout << str.front() << std::endl;
    }
    {
        std::vector<char> str(5, 'c');
        if (&str.back() == &(str[str.size() - 1]))
            std::cout << "str.back() is back" << std::endl;
        std::cout << str.back() << std::endl;
        str.back() = 'a';
        std::cout << str.back() << std::endl;
    }
    {
        const std::vector<char> str(5, 'c');
        std::cout << str.back() << std::endl;
    }
    {
        std::vector<int> vec(6, 1);
        int* data = vec.data();
        for (int i = 0; i < vec.size(); ++i)
            std::cout << data[i] << " ";
        std::cout << std::endl;
        data[0] = 2;
        std::cout << data[0] << std::endl;
        std::cout << vec[0] << std::endl;
    }
    {
        const std::vector<int> vec(6, 1);
        const int* data = vec.data();
        for (int i = 0; i < vec.size(); ++i)
            std::cout << data[i] << " ";
        std::cout << std::endl;
    }
    {
        std::vector<int> vec;
        int* data = vec.data();
        if (data == NULL)
            std::cout << "data is NULL" << std::endl;
    }
    {
        std::vector<int> vec(6, 1);
        std::vector<int>::iterator begin = vec.begin();
        std::vector<int>::iterator end = vec.end();
        for (; begin != end; ++begin)
            std::cout << *begin << " ";
        std::cout << std::endl;
        begin = vec.begin();
        *begin = 2;
        std::cout << vec[0] << std::endl;
    }
    {
        std::vector<int> vec;
        std::vector<int>::iterator begin = vec.begin();
        std::vector<int>::iterator end = vec.end();
        if (begin == end)
            std::cout << "if vec was empty then begin == end" << std::endl;
    }
    {
        const std::vector<int> vec(6, 1);
        std::vector<int>::const_iterator begin = vec.begin();
        std::vector<int>::const_iterator end = vec.end();
        for (; begin != end; ++begin)
            std::cout << *begin << " ";
        std::cout << std::endl;
    }
        {
        std::vector<int> vec(6, 1);
        std::vector<int>::reverse_iterator rbegin = vec.rbegin();
        std::vector<int>::reverse_iterator rend = vec.rend();
        for (; rbegin != rend; ++rbegin)
            std::cout << *rbegin << " ";
        std::cout << std::endl;
        rbegin = vec.rbegin();
        *rbegin = 2;
        std::cout << vec[vec.size() - 1] << std::endl;
    }
    {
        std::vector<int> vec;
        std::vector<int>::reverse_iterator rbegin = vec.rbegin();
        std::vector<int>::reverse_iterator rend = vec.rend();
        if (rbegin == rend)
            std::cout << "if vec was empty then rbegin == rend" << std::endl;
    }
    {
        const std::vector<int> vec(6, 1);
        std::vector<int>::const_reverse_iterator rbegin = vec.rbegin();
        std::vector<int>::const_reverse_iterator rend = vec.rend();
        for (; rbegin != rend; ++rbegin)
            std::cout << *rbegin << " ";
        std::cout << std::endl;
    }
    {
        std::vector<int> vec;
        std::cout << "vec is empty: " << vec.empty() << std::endl;
    }
    {
        std::vector<int> vec1;
        std::vector<char> vec2(5, 'a');
        std::cout << "empty vec size: " << vec1.size() << std::endl;
        std::cout << "5 char vec size: " << vec2.size() << std::endl;
    }
    {
        std::vector<char> s;
        std::cout << "Maximum size of a 'vector' is " << s.max_size() << std::endl;
    }
    {
        std::vector<int> vec;
        std::cout << "capacity: " << vec.capacity() << std::endl;
        vec.push_back(1);
        std::cout << "push_back -> " << vec.capacity() << std::endl;
        vec.reserve(10);
        std::cout << "reserve 10 -> " << vec.capacity() << std::endl;
        std::cout << vec[0] << std::endl;
        vec.reserve(5);
        std::cout << "reserve 5 -> " << vec.capacity() << std::endl;
        std::cout << "reserve max + 1 size: " << vec.max_size() + 1 << std::endl;
        try
        {
           vec.reserve(vec.max_size() + 1);
        }
        catch(const std::length_error& e)
        {
            std::cout << "std::length_error: " <<  e.what() << '\n';
        }
        catch(const std::exception& e)
        {
            std::cout << "std::exception: " <<  e.what() << '\n';
        }
    }
    {
        std::vector<int> vec(6, 1);
        std::cout << "capacity: " << vec.capacity() << std::endl;
        std::cout << "size: " << vec.size() << std::endl;
        vec.clear();
        std::cout << "vec clear" << std::endl;
        std::cout << "capacity: " << vec.capacity() << std::endl;
        std::cout << "size: " << vec.size() << std::endl;
    }
    {
        std::vector<int> vec(5, 1);
        std::vector<int>::iterator iter = vec.insert(vec.begin() + 1, 2);
        std::cout << vec[1] << std::endl;
        std::cout << vec[2] << std::endl;
        std::cout << *iter << std::endl;
        vec.insert(vec.begin() + 3, 2, 3);
        std::cout << vec[3] << std::endl;
        std::cout << vec[4] << std::endl;
        std::cout << vec[5] << std::endl;
        std::vector<int> src(5, 4);
        vec.insert(vec.begin() + 5, src.begin(), src.begin() + 2);
        std::cout << vec[5] << std::endl;
        std::cout << vec[6] << std::endl;
        std::cout << vec[7] << std::endl;
    }
    {
        std::vector<int> vec(5, 1);
        vec.reserve(10);
        std::cout << "reserve 10 -> " << vec.capacity() << std::endl;
        std::cout << vec[0] << std::endl;
        vec.insert(vec.begin(), 2);
        std::cout << "vec.insert(vec.begin(), 2) -> " << vec.capacity() << std::endl;
        std::cout << vec[0] << std::endl;
        vec.insert(vec.begin(), 10, 5);
        std::cout << "vec.insert(vec.begin(), 10, 5) -> " << vec.capacity() << std::endl;
        std::cout << vec[0] << std::endl;
    }
    {
        std::vector<int> vec;
        for (int i = 0; i < 5; ++i)
            vec.push_back(i);
        for (int i = 0; i < vec.size(); ++i)
            std::cout << vec[i] << ' ';
        std::cout << std::endl;
        std::vector<int>::iterator iter = vec.erase(vec.begin() + 1);
        for (int i = 0; i < vec.size(); ++i)
            std::cout << vec[i] << ' ';
        std::cout << std::endl;
        std::cout << *iter << std::endl;
        iter = vec.erase(vec.begin(), vec.begin() + 2);
        for (int i = 0; i < vec.size(); ++i)
            std::cout << vec[i] << ' ';
        std::cout << std::endl;
        std::cout << *iter << std::endl;
        iter = vec.erase(vec.begin(), vec.begin());
        for (int i = 0; i < vec.size(); ++i)
            std::cout << vec[i] << ' ';
        std::cout << std::endl;
        std::cout << *iter << std::endl;
        std::cout << vec.capacity() << std::endl;
    }
    {
        std::vector<int> vec(3, 1);
        vec.push_back(2);
        std::cout << vec[3] << std::endl;
        vec.pop_back();
        std::cout << vec.size() << std::endl;
        vec.pop_back();
        std::cout << vec.size() << std::endl;
        vec.pop_back();
        std::cout << vec.size() << std::endl;
        vec.pop_back();
        std::cout << vec.size() << std::endl;
    }
    {
        std::vector<int> vec(3, 1);
        vec.resize(5);
        for (int i = 0; i < vec.size(); ++i)
            std::cout << vec[i] << ' ';
        std::cout << std::endl;
        std::cout << vec.capacity() << std::endl;
        vec.resize(2);
        for (int i = 0; i < vec.size(); ++i)
            std::cout << vec[i] << ' ';
        std::cout << std::endl;
        std::cout << vec.capacity() << std::endl;
    }
    {
        std::vector<int> vec1(3, 1);
        std::vector<int> vec2(5, 2);
        for (int i = 0; i < vec1.size(); ++i)
            std::cout << vec1[i] << ' ';
        std::cout << std::endl;
        for (int i = 0; i < vec2.size(); ++i)
            std::cout << vec2[i] << ' ';
        std::cout << std::endl;
        vec1.swap(vec2);
        for (int i = 0; i < vec1.size(); ++i)
            std::cout << vec1[i] << ' ';
        std::cout << std::endl;
        for (int i = 0; i < vec2.size(); ++i)
            std::cout << vec2[i] << ' ';
        std::cout << std::endl;
    }
    {
        std::vector<int> vec1;
        std::vector<int> vec2;
        std::vector<int> vec3;
        std::vector<int> vec4;
    
        for (int i = 0; i < 3; ++i)
            vec1.push_back(i);
        for (int i = 0; i < 4; ++i)
            vec2.push_back(i);
        for (int i = 0; i < 3; ++i)
            vec3.push_back(i + 1);
        for (int i = 0; i < 3; ++i)
            vec4.push_back(i);

        std::cout << std::boolalpha;
    
        // Compare non size containers
        std::cout << "vec1 == vec2 returns " << (vec1 == vec2) << '\n';
        std::cout << "vec1 != vec2 returns " << (vec1 != vec2) << '\n';
        std::cout << "vec1 <  vec2 returns " << (vec1 < vec2) << '\n';
        std::cout << "vec1 <= vec2 returns " << (vec1 <= vec2) << '\n';
        std::cout << "vec1 >  vec2 returns " << (vec1 > vec2) << '\n';
        std::cout << "vec1 >= vec2 returns " << (vec1 >= vec2) << '\n';
    
        std::cout << '\n';
    
        // Compare non equal containers
        std::cout << "vec1 == vec3 returns " << (vec1 == vec3) << '\n';
        std::cout << "vec1 != vec3 returns " << (vec1 != vec3) << '\n';
        std::cout << "vec1 <  vec3 returns " << (vec1 < vec3) << '\n';
        std::cout << "vec1 <= vec3 returns " << (vec1 <= vec3) << '\n';
        std::cout << "vec1 >  vec3 returns " << (vec1 > vec3) << '\n';
        std::cout << "vec1 >= vec3 returns " << (vec1 >= vec3) << '\n';

        std::cout << '\n';

        // Compare equal containers
        std::cout << "vec1 == vec4 returns " << (vec1 == vec4) << '\n';
        std::cout << "vec1 != vec4 returns " << (vec1 != vec4) << '\n';
        std::cout << "vec1 <  vec4 returns " << (vec1 < vec4) << '\n';
        std::cout << "vec1 <= vec4 returns " << (vec1 <= vec4) << '\n';
        std::cout << "vec1 >  vec4 returns " << (vec1 > vec4) << '\n';
        std::cout << "vec1 >= vec4 returns " << (vec1 >= vec4) << '\n';
    }
    {
        std::vector<int> vec1(3, 1);
        std::vector<int> vec2(5, 2);
        for (int i = 0; i < vec1.size(); ++i)
            std::cout << vec1[i] << ' ';
        std::cout << std::endl;
        for (int i = 0; i < vec2.size(); ++i)
            std::cout << vec2[i] << ' ';
        std::cout << std::endl;
        std::swap(vec1, vec2);
        for (int i = 0; i < vec1.size(); ++i)
            std::cout << vec1[i] << ' ';
        std::cout << std::endl;
        for (int i = 0; i < vec2.size(); ++i)
            std::cout << vec2[i] << ' ';
        std::cout << std::endl;
    }
}

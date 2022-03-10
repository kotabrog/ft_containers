#include <iostream>
#include <typeinfo>
#include <iterator>
#include <vector>
#include <map>

int main()
{
    std::vector<int> vec;
    for (int i = 0; i < 5; ++i)
    {
        vec.push_back(i);
    }
    std::reverse_iterator<std::vector<int>::iterator> ri1;
    std::reverse_iterator<std::vector<int>::iterator> ri2(vec.begin());
    std::reverse_iterator<std::vector<int>::iterator> ri3(vec.rbegin());
    std::reverse_iterator<std::vector<int>::iterator> ri4(vec.rend());
    for (; ri3 != ri4; ++ri3)
    {
        std::cout << *ri3 << std::endl;
    }

    if (typeid(std::reverse_iterator<std::vector<int>::iterator>::iterator_type) == typeid(std::vector<int>::iterator))
        std::cout << "iterator_type: ok" << std::endl;
    if (typeid(std::reverse_iterator<std::vector<int>::iterator>::iterator_category) == typeid(std::iterator_traits<std::vector<int>::iterator>::iterator_category))
        std::cout << "iterator_category: ok" << std::endl;
    if (typeid(std::reverse_iterator<std::vector<int>::iterator>::value_type) == typeid(std::iterator_traits<std::vector<int>::iterator>::value_type))
        std::cout << "value_type: ok" << std::endl;
    if (typeid(std::reverse_iterator<std::vector<int>::iterator>::difference_type) == typeid(std::iterator_traits<std::vector<int>::iterator>::difference_type))
        std::cout << "difference_type: ok" << std::endl;
    if (typeid(std::reverse_iterator<std::vector<int>::iterator>::pointer) == typeid(std::iterator_traits<std::vector<int>::iterator>::pointer))
        std::cout << "pointer: ok" << std::endl;
    if (typeid(std::reverse_iterator<std::vector<int>::iterator>::reference) == typeid(std::iterator_traits<std::vector<int>::iterator>::reference))
        std::cout << "reference: ok" << std::endl;

    std::reverse_iterator<std::vector<int>::iterator> ri5;
    ri5 = vec.rbegin();
    if (vec.rbegin() == ri5)
        std::cout << "operator=: ok" << std::endl;

    std::vector<int>::iterator vec2 = vec.begin() + 1;
    std::reverse_iterator<std::vector<int>::iterator> ri6(vec2);
    if (ri6.base() == vec2)
        std::cout << "std::reverse_iterator(it).base() == it: ok" << std::endl;
    if (&*(ri6.base() - 1) == &*ri6)
        std::cout << "&*(ri6.base() - 1) == &*ri6: ok" << std::endl;

    std::cout << "*ri:" << *ri6 << std::endl;

    std::map<int, int> map1;
    map1[0] = 1;
    std::reverse_iterator<std::map<int, int>::iterator> ri7(map1.begin());
    std::cout << "map ri->first:" << ri7->first << std::endl;
    std::cout << "map ri->second:" << ri7->second << std::endl;

    for (std::size_t i = 0; i != vec.size(); ++i)
    {
        std::cout << "ri[" << i << "]: " << ri5[i] << std::endl;
    }

    std::cout << "*ri++: " << *ri5++ << std::endl;
    std::cout << "*ri--: " << *ri5-- << std::endl;
    std::cout << "*ri: " << *ri5 << std::endl;
    std::cout << "*++ri: " << *++ri5 << std::endl;
    std::cout << "*--ri: " << *--ri5 << std::endl;
    ri5 = ri5 + 2;
    std::cout << "ri = ri + 2, *ri: " << *ri5 << std::endl;
    ri5 = ri5 - 1;
    std::cout << "ri = ri - 1, *ri: " << *ri5 << std::endl;
    ri5 += 1;
    std::cout << "ri += 1, *ri: " << *ri5 << std::endl;
    ri5 -= 2;
    std::cout << "ri -= 2, *ri: " << *ri5 << std::endl;

    std::reverse_iterator<std::vector<int>::iterator> x = ri5;
    std::reverse_iterator<std::vector<int>::iterator> y = ri5;
    std::reverse_iterator<std::vector<int>::iterator> z = ri5 + 2;

    std::vector<int> vec3(vec);
    std::reverse_iterator<std::vector<int>::const_iterator> ri8(vec3.rbegin());

    std::reverse_iterator<std::vector<int>::const_iterator> x2 = ri8;


    std::cout
        << std::boolalpha
        << "*x == " << *x << '\n' // 4
        << "*y == " << *y << '\n' // 4
        << "*z == " << *z << '\n' // 2
        << "x == y ? " << (x == y) << '\n' // true
        << "x != y ? " << (x != y) << '\n' // false
        << "x <  y ? " << (x <  y) << '\n' // false
        << "x <= y ? " << (x <= y) << '\n' // true
        << "x == z ? " << (x == z) << '\n' // false
        << "x != z ? " << (x != z) << '\n' // true
        << "x <  z ? " << (x <  z) << '\n' // true
        << "x <= z ? " << (x <= z) << '\n' // true
        ;

    if (typeid(std::reverse_iterator<std::vector<int>::const_iterator>::iterator_type) == typeid(std::vector<int>::const_iterator))
        std::cout
            << std::boolalpha
            << "x2 is const_iterator\n"
            << "*x2 == " << *x2 << '\n' // 4
            << "x2 == y ? " << (x2 == y) << '\n' // false
            << "x2 != y ? " << (x2 != y) << '\n' // true
            << "x2 <  y ? " << (x2 <  y) << '\n' // false
            << "x2 <= y ? " << (x2 <= y) << '\n' // false
            << "x2 == z ? " << (x2 == z) << '\n' // false
            << "x2 != z ? " << (x2 != z) << '\n' // true
            << "x2 <  z ? " << (x2 <  z) << '\n' // false
            << "x2 <= z ? " << (x2 <= z) << '\n' // false
            ;

    ri5 = 2 + ri5;
    std::cout << "ri = 2 + ri, *ri: " << *ri5 << std::endl;
    ri5 = -2 + ri5;
    std::cout << "ri = -2 + ri5, *ri: " << *ri5 << std::endl;
}

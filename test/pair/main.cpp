#include <iostream>
#include <utility>
#include <string>
#include <typeinfo>

int main()
{
    // pairオブジェクトの構築
    std::pair<int, std::string> p = std::make_pair(1, "hello");

    // 要素の参照
    std::cout << p.first << std::endl;
    std::cout << p.second << std::endl;

    std::cout << (typeid(std::pair<int, std::string>::first_type) == typeid(int)) << std::endl;
    std::cout << (typeid(std::pair<int, std::string>::second_type) == typeid(std::string)) << std::endl;

    std::pair<int, std::string> p1;
    std::cout << p1.first << std::endl;
    std::cout << p1.second << std::endl;

    std::pair<int, std::string> p2 = p;
    std::cout << p2.first << std::endl;
    std::cout << p2.second << std::endl;

    p2 = p1;
    std::cout << p2.first << std::endl;
    std::cout << p2.second << std::endl;

    std::cout << (p1 == p2) << std::endl;
    std::cout << (p1 != p2) << std::endl;
    std::cout << (p1 < p2) << std::endl;
    std::cout << (p1 <= p2) << std::endl;
    std::cout << (p1 > p2) << std::endl;
    std::cout << (p1 >= p2) << std::endl;

    std::pair<int, std::string> p3(1, "hello000");
    std::cout << p3.first << std::endl;
    std::cout << p3.second << std::endl;

    std::cout << (p == p3) << std::endl;
    std::cout << (p != p3) << std::endl;
    std::cout << (p < p3) << std::endl;
    std::cout << (p <= p3) << std::endl;
    std::cout << (p > p3) << std::endl;
    std::cout << (p >= p3) << std::endl;
}

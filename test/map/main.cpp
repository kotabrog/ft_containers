#include <iostream>
#include <string>
#include <map>
#include <typeinfo>

class Test
{
private:
    int data;
public:
    Test() : data(0) {std::cout << "construct:" << data << std::endl;}
    Test(int x) : data(x) {std::cout << "construct:" << data << std::endl;}
    Test(const Test& temp) : data(temp.data) {std::cout << "construct:" << data << std::endl;}
    Test& operator=(const Test& temp) {this->data = temp.data; std::cout << "copy:" << data << std::endl; return *this;}
    ~Test() {std::cout << "destruct:" << data << std::endl;}

    int get_data() const {return data;}
};

bool operator==(const Test& lhs, const Test& rhs) {return lhs.get_data() == rhs.get_data();}
bool operator!=(const Test& lhs, const Test& rhs) {return lhs.get_data() != rhs.get_data();}
bool operator<(const Test& lhs, const Test& rhs) {return lhs.get_data() < rhs.get_data();}
bool operator>(const Test& lhs, const Test& rhs) {return lhs.get_data() > rhs.get_data();}
bool operator<=(const Test& lhs, const Test& rhs) {return lhs.get_data() <= rhs.get_data();}
bool operator>=(const Test& lhs, const Test& rhs) {return lhs.get_data() >= rhs.get_data();}
std::ostream& operator<<(std::ostream& os, const Test& test) {os << test.get_data(); return os;}

int main()
{
    {
        std::map<Test, int> ma;
        Test v0(0);
        Test v1(1);
        Test v2(2);

        ma[v0] = 1;
        ma[v2] = 3;
        ma[v1] = 2;
        std::cout << "key: " << v0 << ", value: " << ma[v0] << std::endl;
        std::cout << "key: " << v1 << ", value: " << ma[v1] << std::endl;
        std::cout << "key: " << v2 << ", value: " << ma[v2] << std::endl;

        std::map<Test, int>::iterator it = ma.begin();
        std::map<Test, int>::iterator end = ma.end();
        for (; it != end; ++it)
        {
            std::cout << "iter: " << (*it).first << ", " << (*it).second << std::endl;
        }

        std::cout << "erase with key: " << v1 << std::endl;
        std::size_t ret_erase = ma.erase(v1);
        std::cout << "return erase value: " << ret_erase << std::endl;
        for (it = ma.begin(); it != end; ++it)
        {
            std::cout << "iter: " << (*it).first << ", " << (*it).second << std::endl;
        }
    }

    if (typeid(std::map<char, int>::key_type) == typeid(char))
        std::cout << "key_type: ok " << std::endl;
    if (typeid(std::map<char, int>::mapped_type) == typeid(int))
        std::cout << "mapped_type: ok " << std::endl;
    if (typeid(std::map<char, int>::value_type) == typeid(std::pair<const char, int>))
        std::cout << "value_type: ok " << std::endl;
    // if (typeid(std::map<char, int>::value_type) != typeid(std::pair<char, int>))
    //     std::cout << "value_type not const: ok " << std::endl;
    if (typeid(std::map<char, int>::size_type) == typeid(std::size_t))
        std::cout << "size_type: ok " << std::endl;
    if (typeid(std::map<char, int>::difference_type) == typeid(std::ptrdiff_t))
        std::cout << "difference_type: ok " << std::endl;
    if (typeid(std::map<char, int>::key_compare) == typeid(std::less<char>))
        std::cout << "key_compare: ok " << std::endl;
    if (typeid(std::map<char, int>::allocator_type) == typeid(std::allocator<std::pair<const char, int> >))
        std::cout << "allocator_type: ok " << std::endl;
    // if (typeid(std::map<char, int>::allocator_type) != typeid(std::allocator<std::pair<char, int> >))
    //     std::cout << "allocator_type not const: ok " << std::endl;
    if (typeid(std::map<char, int>::reference) == typeid(std::map<char, int>::value_type&))
        std::cout << "reference: ok " << std::endl;
    if (typeid(std::map<char, int>::const_reference) == typeid(const std::map<char, int>::value_type&))
        std::cout << "const_reference: ok " << std::endl;
    if (typeid(std::map<char, int>::pointer) == typeid(std::allocator<std::pair<const char, int> >::pointer))
        std::cout << "pointer: ok " << std::endl;
    if (typeid(std::map<char, int>::const_pointer) == typeid(std::allocator<std::pair<const char, int> >::const_pointer))
        std::cout << "const_pointer: ok " << std::endl;
    if (typeid(std::iterator_traits<std::map<char, int>::iterator>::difference_type) == typeid(std::ptrdiff_t))
        std::cout << "iterator difference_type: ok " << std::endl;
    if (typeid(std::iterator_traits<std::map<char, int>::iterator>::value_type) == typeid(std::pair<const char, int>))
        std::cout << "iterator value_type: ok " << std::endl;
    if (typeid(std::iterator_traits<std::map<char, int>::iterator>::pointer) == typeid(std::pair<const char, int>*))
        std::cout << "iterator pointer: ok " << std::endl;
    if (typeid(std::iterator_traits<std::map<char, int>::iterator>::reference) == typeid(std::pair<const char, int>&))
        std::cout << "iterator reference: ok " << std::endl;
    if (typeid(std::iterator_traits<std::map<char, int>::iterator>::iterator_category) == typeid(std::bidirectional_iterator_tag))
        std::cout << "iterator iterator_category: ok " << std::endl;
    if (typeid(std::iterator_traits<std::map<char, int>::const_iterator>::difference_type) == typeid(std::ptrdiff_t))
        std::cout << "const_iterator difference_type: ok " << std::endl;
    if (typeid(std::iterator_traits<std::map<char, int>::const_iterator>::value_type) == typeid(std::pair<const char, int>))
        std::cout << "const_iterator value_type: ok " << std::endl;
    if (typeid(std::iterator_traits<std::map<char, int>::const_iterator>::pointer) == typeid(const std::pair<const char, int>*))
        std::cout << "const_iterator pointer: ok " << std::endl;
    if (typeid(std::iterator_traits<std::map<char, int>::const_iterator>::reference) == typeid(const std::pair<const char, int>&))
        std::cout << "const_iterator reference: ok " << std::endl;
    if (typeid(std::iterator_traits<std::map<char, int>::const_iterator>::iterator_category) == typeid(std::bidirectional_iterator_tag))
        std::cout << "const_iterator iterator_category: ok " << std::endl;
    if (typeid(std::map<char, int>::reverse_iterator) == typeid(std::reverse_iterator<std::map<char, int>::iterator>))
        std::cout << "reverse_iterator: ok " << std::endl;
    if (typeid(std::map<char, int>::const_reverse_iterator) == typeid(std::reverse_iterator<std::map<char, int>::const_iterator>))
        std::cout << "const_reverse_iterator: ok " << std::endl;

    {
        std::map<char, int> ma;
        ma['a'] = 0;
        ma['b'] = 1;
        ma['f'] = 5;
        ma['d'] = 3;
        ma['c'] = 2;
        ma['e'] = 4;

        std::map<char, int>::iterator it(ma.begin());
        std::map<char, int>::iterator end = ma.end();
        for (; it != end; ++it)
        {
            std::cout << "iter: " << (*it).first << ", " << (*it).second << std::endl;
        }

        std::map<char, int>::iterator copy_it;
        copy_it = ma.begin();
        std::cout << "copy: " << copy_it->first << ", " << copy_it->second << std::endl;
        std::cout << "copy == origin: " << (copy_it == ma.begin()) << std::endl;

        ++copy_it;
        std::cout << "increment copy: " << copy_it->first << ", " << copy_it->second << std::endl;

        copy_it->second = 0;
        std::cout << "increment copy: " << copy_it->first << ", " << copy_it->second << std::endl;
        std::cout << "origin: " << ma['b'] << std::endl;

        std::map<char, int>::iterator copy_it2 = copy_it++;
        std::cout << "increment copy: " << copy_it2->first << ", " << copy_it2->second << std::endl;
        std::cout << "origin: " << copy_it->first << ", " << copy_it->second << std::endl;

        --copy_it;
        std::cout << "decrement copy: " << copy_it->first << ", " << copy_it->second << std::endl;

        copy_it->second = 2;
        std::cout << "decrement copy: " << copy_it->first << ", " << copy_it->second << std::endl;
        std::cout << "origin: " << ma['b'] << std::endl;

        std::map<char, int>::iterator copy_it3 = copy_it--;
        std::cout << "decrement copy: " << copy_it2->first << ", " << copy_it2->second << std::endl;
        std::cout << "origin: " << copy_it->first << ", " << copy_it->second << std::endl;
    }
    {
        std::map<char, int> ma;
        std::cout << "not exist -> " << ma['a'] << std::endl;
    }
}
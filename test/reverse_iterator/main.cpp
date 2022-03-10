#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>

namespace {
    void Println(int elem)
    {
        std::cout << elem << std::endl;
    }
}

int main()
{
    typedef std::list<int> IntList;

    const int table[] = { 0, 1, 2, 3, 4 };

    IntList lst(table, table + 5);

    std::for_each(lst.rbegin(), lst.rend(), Println);
}
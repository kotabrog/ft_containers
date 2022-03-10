#include <iostream>
#include <vector>
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
    typedef std::vector<int> IntVector;

    const int table[] = { 0, 1, 2, 3, 4 };

    IntVector lst(table, table + 5);

    IntVector::const_reverse_iterator rit = lst.rbegin();
    IntVector::const_reverse_iterator ritEnd = lst.rend();

    IntVector::const_iterator it = ritEnd.base();
    IntVector::const_iterator itEnd = rit.base();

    std::for_each(it, itEnd, Println);
}
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

    IntVector::const_iterator it = lst.begin();
    IntVector::const_iterator itEnd = lst.end();

    IntVector::const_reverse_iterator rit(itEnd);
    IntVector::const_reverse_iterator ritEnd(it);

    std::for_each(rit, ritEnd, Println);
}
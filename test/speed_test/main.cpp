#include <iostream>
#include <vector>
#include <time.h>

int main()
{
    std::cout << "clock():\n";
    for (int i = 0; i < 10; ++i)
    {
        std::vector<int> v;
        clock_t start = clock();
        const int N = 1000*10000;
        for (int i = 0; i < N; ++i)
        {
            v.push_back(i);
        }
        clock_t end = clock();
        std::cout << "duration = " << (double)(end - start) / CLOCKS_PER_SEC << "sec.\n";
    }
    return 0;
}

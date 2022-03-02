#include <algorithm>
#include <iostream>
#include <vector>
#include <array>
#include <iterator>

bool p(int x, int y)
{
    return x - 1 <= y && y <= x + 1;
}

int main()
{
    std::vector<int> v;
    std::vector<int> v2;

    for (int i = 0; i < 6; ++i)
    {
        v.push_back(i);
        v2.push_back(i);
    }
    v2[5] += 1;

    // コンテナの中身が同じかどうか調べる
    bool result = std::equal(v.begin(), v.end(), v2.begin());
    std::cout << std::boolalpha << result << std::endl;

    // x±1 の誤差を許すようにする
    bool result2 = std::equal(v.begin(), v.end(), v2.begin(), p);
    std::cout << std::boolalpha << result2 << std::endl;

    v2[5] -= 1;
    bool result3 = std::equal(v.begin(), v.end(), v2.begin(), v2.end());
    std::cout << std::boolalpha << result3 << std::endl;

    v2.push_back(6);
    bool result4 = std::equal(v.begin(), v.end(), v2.begin());
    std::cout << std::boolalpha << result4 << std::endl;

    bool result5 = std::equal(v.begin(), v.end(), v2.begin(), v2.end());
    std::cout << std::boolalpha << result5 << std::endl;

    bool result6 = std::equal(v2.begin(), v2.end(), v.begin());
    std::cout << std::boolalpha << result6 << std::endl;
}
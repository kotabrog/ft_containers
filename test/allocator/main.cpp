#include <memory>
#include <iostream>
#include <algorithm>
#include <numeric>

// https://cpprefjp.github.io/reference/memory/allocator.html

template <typename Alloc, typename Iter>
typename Alloc::template rebind<typename std::iterator_traits<Iter>::value_type>::other
get_alloc_by_iter(Alloc, Iter)
{
    return typename Alloc::template rebind<typename std::iterator_traits<Iter>::value_type>::other();
}

int main(int argc, char** argv)
{
    auto alc = std::allocator<int>();

    // 10要素のint型が入る領域を確保
    int* arr = alc.allocate(10);

    // 確保した領域の各要素を構築する(コンストラクタを呼び出す)
    for (std::size_t i = 0; i != 10; ++i) alc.construct(arr + i);

    std::iota(arr, arr + 10, 0);
    std::for_each(arr, arr + 10, [](int i) { std::cout << i << " "; });
    std::cout << std::endl;

    std::cout << "max_size: " << alc.max_size() << std::endl;

    // 配列の各要素を破棄する(デストラクタを呼び出す)
    for (std::size_t i = 0; i != 10; ++i) alc.destroy(arr + i);

    // 領域を解放する
    alc.deallocate(arr, 10);

    char* arr2;
    std::allocator<int>::template rebind<char>::other alc2 = get_alloc_by_iter(alc, arr2);
    arr2 = alc2.allocate(10);
    alc2.deallocate(arr2, 10);
}
#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft
{
template<typename T>
const T& min(const T& a, const T& b)
{
    return a <= b ? a : b;
}

template<typename T>
const T& max(const T& a, const T& b)
{
    return a >= b ? a : b;
}
} // namespace ft

#endif

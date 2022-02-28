#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

namespace ft
{
template <bool B, class T = void>
struct enable_if
{
    typedef T type;
};

template <class T>
struct enable_if<false, T>
{};

} // namespace ft

#endif

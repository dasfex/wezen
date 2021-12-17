#ifndef CALCOM_MINMAX_HPP
#define CALCOM_MINMAX_HPP

#include <type_traits>

namespace calcom {

template <class T, T lhs, T rhs, class = std::void_t<decltype(std::declval<T>() < std::declval<T>())>>
struct MinT {
    static constexpr T value = lhs < rhs ? lhs : rhs;
};

template <class T, T lhs, T rhs>
constexpr T MinTV = MinT<T, lhs, rhs>::value;

template <int lhs, int rhs>
struct Min : MinT<int, lhs, rhs> {};

template <int lhs, int rhs>
constexpr int MinV = Min<lhs, rhs>::value;

template <size_t lhs, size_t rhs>
struct MinU : MinT<size_t, lhs, rhs> {};

template <size_t lhs, size_t rhs>
constexpr size_t MinUV = MinU<lhs, rhs>::value;



template <class T, T lhs, T rhs, class = std::void_t<decltype(std::declval<T>() < std::declval<T>())>>
struct MaxT {
    static constexpr T value = lhs < rhs ? rhs : lhs;
};

template <class T, T lhs, T rhs>
constexpr T MaxTV = MaxT<T, lhs, rhs>::value;

template <int lhs, int rhs>
struct Max : MaxT<int, lhs, rhs> {};

template <int lhs, int rhs>
constexpr int MaxV = Max<lhs, rhs>::value;

template <size_t lhs, size_t rhs>
struct MaxU : MaxT<size_t, lhs, rhs> {};

template <size_t lhs, size_t rhs>
constexpr size_t MaxUV = MaxU<lhs, rhs>::value;

} // calcom

#endif //CALCOM_MINMAX_HPP

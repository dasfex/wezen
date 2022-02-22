#ifndef WEZEN_MATH_BASICS_HPP
#define WEZEN_MATH_BASICS_HPP

#include <type_traits>
#include <numeric>

#include <iostream>

namespace wezen {

template <class T, T a>
struct abs {
    static constexpr T value = a >= 0 ? a : -a;
};

template <class T, T a>
constexpr inline T abs_v = abs<T, a>::value;

template <class T, T Head, T... Tail>
struct min {
    static constexpr T value = min<T, Head, min<T, Tail...>::value>::value;
};

template <class T, T lhs, T rhs>
struct min<T, lhs, rhs> {
    static constexpr T value = lhs < rhs ? lhs : rhs;
};

template <class T, T... Tail>
constexpr inline T min_v = min<T, Tail...>::value;

template <class T, T Head, T... Tail>
struct max {
    static constexpr T value = max<T, Head, max<T, Tail...>::value>::value;
};

template <class T, T lhs, T rhs>
struct max<T, lhs, rhs> {
    static constexpr T value = lhs < rhs ? rhs : lhs;
};

template <class T, T... Tail>
constexpr inline T max_v = max<T, Tail...>::value;

template <class T, T Head, T... Tail>
struct gcd {
    static constexpr T value = gcd<T, Head, gcd<T, Tail...>::value>::value;
};

template <class T, T a, T b>
struct gcd<T, a, b> {
    static constexpr T value = [] {
        if constexpr (b > 0) {
            return gcd<T, b, a % b>::value;
        } else {
            return a;
        }
    }();
};

template <class T, T... Tail>
constexpr inline T gcd_v = gcd<T, Tail...>::value;

template <class T, T Head, T... Tail>
struct lcm {
    static constexpr T value = lcm<T, Head, lcm<T, Tail...>::value>::value;
};

template <class T, T a, T b>
struct lcm<T, a, b> {
    static constexpr T value = a / gcd_v<T, a, b> * b;
};

template <class T, T... Tail>
constexpr inline T lcm_v = lcm<T, Tail...>::value;

template <bool Condition, class T, T a, T b>
struct condition {
    static constexpr T value = Condition ? a : b;
};

template <bool Condition, class T, T a, T b>
constexpr inline T condition_v = condition<Condition, T, a, b>::value;

template <class T, T a, size_t N, T M = std::numeric_limits<T>::max()>
struct pow {
    static constexpr T value = [] {
        if constexpr (N == 1) {
            return a;
        } else if constexpr (N % 2 == 1) {
            return a * pow<T, a, N - 1, M>::value % M;
        } else {
            T x = pow<T, a, N / 2, M>::value;
            return x * x % M;
        }
    }();
};

template <class T, T a, size_t N, T M = std::numeric_limits<T>::max()>
constexpr inline T pow_v = pow<T, a, N, M>::value;

#ifdef TEST
/// abs
static_assert(abs_v<int, -2> == 2);
static_assert(abs_v<int, 0> == 0);
static_assert(abs_v<int, 2> == 2);
/// min
static_assert(min_v<int, -1, 2> == -1);
static_assert(min_v<size_t, 228, 3> == 3);
static_assert(min_v<int, 1, 4, 2341, -31, -17> == -31);
/// max
static_assert(max_v<int, -1, 2> == 2);
static_assert(max_v<size_t, 228, 3> == 228);
static_assert(max_v<int, 1, 4, 2341, -31, -17> == 2341);
/// gcd
static_assert(gcd_v<long long, 8, 16, 32> == 8);
static_assert(gcd_v<int, 8, 17, 32, 228> == 1);
static_assert(gcd_v<size_t, 1024, 1024> == 1024);
static_assert(gcd_v<int, 1024, 0> == 1024);
/// lcm
static_assert(lcm_v<int, 2, 4, 5> == 20);
static_assert(lcm_v<int, 2, 3, 5> == 30);
static_assert(lcm_v<size_t, 2, 2> == 2);
/// condition
static_assert(condition_v<true, int, 6, 3> == 6);
static_assert(condition_v<false, int, 6, 3> == 3);
static_assert(condition_v<3 == 2, size_t, 221, 229> == 229);
/// pow
static_assert(pow_v<int, 2, 3> == 8);
static_assert(pow_v<size_t, 2, 3, 7> == 1);
static_assert(pow_v<size_t, 3, 1000000000, 19> == 16);
#endif

} // namespace wezen

#endif // WEZEN_MATH_BASICS_HPP

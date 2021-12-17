#ifndef WEZEN_MATH_BASICS_HPP
#define WEZEN_MATH_BASICS_HPP

#include <type_traits>

namespace wezen {

template <class T, T a>
struct abs_type {
    static constexpr T value = a >= 0 ? a : -a;
};

template <class T, T a>
constexpr inline T abs_type_v = abs_type<T, a>::value;

template <int a>
struct abs : abs_type<int, a> {};

template <int a>
constexpr inline int abs_v = abs<a>::value;

template <class T, T Head, T... Tail>
struct min_type {
    static constexpr T value = min_type<T, Head, min_type<T, Tail...>::value>::value;
};

template <class T, T lhs, T rhs>
struct min_type<T, lhs, rhs> {
    static constexpr T value = lhs < rhs ? lhs : rhs;
};

template <class T, T... Tail>
constexpr inline T min_type_v = min_type<T, Tail...>::value;

template <int... Tail>
struct min : min_type<int, Tail...> {};

template <int... Tail>
constexpr inline int min_v = min<Tail...>::value;

template <size_t... Tail>
struct umin : min_type<size_t, Tail...> {};

template <size_t... Tail>
constexpr inline size_t umin_v = umin<Tail...>::value;

template <class T, T Head, T... Tail>
struct max_type {
    static constexpr T value = max_type<T, Head, max_type<T, Tail...>::value>::value;
};

template <class T, T lhs, T rhs>
struct max_type<T, lhs, rhs> {
    static constexpr T value = lhs < rhs ? rhs : lhs;
};

template <class T, T... Tail>
constexpr inline T max_type_v = max_type<T, Tail...>::value;

template <int... Tail>
struct max : max_type<int, Tail...> {};

template <int... Tail>
constexpr inline int max_v = max<Tail...>::value;

template <size_t... Tail>
struct umax : max_type<size_t, Tail...> {};

template <size_t... Tail>
constexpr inline size_t umax_v = umax<Tail...>::value;

template <class T, T Head, T... Tail>
struct gcd_type {
    static constexpr T value = gcd_type<T, Head, gcd_type<T, Tail...>::value>::value;
};

template <class T, T a, T b>
struct gcd_type<T, a, b> {
    static constexpr T value = [] {
        if constexpr (b > 0) {
            return gcd_type<T, b, a % b>::value;
        } else {
            return a;
        }
    }();
};

template <class T, T... Tail>
constexpr inline T gcd_type_v = gcd_type<T, Tail...>::value;

template <int... Tail>
struct gcd : gcd_type<int, Tail...> {};

template <int... Tail>
constexpr inline int gcd_v = gcd<Tail...>::value;

template <size_t... Tail>
struct ugcd : gcd_type<size_t, Tail...> {};

template <size_t... Tail>
constexpr inline size_t ugcd_v = ugcd<Tail...>::value;

template <class T, T Head, T... Tail>
struct lcm_type {
    static constexpr T value = lcm_type<T, Head, lcm_type<T, Tail...>::value>::value;
};

template <class T, T a, T b>
struct lcm_type<T, a, b> {
    static constexpr T value = a / gcd_type_v<T, a, b> * b;
};

template <class T, T... Tail>
constexpr inline T lcm_type_v = lcm_type<T, Tail...>::value;

template <int... Tail>
struct lcm : lcm_type<int, Tail...> {};

template <int... Tail>
constexpr inline int lcm_v = lcm<Tail...>::value;

template <size_t... Tail>
struct ulcm : lcm_type<size_t, Tail...> {};

template <size_t... Tail>
constexpr inline size_t ulcm_v = ulcm<Tail...>::value;

template <bool Condition, class T, T a, T b>
struct condition_type {
    static constexpr T value = Condition ? a : b;
};

template <bool Condition, class T, T a, T b>
constexpr inline T condition_type_v = condition_type<Condition, T, a, b>::value;

template <bool Condition, int a, int b>
struct condition : condition_type<Condition, int, a, b> {};

template <bool Condition, int a, int b>
constexpr inline int condition_v = condition<Condition, a, b>::value;

#ifdef TEST
/// abs
static_assert(abs_type_v<int, -2> == 2);
static_assert(abs_type_v<int, 0> == 0);
static_assert(abs_type_v<int, 2> == 2);
/// min
static_assert(min_v<-1, 2> == -1);
static_assert(umin_v<228, 3> == 3);
static_assert(min_v<1, 4, 2341, -31, -17> == -31);
/// max
static_assert(max_v<-1, 2> == 2);
static_assert(umax_v<228, 3> == 228);
static_assert(max_v<1, 4, 2341, -31, -17> == 2341);
/// gcd
static_assert(gcd_type_v<long long, 8, 16, 32> == 8);
static_assert(gcd_v<8, 17, 32, 228> == 1);
static_assert(gcd_v<1024, 1024> == 1024);
static_assert(ugcd_v<1024, 0> == 1024);
/// lcm
static_assert(lcm_type_v<int, 2, 4, 5> == 20);
static_assert(lcm_v<2, 3, 5> == 30);
static_assert(ulcm_v<2, 2> == 2);
/// condition
static_assert(condition_v<true, 6, 3> == 6);
static_assert(condition_v<false, 6, 3> == 3);
static_assert(condition_v<3 == 2, 221, 229> == 229);
#endif

} // namespace wezen

#endif // WEZEN_MATH_BASICS_HPP

#ifndef WEZEN_MINMAX_HPP
#define WEZEN_MINMAX_HPP

#include <type_traits>

namespace wezen {

template <class T, T Head, T... Tail>
struct min_type {
    static constexpr T value = min_type<T, Head, min_type<T, Tail...>::value>::value;
};

template <class T, T lhs, T rhs>
struct min_type<T, lhs, rhs> {
    static constexpr T value = lhs < rhs ? lhs : rhs;
};

template <class T, T... Tail>
constexpr T min_type_v = min_type<T, Tail...>::value;

template <int... Tail>
struct min : min_type<int, Tail...> {};

template <int... Tail>
constexpr int min_v = min<Tail...>::value;

template <size_t... Tail>
struct umin : min_type<size_t, Tail...> {};

template <size_t... Tail>
constexpr size_t umin_v = umin<Tail...>::value;



template <class T, T Head, T... Tail>
struct max_type {
    static constexpr T value = max_type<T, Head, max_type<T, Tail...>::value>::value;
};

template <class T, T lhs, T rhs>
struct max_type<T, lhs, rhs> {
    static constexpr T value = lhs < rhs ? rhs : lhs;
};

template <class T, T... Tail>
constexpr T max_type_v = max_type<T, Tail...>::value;

template <int... Tail>
struct max : max_type<int, Tail...> {};

template <int... Tail>
constexpr int max_v = max<Tail...>::value;

template <size_t... Tail>
struct umax : max_type<size_t, Tail...> {};

template <size_t... Tail>
constexpr size_t umax_v = umax<Tail...>::value;

} // wezen

#endif // WEZEN_MINMAX_HPP

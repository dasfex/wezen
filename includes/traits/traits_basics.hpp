#ifndef WEZEN_TRAITS_BASICS_HPP
#define WEZEN_TRAITS_BASICS_HPP

namespace wezen {

template <class T>
struct rank {
    static constexpr size_t value = 0;
};

template <class T, int N>
struct rank<T[N]> {
    static constexpr size_t value = 1 + rank<T>::value;
};

template <class T>
struct rank<T[]> {
    static constexpr size_t value = 1 + rank<T>::value;
};

template <class T>
constexpr inline auto rank_v = rank<T>::value;

#ifdef TEST
/// rank
static_assert(rank_v<int> == 0);
static_assert(rank_v<int[]> == 1);
static_assert(rank_v<int[10][2][12]> == 3);
#endif

} // namespace wezen

#endif // WEZEN_TRAITS_BASICS_HPP

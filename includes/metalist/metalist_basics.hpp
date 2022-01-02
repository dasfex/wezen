#ifndef WEZEN_METALIST_BASICS_HPP
#define WEZEN_METALIST_BASICS_HPP

#ifdef TEST
#include <type_traits>
#endif

namespace wezen {

template<class T, T... List>
struct metalist_type;

template<int... List>
struct metalist;

namespace details {
template<class T, T Head, T... Tail>
struct decompose_type {
    static constexpr T head = Head;

    template<class = void>
    using tail = metalist_type<T, Tail...>;
};

template<int Head, int... Tail>
struct decompose {
    static constexpr int head = Head;

    template<class = void>
    using tail = metalist<Tail...>;
};
} // namespace details

template <class T, T... List>
struct metalist_type {
    using type = T;
    static constexpr size_t size = sizeof...(List);
    static constexpr T head = details::decompose_type<T, List...>::head;

    template <class = void>
    using tail = typename details::decompose_type<T, List...>::template tail<>;
};

template <class T>
struct metalist_type<T> {
    using type = T;
    static constexpr size_t size = 0;
};

template <int... List>
struct metalist {
    using type = int;
    static constexpr size_t size = sizeof...(List);
    static constexpr int head = details::decompose<List...>::head;

    template <class = void>
    using tail = typename details::decompose<List...>::template tail<>;
};

template <>
struct metalist<> {
    using type = int;
    static constexpr size_t size = 0;
};

template <size_t Ind, class Metalist, class = std::void_t<typename Metalist::template tail<>>>
struct get {
    static_assert(Ind < Metalist::size);
    static constexpr auto value = get<Ind - 1, typename Metalist::template tail<>>::value;
};

template <class Metalist>
struct get<0, Metalist> {
    static_assert(Metalist::size >= 1);
    static constexpr typename Metalist::type value = Metalist::head;
};

template <size_t Ind, class Metalist>
constexpr inline auto get_v = get<Ind, Metalist>::value;

#ifdef TEST
/// decompose_type
static_assert(details::decompose_type<int, 1, 2, 3, 4>::head == 1);
static_assert(std::is_same_v<typename details::decompose_type<int, 1, 2, 3, 4>::template tail<>,
        metalist_type<int, 2, 3, 4>>);

/// metalist
static_assert(std::is_same_v<metalist_type<int, 1, 2, 3>::type, int>);
static_assert(metalist_type<int, 1, 2, 3>::size == 3);
static_assert(metalist_type<int, 1>::head == 1);
static_assert(std::is_same_v<typename metalist_type<int, 1>::template tail<>, metalist_type<int>>);
static_assert(std::is_same_v<typename metalist_type<int, 1, 2>::template tail<>, metalist_type<int, 2>>);
static_assert(metalist_type<int>::size == 0);
static_assert(metalist<1, 2, -1, 4>::head == 1);

/// get
using local_meta = metalist<0, 1, 2>;
static_assert(get<0, local_meta>::value == 0);
static_assert(get<2, local_meta>::value == 2);
static_assert(get_v<2, metalist_type<size_t, 0, 2, 7>> == 7);
#endif

} // namespace wezen

#endif // WEZEN_METALIST_BASICS_HPP

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
    using common = metalist_type;
    static constexpr size_t size = sizeof...(List);
    static constexpr T head = details::decompose_type<T, List...>::head;

    template <class = void>
    using tail = typename details::decompose_type<T, List...>::template tail<>;
};

template <class T>
struct metalist_type<T> {
    using type = T;
    using common = metalist_type;
    static constexpr size_t size = 0;
};

template <int... List>
struct metalist {
    using type = int;
    using common = metalist;
    static constexpr size_t size = sizeof...(List);
    static constexpr int head = details::decompose<List...>::head;

    template <class = void>
    using tail = typename details::decompose<List...>::template tail<>;
};

template <>
struct metalist<> {
    using type = int;
    using common = metalist;
    static constexpr size_t size = 0;
};

template <size_t Ind, class Metalist>
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

template <class T, T Finded, class Metalist>
struct contains_type {
    static_assert(std::is_same_v<T, typename Metalist::type>);
    static constexpr bool value = [] {
        if constexpr (Metalist::size > 0) {
            if constexpr (Finded == Metalist::head) {
                return true;
            } else {
                return contains_type<T, Finded, typename Metalist::template tail<>>::value;
            }
        } else {
            return false;
        }
    }();
};

template <class T, T Finded, class Metalist>
constexpr inline bool contains_type_v = contains_type<T, Finded, Metalist>::value;

template <int Finded, class Metalist>
struct contains {
    static constexpr bool value = contains_type_v<int, Finded, Metalist>;
};

template <int Finded, class Metalist>
constexpr inline bool contains_v = contains<Finded, Metalist>::value;

namespace details {

template <class T, T Finded, class Metalist, size_t Size = Metalist::size>
struct find_type_impl {
    static_assert(std::is_same_v<T, typename Metalist::type>);
    static constexpr size_t value = [] {
        if constexpr (Metalist::size > 0) {
            if constexpr (Finded == Metalist::head) {
                return 0;
            } else {
                constexpr auto result = find_type_impl<T, Finded, typename Metalist::template tail<>, Size>::value;
                if constexpr (result == Size) {
                    return result;
                } else {
                    return result + 1;
                }
            }
        } else {
            return Size;
        }
    }();
};

template <class Metalist, template <typename Metalist::type> class Predicate,  size_t Size = Metalist::size>
struct find_if_impl {
    static constexpr size_t value = [] {
        if constexpr (Metalist::size > 0) {
            if constexpr (Predicate<Metalist::head>::value) {
                return 0;
            } else {
                constexpr auto result = find_if_impl<typename Metalist::template tail<>, Predicate, Size>::value;
                if constexpr (result == Size) {
                    return result;
                } else {
                    return result + 1;
                }
            }
        } else {
            return Size;
        }
    }();
};

} // namespace details

template <class T, T Finded, class Metalist>
struct find_type {
    static constexpr auto value = details::find_type_impl<T, Finded, Metalist>::value;
};

template <class T, T Finded, class Metalist>
constexpr inline auto find_type_v = find_type<T, Finded, Metalist>::value;

template <int Finded, class Metalist>
struct find {
    static constexpr auto value = find_type<int, Finded, Metalist>::value;
};

template <int Finded, class Metalist>
constexpr inline auto find_v = find<Finded, Metalist>::value;

template <class Metalist, template <typename Metalist::type> class Predicate>
struct find_if {
    static constexpr auto value = details::find_if_impl<Metalist, Predicate, Metalist::size>::value;
};

template <class Metalist, template <typename Metalist::type> class Predicate>
constexpr inline auto find_if_v = find_if<Metalist, Predicate>::value;

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
static_assert(get<0, metalist<0, 1, 2>>::value == 0);
static_assert(get<2, metalist<0, 1, 2>>::value == 2);
static_assert(get_v<2, metalist_type<size_t, 0, 2, 7>> == 7);

/// contains
static_assert(contains_type_v<int, 3, metalist<3, 2, 1>>);
static_assert(contains<2, metalist<3, 2, 1>>::value);
static_assert(contains_v<1, metalist<3, 2, 1>>);
static_assert(!contains_v<0, metalist<3, 2, 1>>);

/// find
static_assert(find_type_v<int, 2, metalist<1, 2, 3>> == 1);
static_assert(find<1, metalist<1, 2, 3>>::value == 0);
static_assert(find_v<3, metalist<1, 2, 3>> == 2);
static_assert(find_v<4, metalist<1, 2, 3>> == 3);

/// find_if
template <int x>
struct is_even {
    static constexpr bool value = x % 2 == 0;
};
template <int x>
struct only_false {
    static constexpr bool value = false;
};
static_assert(find_if<metalist<1, 3, 5, 6, 7>, is_even>::value == 3);
static_assert(find_if_v<metalist<1, 3, 5, 6, 7>, only_false> == 5);
#endif

} // namespace wezen

#endif // WEZEN_METALIST_BASICS_HPP

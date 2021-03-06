#ifndef WEZEN_METALIST_BASICS_HPP
#define WEZEN_METALIST_BASICS_HPP

#ifdef TEST
#include <type_traits>
#endif

namespace wezen {

/// fail
template <typename T = void, typename S = void>
struct get_head;

template <typename T, template <typename S, S...> typename Metalist, T Head, T... Tail>
struct get_head<Metalist<T, Head, Tail...>> {
    static constexpr T value = Head;
};

/// fail
template <typename T, typename S = void>
struct get_tail;

template <typename T, template <typename S, S...> typename Metalist, T Head, T... Tail>
struct get_tail<Metalist<T, Head, Tail...>> {
    using type = Metalist<T, Tail...>;
};

template <typename Metalist>
using get_tail_t = typename get_tail<Metalist>::type;

template <typename T, T... List>
struct metalist {
    using type = T;
    static constexpr size_t size = sizeof...(List);
};

template <size_t Ind, typename Metalist>
struct get {
    static_assert(Ind < Metalist::size);
    static constexpr auto value = get<Ind - 1, get_tail_t<Metalist>>::value;
};

template <typename Metalist>
struct get<0, Metalist> {
    static_assert(Metalist::size > 0);
    static constexpr typename Metalist::type value = get_head<Metalist>::value;
};

template <size_t Ind, typename Metalist>
constexpr inline auto get_v = get<Ind, Metalist>::value;

template <typename T, T Finded, typename Metalist>
struct contains {
    static constexpr bool value = [] {
        if constexpr (Metalist::size > 0) {
            if constexpr (Finded == get_head<Metalist>::value) {
                return true;
            } else {
                return contains<T, Finded, get_tail_t<Metalist>>::value;
            }
        } else {
            return false;
        }
    }();
};

template <typename T, T Finded, typename Metalist>
constexpr inline bool contains_v = contains<T, Finded, Metalist>::value;

namespace details {

template <typename T, T Finded, typename Metalist, size_t Size = Metalist::size>
struct find_impl {
    static_assert(std::is_same_v<T, typename Metalist::type>);
    static constexpr size_t value = [] {
        if constexpr (Metalist::size > 0) {
            if constexpr (Finded == get_head<Metalist>::value) {
                return 0;
            } else {
                constexpr auto result = find_impl<T, Finded, get_tail_t<Metalist>, Size>::value;
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

template <typename Metalist, template <typename Metalist::type> typename Predicate,  size_t Size = Metalist::size>
struct find_if_impl {
    static constexpr size_t value = [] {
        if constexpr (Metalist::size > 0) {
            if constexpr (Predicate<get_head<Metalist>::value>::value) {
                return 0;
            } else {
                constexpr auto result = find_if_impl<get_tail_t<Metalist>, Predicate, Size>::value;
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

template <typename T, T Finded, typename Metalist>
struct find {
    static constexpr auto value = details::find_impl<T, Finded, Metalist>::value;
};

template <typename T, T Finded, typename Metalist>
constexpr inline auto find_v = find<T, Finded, Metalist>::value;

template <typename Metalist, template <typename Metalist::type> typename Predicate>
struct find_if {
    static constexpr auto value = details::find_if_impl<Metalist, Predicate, Metalist::size>::value;
};

template <typename Metalist, template <typename Metalist::type> typename Predicate>
constexpr inline auto find_if_v = find_if<Metalist, Predicate>::value;

/// fail
template <typename T, typename T::type>
struct push_front;

template <typename T, T Pushed, template <typename S, S...> typename Metalist, T Head, T... Tail>
struct push_front<Metalist<T, Head, Tail...>, Pushed> {
    using type = Metalist<T, Pushed, Head, Tail...>;
};

template <typename T, T Pushed, template <typename S, S...> typename Metalist>
struct push_front<Metalist<T>, Pushed> {
    using type = Metalist<T, Pushed>;
};

template <typename Metalist, typename Metalist::type Pushed>
using push_front_t = typename push_front<Metalist, Pushed>::type;

/// fail
template <typename T, typename T::type>
struct push_back;

template <typename T, T Pushed, template <typename S, S...> typename Metalist, T Head, T... Tail>
struct push_back<Metalist<T, Head, Tail...>, Pushed> {
    using type = Metalist<T, Head, Tail..., Pushed>;
};

template <typename T, T Pushed, template <typename S, S...> typename Metalist>
struct push_back<Metalist<T>, Pushed> {
    using type = Metalist<T, Pushed>;
};

template <typename Metalist, typename Metalist::type Pushed>
using push_back_t = typename push_back<Metalist, Pushed>::type;

#ifdef TEST

/// metalist
static_assert(std::is_same_v<metalist<int, 1, 2, 3>::type, int>);
static_assert(metalist<int, 1, 2, 3>::size == 3);
static_assert(get_head<metalist<int, 0, 1, 2, 3>>::value == 0);
static_assert(std::is_same_v<get_tail<metalist<int, 1>>::type, metalist<int>>);
static_assert(std::is_same_v<get_tail_t<metalist<int, 1, 2, 3, 4>>, metalist<int, 2, 3, 4>>);
static_assert(metalist<int>::size == 0);
static_assert(get_head<metalist<int, 2, -1, 4>>::value == 2);

/// get
static_assert(get<0, metalist<int, 0, 1, 2>>::value == 0);
static_assert(get<2, metalist<int, 0, 1, 2>>::value == 2);
static_assert(get_v<2, metalist<size_t, 0, 2, 7>> == 7);

/// contains
static_assert(contains_v<int, 3, metalist<int, 3, 2, 1>>);
static_assert(contains<int, 2, metalist<int, 3, 2, 1>>::value);
static_assert(contains_v<int, 1, metalist<int, 3, 2, 1>>);
static_assert(!contains_v<int, 0, metalist<int, 3, 2, 1>>);

/// find
static_assert(find_v<int, 2, metalist<int, 1, 2, 3>> == 1);
static_assert(find<int, 1, metalist<int, 1, 2, 3>>::value == 0);
static_assert(find_v<int, 3, metalist<int, 1, 2, 3>> == 2);
static_assert(find_v<int, 4, metalist<int, 1, 2, 3>> == 3);

/// find_if
template <int x>
struct is_even {
    static constexpr bool value = x % 2 == 0;
};
template <int x>
struct only_false {
    static constexpr bool value = false;
};
static_assert(find_if<metalist<int, 1, 3, 5, 6, 7>, is_even>::value == 3);
static_assert(find_if_v<metalist<int, 1, 3, 5, 6, 7>, only_false> == 5);

/// push_front
using ftest_list = metalist<int, 1, 2, 3>;
using fans1 = metalist<int, 0, 1, 2, 3>;
using fans2 = metalist<int, 5, 1, 2, 3>;
using fans3 = metalist<int, 18>;
static_assert(std::is_same_v<push_front<ftest_list, 0>::type, fans1>);
static_assert(std::is_same_v<push_front_t<ftest_list, 5>, fans2>);
static_assert(std::is_same_v<push_front_t<metalist<int>, 18>, fans3>);

/// push_back
using btest_list = metalist<int, 1, 2>;
using bans1 = metalist<int, 1, 2, 0>;
using bans2 = metalist<int, 1, 2, 5>;
using bans3 = metalist<int, 18>;
static_assert(std::is_same_v<push_back<btest_list, 0>::type, bans1>);
static_assert(std::is_same_v<push_back_t<btest_list, 5>, bans2>);
static_assert(std::is_same_v<push_back_t<metalist<int>, 18>, bans3>);
#endif

} // namespace wezen

#endif // WEZEN_METALIST_BASICS_HPP

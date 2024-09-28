#ifndef WEZEN_ALGORITHM_HPP
#define WEZEN_ALGORITHM_HPP

#include "metalist_basics.hpp"

namespace wezen {

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

#ifdef TEST

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

#endif

}  // namespace wezen

#endif //WEZEN_ALGORITHM_HPP

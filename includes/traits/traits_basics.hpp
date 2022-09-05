#ifndef WEZEN_TRAITS_BASICS_HPP
#define WEZEN_TRAITS_BASICS_HPP

#ifdef TEST
#include <string>
#endif

namespace wezen {

template <typename T>
struct rank {
    static constexpr size_t value = 0;
};

template <typename T, int N>
struct rank<T[N]> {
    static constexpr size_t value = 1 + rank<T>::value;
};

template <typename T>
struct rank<T[]> {
    static constexpr size_t value = 1 + rank<T>::value;
};

template <typename T>
constexpr inline auto rank_v = rank<T>::value;

#define HAS_METHOD(NAME) \
namespace wezen { \
template <class T, class... Args> \
struct has_##NAME { \
 private: \
  template <class TT, class... Aargs, \
        class = decltype(std::declval<TT>().NAME(std::declval<Aargs>()...))> \
  static std::true_type f(int); \
  template <class...> \
  static std::false_type f(...); \
 public: \
  using type = decltype(f<T, Args...>(0)); \
}; \
template <class T, class... Args> \
constexpr inline bool has_##NAME##_v = std::is_same_v<typename has_##NAME<T, Args...>::type, std::true_type>; \
} // namespace wezen

#define HAS_OPERATOR(NAME, OP) \
namespace wezen { \
template <class T> \
struct has_##NAME { \
 private: \
  template <class TT, \
        class = decltype(std::declval<TT>() OP std::declval<TT>())> \
  static std::true_type f(int); \
  template <class...> \
  static std::false_type f(...); \
 public: \
  using type = decltype(f<T>(0)); \
}; \
template <class T> \
constexpr inline bool has_##NAME##_v = std::is_same_v<typename has_##NAME<T>::type, std::true_type>; \
} // namespace wezen

#define HAS_UNARY_OPERATOR(NAME, OP) \
namespace wezen { \
template <typename T> \
struct has_##NAME { \
 private: \
  template <typename TT, \
        class = decltype(OP std::declval<TT>())> \
  static std::true_type f(int); \
  template <typename...> \
  static std::false_type f(...); \
 public: \
  using type = decltype(f<T>(0)); \
}; \
template <typename T> \
constexpr inline bool has_##NAME##_v = std::is_same_v<typename has_##NAME<T>::type, std::true_type>; \
} // namespace wezen

template <typename T, typename... Tail>
struct is_one_of {
    static constexpr bool value = is_one_of<T, Tail...>::value;
};

template <typename T, typename U, typename... Tail>
struct is_one_of<T, U, Tail...> {
    static constexpr bool value = is_one_of<T, Tail...>::value;
};

template <typename T, typename... Tail>
struct is_one_of<T, T, Tail...> {
    static constexpr bool value = true;
};

template <typename T>
struct is_one_of<T> {
    static constexpr bool value = false;
};

template <typename T, typename... Tail>
constexpr inline bool is_one_of_v = is_one_of<T, Tail...>::value;

#if __cplusplus >= 202002L
#include <type_traits>

template <typename T>
struct type_identity : std::type_identity_t<T> {};

template <typename T>
using type_identity_t = typename std::type_identity_t<T>;
#else
template <typename T>
struct type_identity {
    using type = T;
};

template <typename T>
using type_identity_t = typename type_identity<T>::type;
#endif  // __cplusplus >= 202002L

namespace details {

template <typename T, typename...>
struct void_t_impl : type_identity<T> {};

}  // namespace details

template <typename... Args>
struct void_t : details::void_t_impl<void, Args...> {};

#ifdef TEST
/// rank
static_assert(rank_v<int> == 0);
static_assert(rank_v<int[]> == 1);
static_assert(rank_v<int[10][2][12]> == 3);

/// HAS_METHOD, HAS_OPERATOR, HAS_UNARY_OPERATOR
struct TestClass {
    void foo(int, double) {}

    void operator+(const TestClass&) {}

    void operator++() {}
};

HAS_METHOD(foo);

static_assert(wezen::has_foo_v<TestClass, int, double>);
static_assert(!wezen::has_foo_v<TestClass, int, std::string>);

HAS_OPERATOR(plus, +);
HAS_OPERATOR(minus, -);

static_assert(wezen::has_plus_v<TestClass>);
static_assert(!wezen::has_minus_v<TestClass>);

HAS_UNARY_OPERATOR(pref_plus, ++);
HAS_UNARY_OPERATOR(pref_minus, --);

static_assert(wezen::has_pref_plus_v<TestClass>);
static_assert(!wezen::has_pref_minus_v<TestClass>);

/// is_one_of
static_assert(!is_one_of_v<int, double, float>);
static_assert(is_one_of_v<int, double, int, float>);
static_assert(!is_one_of_v<int>);
static_assert(is_one_of_v<int, int>);
static_assert(!is_one_of_v<int, float>);

/// type_identity
static_assert(std::is_same_v<type_identity_t<int>, int>);
static_assert(std::is_same_v<type_identity_t<TestClass>, TestClass>);

/// void_t; example should compile
struct One { int x; };
struct Two { int y; };

template <typename T, void_t<decltype(T::x)>* = nullptr>
void f() {}
template <typename T, void_t<decltype(T::y)>* = nullptr>
void f() {}

void wrapper() {
    f<One>();
    f<Two>();
}
#endif

} // namespace wezen

#endif // WEZEN_TRAITS_BASICS_HPP

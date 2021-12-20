#ifndef WEZEN_TRAITS_BASICS_HPP
#define WEZEN_TRAITS_BASICS_HPP

#ifdef TEST
#include <string>
#endif

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

#define HAS_METHOD(NAME) \
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
constexpr inline bool has_##NAME##_v = std::is_same_v<typename has_##NAME<T, Args...>::type, std::true_type>

#define HAS_OPERATOR(NAME, OP) \
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
constexpr inline bool has_##NAME##_v = std::is_same_v<typename has_##NAME<T>::type, std::true_type>

#define HAS_UNARY_OPERATOR(NAME, OP) \
template <class T> \
struct has_##NAME { \
 private: \
  template <class TT, \
        class = decltype(OP std::declval<TT>())> \
  static std::true_type f(int); \
  template <class...> \
  static std::false_type f(...); \
 public: \
  using type = decltype(f<T>(0)); \
}; \
template <class T> \
constexpr inline bool has_##NAME##_v = std::is_same_v<typename has_##NAME<T>::type, std::true_type>

#ifdef TEST
/// rank
static_assert(rank_v<int> == 0);
static_assert(rank_v<int[]> == 1);
static_assert(rank_v<int[10][2][12]> == 3);

/// HAS_METHOD, HAS_OPERATOR, HAS_UNARY_OPERATOR
struct TestClass {
    void foo(int, double) {}

    TestClass operator+(const TestClass& rhs) {
        return *this;
    }

    void operator++() {}
};

HAS_METHOD(foo);

static_assert(has_foo_v<TestClass, int, double>);
static_assert(!has_foo_v<TestClass, int, std::string>);

HAS_OPERATOR(plus, +);
HAS_OPERATOR(minus, -);

static_assert(has_plus_v<TestClass>);
static_assert(!has_minus_v<TestClass>);

HAS_UNARY_OPERATOR(pref_plus, ++);
HAS_UNARY_OPERATOR(pref_minus, --);

static_assert(has_pref_plus_v<TestClass>);
static_assert(!has_pref_minus_v<TestClass>);
#endif

} // namespace wezen

#endif // WEZEN_TRAITS_BASICS_HPP

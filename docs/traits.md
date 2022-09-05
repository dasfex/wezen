# Traits

1. [Basic traits](https://github.com/dasfex/wezen/blob/trunk/includes/traits/traits_basics.hpp).
+ ```rank``` - return dimension count.

Signature:
```cpp
template <class T> rank -> 0;
template <class T[]> rank -> size_t;
template <class T[N]> rank -> size_t;
```

Example:
```cpp
wezen::rank<int>::value; // 0
wezen::rank_v<int[]>; // 1
wezen::rank_v<int[10][2][12]>; // 3
```

Next traits is generated with macroses. 
Do not forget use ```;```.

Macroses are expanded on preprocessing when there is no information
about namespaces so it is better if you will use it with ```wezen```
namespace.

+ ```HAS_METHOD``` - macros (sorry) for generating code 
for checking method availability.

Signature
```cpp
HAS_METHOD(NAME);
```
generates
```cpp
template <T, T... Args> has_##NAME -> typename type;
```

Example:
```cpp
struct TestClass {
    void foo(int, double) {}
}; 

HAS_METHOD(foo);

// can I call foo on object of TestClass type with int double args?
// remember about type conversions
wezen::has_foo_v<TestClass, int, double>; // true
wezen::has_foo_v<TestClass, std::string>; // false
```
+ ```HAS_OPERATOR``` - macros for generating code 
for checking binary operator availability.

Signature
```cpp
HAS_OPERATOR(NAME, OP);
```
generates
```cpp
template <T> has_##NAME -> typename type;
```

Example:
```cpp
struct TestClass {
    TestClass operator+(const TestClass& rhs) {
        return *this;
    }
}; 

// name and operator
// x + x
HAS_OPERATOR(plus, +);
// x - x
HAS_OPERATOR(minus, -);

// can I call operator on two objects of TestClass type?
wezen::has_plus_v<TestClass>; // true
wezen::has_minus_v<TestClass>; // false
```
+ ```HAS_UNARY_OPERATOR``` - macros for generating code 
for checking unary operator availability.

Signature
```cpp
HAS_UNARY_OPERATOR(NAME, OP);
```
generates
```cpp
template <T> has_##NAME -> typename type;
```

Example:
```cpp
struct TestClass {
    void operator++() {}
};

// check ++x
HAS_UNARY_OPERATOR(pref_plus, ++);
// check --x
HAS_UNARY_OPERATOR(pref_minus, --);

wezen::has_pref_plus_v<TestClass>; // true
wezen::has_pref_minus_v<TestClass>; // false
```

+ ```is_one_of``` - checks is type ```T``` inside list of types.

Signature:
```cpp
template <class T, class... Tail> is_one_of -> bool;
template <class T, class T, class... Tail> is_one_of -> true;
template <class T, class U, class... Tail> is_one_of -> bool;
template <class T> is_one_of -> false;
```

Example:
```cpp
wezen::is_one_of_v<int, double, float>; // false
wezen::is_one_of_v<int, double, int, float>; // true
wezen::is_one_of<int>::value; // false
wezen::is_one_of_v<int, int>; // true
wezen::is_one_of_v<int, float>; // false
```

+ ```type_identity``` ([cppreference](https://en.cppreference.com/w/cpp/types/type_identity)) -
custom implementation or from STL if your standard >= C++20.

Signature:
```cpp
template <typename T> type_identity -> T;
```

Example:
```cpp
std::is_same_v<wezen::type_identity_t<int>, int>; // true
std::is_same_v<wezen::type_identity_t<TestClass>, TestClass>; // true
```

+ ```void_t``` - like in C++17 STL but works.

Signature:
```cpp
template <typename...> -> void;
```

Example:
```cpp
struct One { int x; };
struct Two { int y; };

template <typename T, wezen::void_t<decltype(T::x)>* = nullptr>
void f() {}
template <typename T, wezen::void_t<decltype(T::y)>* = nullptr>
void f() {}

void wrapper() {
    f<One>();
    f<Two>();
}
```
This example works with ```wezen::void_t``` but not with ```std::void_t```.

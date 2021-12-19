# Traits

1. [Basic traits](https://github.com/dasfex/wezen/blob/trunk/includes/traits/traits_basics.hpp).
+ ```rank``` - return dimension count.
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

+ ```HAS_METHOD``` - macros(sorry) for generating code 
for checking method availability.
```cpp
struct TestClass {
    void foo(int, double) {}
}; 

namespace wezen {
HAS_METHOD(foo);
}

// can I call foo on object of TestClass type with int double args?
// remember about type conversions
wezen::has_foo_v<TestClass, int, double>; // true
wezen::has_foo_v<TestClass, std::string>; // false
```
+ ```HAS_OPERATOR``` - macros for generating code 
for checking binary operator availability.
```cpp
struct TestClass {
    TestClass operator+(const TestClass& rhs) {
        return *this;
    }
}; 

namespace wezen {
// name and operator
// x + x
HAS_OPERATOR(plus, +);
// x - x
HAS_OPERATOR(minus, -);
}

// can I call operator on two objects of TestClass type?
wezen::has_plus_v<TestClass>; // true
wezen::has_minus_v<TestClass>; // false
```
+ ```HAS_UNARY_OPERATOR``` - macros for generating code 
for checking unary operator availability.
```cpp
struct TestClass {
    void operator++() {}
};

namespace wezen {
// check ++x
HAS_UNARY_OPERATOR(pref_plus, ++);
// check --x
HAS_UNARY_OPERATOR(pref_minus, --);
}

wezen::has_pref_plus_v<TestClass>; // true
wezen::has_pref_minus_v<TestClass>; // false
```

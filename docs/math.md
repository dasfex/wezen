# Math
Wezen has different math functions.

All functions has different versions:
```cpp
func_type<type, args...>; // for explicit type
func<args...>::value; // int version
ufunc<args...>::value; // size_t version
func_v<args...>; // alias for ::value
```

1. [Basic functions](https://github.com/dasfex/wezen/blob/trunk/includes/math/math_basics.hpp):
+ ```abs```

Signature:
```cpp
template <class T, T a> abs_type -> T;
template <int a> abs -> int;
```

Example:
```cpp
 wezen::abs_type_v<long long, -2>;
 wezen::abs<8>::value;
```

+ ```min/max```

Signature:
```cpp
template <class T, T Head, T... Tail> min_type/max_type -> T;
template <class T, T lhs, T rhs> min_type/max_type -> T;
template <int... Tail> min/max -> int;
template <int lhs, int rhs> min/max -> int;
template <size_t... Tail> umin/umax -> size_t;
template <size_t lhs, size_t rhs> umin/umax -> size_t;
```

Example:
```cpp
wezen::min<2, 3, -1>::value;
wezen::min_v<2, 3>;
wezen::max_type_v<int64_t, 2, 3, 9>;
```

+ ```gcd/lcm```

Signature:
```cpp
template <class T, T Head, T... Tail> gcd_type/lcm_type -> T;
template <class T, T a, T b> gcd_type/lcm_type -> T;
template <int... Tail> gcd/lcm -> int;
template <int lhs, int rhs> gcd/lcm -> int;
template <size_t... Tail> umin/umax -> size_t;
template <size_t lhs, size_t rhs> umin/umax -> size_t;
```

Example:
```cpp
wezen::gcd_type_v<long long, 8, 16, 32>;
wezen::gcd<1024, 1024>::value;
wezen::ulcm_v<2, 2>;
```

+ ```condition```

Signature:
```cpp
template <bool Condition, class T, T a, T b> condition_type -> T;
template <bool Condition, int a, int b> condition -> int;
template <bool Condition, size_t a, size_t b> ucondition -> size_t;
```

Example:
```cpp
wezen::condition_v<true, 6, 3>; // 6
wezen::condition_type_v<false, size_t, 6, 3>; // 3
wezen::condition_v<3 == 2, 221, 229>; // 229
```

+ ```pow``` - binary pow for a^b mod M.

Signature:
```cpp
template <class T, T a, size_t N, T M = std::numeric_limits<T>::max()> pow_type -> T;
template <int a, size_t N, int M = std::numeric_limits<int>::max()> pow -> int;
template <size_t a, size_t N, size_t M = std::numeric_limits<size_t>::max()> upow -> size_t;
```

Example:
```cpp
wezen::pow_type_v<int, 2, 3>; // 2^3
wezen::pow_v<2, 3, 7>; // 2^3 % 7
wezen::upow_v<3, 1000000000, 19>; // 3^1e9 % 19 
```

2. More complex functions.

+ [Fibonacci numbers](
https://github.com/dasfex/wezen/blob/trunk/includes/math/fib.hpp
) - sequence 1 1 2 3 5 8 ... .

Computed in ```size_t```. You can specify modulo ```M```.
Asymptotic is O(log N). 

Signature:
```cpp
template <size_t N, size_t M = std::numeric_limits<size_t>::max()> fibonacci -> size_t;
```

Example:
```cpp
wezen::fibonacci<1>::value;
wezen::fibonacci_v<14>;
wezen::fibonacci_v<1000000000, 1000000007>;
```

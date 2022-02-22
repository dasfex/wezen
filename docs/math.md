# Math
Wezen has different math functions.

All functions has main version:
```cpp
func<type, args...>; // for explicit type
```

1. [Basic functions](https://github.com/dasfex/wezen/blob/trunk/includes/math/math_basics.hpp):
+ ```abs```

Signature:
```cpp
template <class T, T a> abs -> T;
```

Example:
```cpp
 wezen::abs_v<long long, -2>; // 2
 wezen::abs<int, 8>::value; // 8
```

+ ```min/max```

Signature:
```cpp
template <class T, T Head, T... Tail> min/max -> T;
template <class T, T lhs, T rhs> min/max -> T;
```

Example:
```cpp
wezen::min<int, 2, 3, -1>::value; // -1
wezen::min_v<int, 2, 3>; // 2
wezen::max_v<int64_t, 2, 3, 9>; // 9
```

+ ```gcd/lcm```

Signature:
```cpp
template <class T, T Head, T... Tail> gcd/lcm -> T;
template <class T, T a, T b> gcd/lcm -> T;
```

Example:
```cpp
wezen::gcd_v<long long, 8, 16, 32>; // 8
wezen::gcd<int, 1024, 1024>::value; // 1024
wezen::lcm<int, 2, 3>::value; // 6
wezen::lcm_v<size_t, 2, 2>; // 2
```

+ ```condition```

Signature:
```cpp
template <bool Condition, class T, T a, T b> condition -> T;
```

Example:
```cpp
wezen::condition_v<true, int, 6, 3>; // 6
wezen::condition_v<false, size_t, 6, 3>; // 3
wezen::condition_v<3 == 2, long long, 221, 229>; // 229
```

+ ```pow``` - binary pow for a^b mod M.

Signature:
```cpp
template <class T, T a, size_t N, T M = std::numeric_limits<T>::max()> pow -> T;
```

Example:
```cpp
wezen::pow_type_v<int, 2, 3>; // 2^3
wezen::pow_v<size_t, 2, 3, 7>; // 2^3 % 7
wezen::upow_v<long long, 3, 1000000000, 19>; // 3^1e9 % 19 
```

+ ```is_sqr``` - is number a square root.
Signature:
```cpp
template <unsigned long long x> is_sqr -> bool;
```

Examples:
```cpp
wezen::is_sqr_v<1>; // true
wezen::is_sqr_v<225>; // true
wezen::is_sqr_v<2>; // false
wezen::is_sqr_v<17>; // false
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

+ ```is_fib``` - is number a fibonacci number.

Signature:
```cpp
template <unsigned long long x> is_fib -> bool;
```
Example:
```cpp
wezen::is_fib_v<3>; // true
wezen::is_fib_v<8>; // true
wezen::is_fib_v<2971215073>; // f_48
// max fib in ull
wezen::is_fib_v<12200160415121876738ull>; // true 
wezen::is_fib_v<2971215072>; // false
wezen::is_fib_v<9>; // false
```

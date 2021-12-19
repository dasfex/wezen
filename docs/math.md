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
+ ```abs```.
```cpp
 wezen::abs_type_v<long long, -2>;
 wezen::abs<8>::value;
```
+ ```min/max```.
```cpp
wezen::min<2, 3, -1>::value;
wezen::min_v<2, 3, -1>;
wezen::max_type_v<int64_t, 2, 3>;
```
+ ```gcd/lcm```.
```cpp
wezen::gcd_type_v<long long, 8, 16, 32>;
wezen::gcd<1024, 1024>::value;
wezen::ulcm_v<2, 2>;
```
+ ```condition```
```cpp
wezen::condition_v<true, 6, 3>; // 6
wezen::condition_type_v<false, size_t, 6, 3>; // 3
wezen::condition_v<3 == 2, 221, 229>; // 229
```
+ ```pow``` - binary pow for a^b mod M.
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
```cpp
fibonacci<1>::value;
fibonacci_v<14>;
fibonacci_v<1000000000, 1000000007>;
```
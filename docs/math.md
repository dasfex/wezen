# Math
Wezen has different math functions.

All functions has different versions:
```cpp
func_type<type, args...>; // for explicit type
func<args...>::value; // int version
ufunc<args...>::value; // size_t version
func_v<args...>; // alias for ::value
```

1. [Basic functions]():
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

2. More complex functions.
+ [Fibonacci numbers]() - sequence 1 1 2 3 5 8 ... .

Computed in ```size_t```. You can specify modulo ```M```.
Asymptotic is O(log N). 
```cpp
fibonacci<1>::value;
fibonacci_v<14>;
fibonacci_v<1000000000, 1000000007>;
```
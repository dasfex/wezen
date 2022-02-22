# wezen
Small header-only library for metaprogramming.
I try to not repeat STL but in some places I am.

### Docs
[Here](https://github.com/dasfex/wezen/tree/trunk/docs)
you can find documentation of Wezen.

### Tests
In every header you can find tests and use it as examples. 
To launch tests compile with ```-DTEST```.

### Naming
Library is named as [Wezen](https://en.wikipedia.org/wiki/Delta_Canis_Majoris).

### Some examples

+ ```pow```
```cpp
// 3^1e9 % 19; asymptotics is O(log N)
wezen::pow_v<int, 3, 1000000000, 19>; 
```

+ ```is_sqr```
```cpp
wezen::is_sqr_v<1>; // true
wezen::is_sqr_v<225>; // true
wezen::is_sqr_v<2>; // false
wezen::is_sqr_v<17>; // false
```

+ ```fibonacci```
```cpp
// F_{1000000000} % (1e9+7); asymptotics is O(log N)
wezen::fibonacci_v<1000000000, 1000000007>;
```

+ ```metalist``` and different functions
```cpp
wezen::get_v<3, wezen::metalist<int, 0, 1, 2, 3, 4>>; // 3
wezen::contains_v<int, 4, 
    wezen::metalist<int, 1, 2, 3, 4, 5>>; // true

template <int x>
struct is_even {
    static constexpr bool value = x % 2 == 0;
};
wezen::find_if_v<
    wezen::metalist<int, 1, 3, 5, 6, 7>, is_even>; // 3

using tail = wezen::get_tail_t<
    wezen::metalist<int, 1, 2, 3>>; // wezen::metalist<int, 2, 3>
```

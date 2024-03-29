# wezen
Small header-only library as training in metaprogramming.
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

+ ```fibonacci``` and ```is_fib```
```cpp
// F_{1000000000} % (1e9+7); asymptotics is O(log N)
wezen::fibonacci_v<1000000000, 1000000007>;
// is_fib
wezen::is_fib_v<3>; // true
wezen::is_fib_v<8>; // true
wezen::is_fib_v<2971215073>; // f_48
wezen::is_fib_v<9>; // false
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
    
using new_list = wezen::push_back_t<
    wezen::metalist<int, 2, 2>, 8>; // wezen::metalist<int, 2, 2, 8>
```

+ ```void_t``` that really works:
This example with ```std::void_t``` will fail:
```cpp
struct One { int x; };
struct Two { int y; };

template <typename T, std::void_t<decltype(T::x)>* = nullptr>
void f() {}
template <typename T, std::void_t<decltype(T::y)>* = nullptr>
void f() {}

int main() {
  f<One>();
  f<Two>();
}
```
But if you change ```std::void_t``` to ```wezen::void_t``` it will compile!

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
wezen::upow_v<3, 1000000000, 19>; 
```

+ ```fibonacci```
```cpp
// F_{1000000000} % (1e9+7); asymptotics is O(log N)
wezen::fibonacci_v<1000000000, 1000000007>;
```

+ ```metalist``` and different functions
```cpp
wezen::get_v<3, wezen::metalist<0, 1, 2, 3, 4>>; // 3
wezen::contains_v<4, wezen::metalist<1, 2, 3, 4, 5>>; // true
```

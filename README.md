# wezen
Small header-only library for metaprogramming.
I try to not repeat STL but in some places I am.

### Support different math functions
+ ```min/max```
```cpp
wezen::min<2, 3, -1>::value; // min for int
wezen::min_v<2, 3, -1>; // alias for ::value
wezen::max_type_v<int64_t, 2, 3>; // you can specify type explicitly
```

### Tests
In ```tests.cpp``` you can find tests and use it as examples.

### Naming
Library is named as [Wezen](https://en.wikipedia.org/wiki/Delta_Canis_Majoris).

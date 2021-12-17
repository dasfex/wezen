# calcom
Small header-only library for compile time computing and some traits.

### Support different math functions
+ ```Min/Max```
```cpp
calcom::min<2, 3>::value; // 2, Min for int
calcom::min_v<2, 3>; // alias for ::value
calcom::max_type_v<int64_t, 2, 3>; // 3, you can specify type explicitly
calcom::max<1, 3, -123, -12, 223>; // or use for any count
```

### Tests

In ```tests.cpp``` you can find tests and use it as examples.

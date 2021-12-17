# calcom
Small library for compile time computing and some traits.

### Support different math functions
+ ```Min/Max```
```cpp
Min<2, 3>::value; // 2, Min for int
MinV<2, 3>; // alias for ::value
MaxTV<int64_t, 2, 3>; // 3, you can specify type explicitly
```

### Tests

In ```tests.cpp``` you can find tests and use it as examples.

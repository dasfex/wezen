# Traits

1. [Basic traits]().
+ ```rank``` - return dimension count.
```cpp
wezen::rank<int>::value; // 0
wezen::rank_v<int[]>; // 1
wezen::rank_v<int[10][2][12]>; // 3
```
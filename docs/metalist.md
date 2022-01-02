# Metalist

1. [Basics](https://github.com/dasfex/wezen/blob/trunk/includes/metalist/metalist_basics.hpp).

+ ```metalist```

Signature:
```cpp
template <class T, T... List> metalist_type -> 
    typename type = T
    size_t size = size(List)
    T head = head(List)
    tail = metalist_type<T, tail(List)>;
template <class T> metalist_type ->
    typename type = T
    size_t size = 0;
template <int... List> metalist : metalist_type<int, List...>;
```

Example:
```cpp
wezen::metalist_type<int, 1, 2, 3>::type; // int
wezen::metalist_type<int, 1, 2, 3>::size; // 3
wezen::metalist_type<int, 1>::head; // 1
typename wezen::metalist_type<int, 1>::template tail<>; // metalist_type<int>
wezen::metalist_type<int>::size; // 0
wezen::metalist<1, 2, -1, 4>::head; // 1
typename wezen::metalist<1, 2, -1, 4>::template tail<>; // metalist<2, -1, 4>
```

There is some disadvantage of how ```tail``` is called but 
this is because we want to decrease compilation time and 
instantiate tail only is you use it.
You can make ```using``` for better experience.

+ ```get```

Signature:
```cpp
template <size_t Ind, Metalist> get -> Metalist::type;
template <0, Metalist> get -> Metalist::head;
```

Example:
```cpp
get<0, metalist<0, 1, 2>>::value; // 0
get<2, metalist<0, 1, 2>>::value; // 2
get_v<2, metalist_type<size_t, 0, 2, 7>>; // 7
```

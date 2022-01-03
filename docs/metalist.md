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

There is some disadvantage of how ```tail``` is invoked but 
this is because we want to decrease compilation time and 
instantiate tail only if you use it.
You can make ```using``` for better experience.

+ ```get``` - return ```metalist[Ind]```.

Signature:
```cpp
template <size_t Ind, Metalist> get -> Metalist::type;
template <0, Metalist> get -> Metalist::head;
```

Example:
```cpp
wezen::get<0, wezen::metalist<0, 1, 2>>::value; // 0
wezen::get<2, wezen::metalist<0, 1, 2>>::value; // 2
wezen::get_v<2, wezen::metalist_type<size_t, 0, 2, 7>>; // 7
```

+ ```contains``` - return is ```metalist``` contains ```Finded```.

Signature:
```cpp
template <class T, T Finded, Metalist> contains_type -> bool;
template <int Finded, Metalist> contains -> bool;
```

Example:
```cpp
wezen::contains_type_v<int, 3, wezen::metalist<3, 2, 1>>; // true
wezen::contains<2, wezen::metalist<3, 2, 1>>::value; // true
wezen::contains_v<1, wezen::metalist<3, 2, 1>>; // true
wezen::contains_v<0, wezen::metalist<3, 2, 1>>; // false
```

+ ```find``` - return index of ```Finded``` in ```metalist``` 
if it is in list or ```metalist::size``` if not.

Signature:
```cpp
template <class T, T Finded, Metalist> find_type -> size_t;
template <int Finded, Metalist> find -> size_t;
```

Example:
```cpp
wezen::find_type_v<int, 2, wezen::metalist<1, 2, 3>>; // 1
wezen::find<1, wezen::metalist<1, 2, 3>>::value; // 0
wezen::find_v<3, wezen::metalist<1, 2, 3>>; // 2
wezen::find_v<4, wezen::metalist<1, 2, 3>>; // 3
```

+ ```find_if``` - return position of the first element in ```metalist``` which satisfy to ```Predicate``` 
or size of there is no such elements.

Signatures:
```cpp
template <Metalist, template <typename Metalist::type> class Predicate> find_if -> size_t;
```
I.e. type of metalist elements and predicate should be the same.
Examples:
```cpp
template <int x>
struct is_even {
    static constexpr bool value = x % 2 == 0;
};
template <int x>
struct only_false {
    static constexpr bool value = false;
};
find_if<metalist<1, 3, 5, 6, 7>, is_even>::value; // 3
find_if_v<metalist<1, 3, 5, 6, 7>, only_false>; // 5
```

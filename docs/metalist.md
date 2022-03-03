# Metalist

1. [Basics](https://github.com/dasfex/wezen/blob/trunk/includes/metalist/metalist_basics.hpp).

+ ```metalist```

Signature:
```cpp
template <typename T, T... List> metalist -> 
    typename type = T
    size_t size = size(List);
```

Example:
```cpp
wezen::metalist<int, 1, 2, 3>::type; // int
wezen::metalist<int, 1, 2, 3>::size; // 3
wezen::metalist<int>::size; // 0
```

+ ```get_head, get_tail```
Signature:
```cpp
template <
        typename T, 
        template <typename S, S...> typename Metalist,
        T Head, T... Tail> -> get_head ->
    T value = Head;
template <
        typename T, 
        template <typename S, S...> typename Metalist,
        T Head, T... Tail> -> get_tail ->
    typename type = Metalist<T, Tail...>;
```
Examples:
```cpp
wezen::get_head<metalist<int, 0, 1, 2>>::value; // 0
wezen::get_tail_t<metalist<int, 1, 2, 3, 4>>; // metalist<int, 2, 3, 4>
```
Look that ```get_tail_t``` exists but ```get_head_v``` not. 

+ ```get``` - return ```metalist[Ind]```.

Signature:
```cpp
template <size_t Ind, Metalist> get -> Metalist::type;
template <0, Metalist> get -> Metalist::head;
```

Example:
```cpp
wezen::get<0, wezen::metalist<int, 0, 1, 2>>::value; // 0
wezen::get<2, wezen::metalist<int, 0, 1, 2>>::value; // 2
wezen::get_v<2, wezen::metalist<size_t, 0, 2, 7>>; // 7
```

+ ```contains``` - return is ```metalist``` contains ```Finded```.

Signature:
```cpp
template <class T, T Finded, Metalist> contains -> bool;
```

Example:
```cpp
wezen::contains_v<int, 3, wezen::metalist<int, 3, 2, 1>>; // true
wezen::contains<int, 2, wezen::metalist<int, 3, 2, 1>>::value; // true
wezen::contains_v<int, 1, wezen::metalist<int, 3, 2, 1>>; // true
wezen::contains_v<int, 0, wezen::metalist<int, 3, 2, 1>>; // false
```

+ ```find``` - return index of ```Finded``` in ```metalist``` 
if it is in list or ```metalist::size``` if not.

Signature:
```cpp
template <class T, T Finded, Metalist> find -> size_t;
```

Example:
```cpp
wezen::find_v<int, 2, wezen::metalist<int, 1, 2, 3>>; // 1
wezen::find<int, 1, wezen::metalist<int, 1, 2, 3>>::value; // 0
wezen::find_v<int, 3, wezen::metalist<int, 1, 2, 3>>; // 2
wezen::find_v<int, 4, wezen::metalist<int, 1, 2, 3>>; // 3
```

+ ```find_if``` - return position of the first element in ```metalist``` which satisfy to ```Predicate``` 
or size of there is no such elements.

Signatures:
```cpp
template <
        Metalist, 
        template <typename Metalist::type> class Predicate
        > find_if -> size_t;
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
find_if<metalist<int, 1, 3, 5, 6, 7>, is_even>::value; // 3
find_if_v<metalist<int, 1, 3, 5, 6, 7>, only_false>; // 5
```

+ ```push_front``` - pushes element to the front of ```wezen::metalist```.

Signatures:
```cpp
template <
        typename Metalist, 
        typename Metalist::type Pushed> push_front -> type;
```

Examples:
```cpp
wezen::push_front_t<
            wezen::metalist<int, 2, 8>, 2
        >; // wezen::metalist<int, 2, 2, 8>
wezen::push_front_t<wezen::metalist<int, 1>, 5>; // wezen::metalist<int, 5, 1>
wezen::push_front_t<wezen::metalist<int>, 18>; // wezen::metalist<int, 18>
```

+ ```push_back``` - pushes element to the back of ```wezen::metalist```.

Signatures:
```cpp
template <
        typename Metalist, 
        typename Metalist::type Pushed> push_back -> type;
```

Examples:
```cpp
wezen::push_back_t<
            wezen::metalist<int, 2, 2>, 8
        >; // wezen::metalist<int, 2, 2, 8>
wezen::push_back_t<wezen::metalist<int, 1>, 5>; // wezen::metalist<int, 1, 5>
wezen::push_back_t<wezen::metalist<int>, 18>; // wezen::metalist<int, 18>
```
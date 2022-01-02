# Docs
Main documentation of Wezen.

Signature scheme(in pseudocode):
```cpp
template <args> func_name -> return_type;
```
if result is ```value``` of type ```return_type``` or
```cpp
template <args> func_name -> using type;
```
if result is type(for type traits).

1. [Math](https://github.com/dasfex/wezen/blob/trunk/docs/math.md).

Simple and not mathematical functions: 
```abs```, ```min```/```max```, ```gcd```/```lcm```, 
```fibonacci```, ```condition```, ```pow```.

2. [Traits](https://github.com/dasfex/wezen/blob/trunk/docs/traits.md).

Different traits: 
```rank```, ```HAS_METHOD```/```HAS_OPERATOR```/```HAS_UNARY_OPERATOR```, 
```is_one_of```.

3. [Metalist](https://github.com/dasfex/wezen/blob/trunk/docs/metalist.md).

Metalist for compile-time storing values and helpers for it:
```metalist_type```.

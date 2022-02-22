#ifndef WEZEN_FIB_HPP
#define WEZEN_FIB_HPP

#include "math_basics.hpp"

#include <limits>

namespace wezen {

namespace details {

template <size_t M, size_t a, size_t b, size_t c, size_t d>
struct matrix {
    static constexpr auto m11 = a % M;
    static constexpr auto m12 = b % M;
    static constexpr auto m21 = c % M;
    static constexpr auto m22 = d % M;
};

template <size_t M,
        size_t a, size_t b,
        size_t c, size_t d,
        size_t q, size_t w,
        size_t e, size_t r>
struct matrix_mul {
    static constexpr matrix<M, (a * q + b * e) % M,
            (a * w + b * r) % M,
            (c * q + d * e) % M,
            (c * w + d * r) % M> value = {};
};

template <size_t N, size_t M>
struct fibonacci_ {
    static constexpr auto value = [] {
        if constexpr (N % 2 == 1) {
            using PrevFib = decltype(fibonacci_<N - 1, M>::value);
            return matrix_mul<M,
                    PrevFib::m11, PrevFib::m12,
                    PrevFib::m21, PrevFib::m22,
                    1, 1, 1, 0
            >::value;
        } else {
            using HalfFib = decltype(fibonacci_<N / 2, M>::value);
            return matrix_mul<M,
                    HalfFib::m11, HalfFib::m12,
                    HalfFib::m21, HalfFib::m22,
                    HalfFib::m11, HalfFib::m12,
                    HalfFib::m21, HalfFib::m22
            >::value;
        }
    }();
};

template <size_t M>
struct fibonacci_<1, M> {
    static constexpr matrix<M, 1, 1, 1, 0> value{};
};

} // namespace details

template <size_t N, size_t M = std::numeric_limits<size_t>::max()>
struct fibonacci {
    static constexpr auto value = decltype(details::fibonacci_<N, M>::value)::m12;
};

template <size_t N, size_t M = std::numeric_limits<size_t>::max()>
constexpr inline auto fibonacci_v = fibonacci<N, M>::value;

namespace details {

using ull = unsigned long long;

template <ull x, ull f1, ull f2>
struct is_fib_gen_impl {
private:
    static constexpr ull max_ull_fib = 12200160415121876738ull;

public:
    static constexpr bool value = [] {
        if constexpr (x == f1 || x == f2) {
            return true;
        } else if constexpr (f1 == max_ull_fib || f2 == max_ull_fib) {
            return false;
        } else {
            return is_fib_gen_impl<x, f1 + f2, f1 + 2 * f2>::value;
        }
    }();
};

} // details

// x is f_n if 5x^2+4 or 5x^2-4 is sqr
template <unsigned long long x>
struct is_fib {
    static constexpr bool value = [] {
        if constexpr (x <= 1920767766) {
            constexpr unsigned long long control = 5 * x * x;
            return is_sqr_v<control + 4> || is_sqr_v<control - 4>;
        } else {
            // start generate from f_48 and f_49
            return details::is_fib_gen_impl<x, 2971215073, 4807526976>::value;
        }
    }();
};

template <unsigned long long x>
constexpr bool is_fib_v = is_fib<x>::value;

#ifdef TEST
/// fibonacci
static_assert(fibonacci_v<1> == 1);
static_assert(fibonacci_v<8> == 21);
static_assert(fibonacci_v<8, 11> == 10);
static_assert(fibonacci_v<1000000000000000000, 1000000007> == 209783453);
/// is_fib
static_assert(is_fib_v<3>);
static_assert(is_fib_v<63245986>);
static_assert(is_fib_v<2971215073>);
static_assert(is_fib_v<12200160415121876738ull>); // max fib in ull
static_assert(!is_fib_v<2971215072>);
static_assert(!is_fib_v<9>);
#endif

} // namespace wezen

#endif // WEZEN_FIB_HPP

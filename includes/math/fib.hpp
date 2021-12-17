#ifndef WEZEN_FIB_HPP
#define WEZEN_FIB_HPP

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

#ifdef TEST
     static_assert(fibonacci_v<1> == 1);
     static_assert(fibonacci_v<8> == 21);
     static_assert(fibonacci_v<8, 11> == 10);
     static_assert(fibonacci_v<1000000000000000000, 1000000007> == 209783453);
#endif

} // namespace wezen

#endif // WEZEN_FIB_HPP

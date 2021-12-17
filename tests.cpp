#include "wezen.hpp"

using namespace wezen;

int main() {
    // Min
    static_assert(min_v<-1, 2> == -1);
    static_assert(umin_v<228, 3> == 3);
    static_assert(min_v<1, 4, 2341, -31, -17> == -31);
    // Max
    static_assert(max_v<-1, 2> == 2);
    static_assert(umax_v<228, 3> == 228);
    static_assert(max_v<1, 4, 2341, -31, -17> == 2341);

    return 0;
}
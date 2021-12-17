#include "calcom.hpp"

using namespace calcom;

int main() {
    // Min
    static_assert(MinV<-1, 2> == -1);
    static_assert(MinUV<228, 3> == 3);
    // Max
    static_assert(MaxV<-1, 2> == 2);
    static_assert(MaxUV<228, 3> == 228);

    return 0;
}
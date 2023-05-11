#include <stdio.h>
#include <inttypes.h>

uint64_t next_pow2(uint64_t x) {
    x |= x >> 1;
    x |= x >> 1;
    x |= x >> 1;
    x |= x >> 1;
    x |= x >> 1;
    x |= x >> 1;
    x |= x >> 1;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    return x + 1;
}

int main() {
    uint64_t x = 7;
    printf("x = 0x%016" PRIx64 ", Decimal = %lu\n", x, x);
    printf("next_pow2(x) = 0x%016" PRIx64 ", Decimal = %lu\n", next_pow2(x), next_pow2(x));
    return 0;
}
#include <inttypes.h>
#include <stdio.h>

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

uint64_t next_pow2_by_builtin_clzl(uint64_t x) {
    if (!x)
        return 1;
    return 1UL << (64 - __builtin_clzl(x));
}

int main() {
    uint64_t x = 8;
    printf("x = 0x%016" PRIx64 ", Decimal = %lu\n", x, x);
    printf("next_pow2(x) = 0x%016" PRIx64 ", Decimal = %lu\n", next_pow2(x), next_pow2(x));
    printf("next_pow2_by_builtin_clzl(x) = 0x%016" PRIx64 ", Decimal = %lu\n", next_pow2_by_builtin_clzl(x), next_pow2_by_builtin_clzl(x));
    return 0;
}
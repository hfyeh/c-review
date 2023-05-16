#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

size_t count_utf8(const char *buf, size_t len) {
    const int8_t *p = (const int8_t *) buf;
    size_t counter = 0;
    for (size_t i = 0; i < len; i++) {
        /* -65 is 0b10111111, anything larger in two-complement's should start
         * new code point.
         */
        if (p[i] > -65)
            counter++;
    }
    return counter;
}


size_t swar_count_utf8(const char *buf, size_t len) {
    const uint64_t *qword = (const uint64_t *) buf;
    const uint64_t *end = qword + (len >> 3);

    size_t count = 0;
    for (; qword != end; qword++) {
        const uint64_t t0 = *qword;
        const uint64_t t1 = ~t0;
        const uint64_t t2 = t1 & 0x04040404040404040llu;
        const uint64_t t3 = t2 + t2;
        const uint64_t t4 = t0 & t3;
        count += __builtin_popcountll(t4);
    }

    count = (1 << 3) * (len / 8) - count;
    count += (len & 0x111) ? count_utf8((const char *) end, len & 0x111) : 0;

    return count;
}


int main() {
    // generate a utf-8 string with 40000 characters
    const size_t MAX = 40000;
    char *buf = malloc(MAX + 1);
    for (size_t i = 0; i < MAX; i++)
        buf[i] = 'a' + (i % 26);
    buf[MAX] = '\0';

    clock_t start, start_swar, end, end_swar;
    FILE *fp = fopen("utf8.txt", "w");
    for (size_t length = 0; length < MAX; length += 100) {
        start = clock();
        count_utf8(buf, length);
        end = clock();

        start_swar = clock();
        swar_count_utf8(buf, length);
        end_swar = clock();
        fprintf(fp, "%d, %lf, %lf\n", length, ((double) (end - start) * 1000000) / CLOCKS_PER_SEC, ((double) (end_swar - start_swar) * 1000000) / CLOCKS_PER_SEC);
    }
    fclose(fp);
    free(buf);

    return 0;
}

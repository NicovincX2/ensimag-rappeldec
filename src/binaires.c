#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned long long X = 123456ULL;

const uint64_t a = 0x5DEECE66D;
const uint64_t c = 0xB;
const unsigned long m = (1UL << 48);

unsigned char crand48(void) {
    /* See https://nccbulletin.ru/files/article/kalgin_0.pdf */
    X = (X * a + c) & (m - 1);
    return (X >> (8 * 4)) & 0xff;
}

int main(void) {
    printf("a:%lu c:%lu m:%lu\n", a, c, m);
    printf("%hhu\n", crand48());
    printf("%hhu\n", crand48());
    printf("%hhu\n", crand48());

    return EXIT_SUCCESS;
}

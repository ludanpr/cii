#include "arith.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void)
{
    int a = 12;
    int b = 15;
    assert(Arith_max(a, b) == b);
    assert(Arith_min(a, b) == a);

    int x = -13;
    int y = 5;
    assert(Arith_div(x, y) == -3);
    assert(Arith_mod(x, y) == 2);

    assert(Arith_ceiling(x, y) == -2);
    assert(Arith_floor(x, y) == -3);

#if __STDC_VERSION__ >= 201112L || defined(__GNUC__)
    short a1 = 5;
    short b1 = -1;
    assert(Arith_max(a1, b1) == a1);
    assert(Arith_min(a1, b1) == b1);

    long a2 = 1245;
    long b2 = -1245;
    assert(Arith_max(a2, b2) == a2);
    assert(Arith_min(a2, b2) == b2);

    long long a3 = -4500;
    long long b3 = -65535;
    assert(Arith_max(a3, b3) == a3);
    assert(Arith_min(a3, b3) == b3);

    long x1 = 13;
    long y1 = -5;
    assert(Arith_div(x1, y1) == -3);
    assert(Arith_mod(x1, y1) == -2);

    assert(Arith_ceiling(x1, y1) == -2);
    assert(Arith_floor(x1, y1) == -3);

#if defined(DEBUG_STATIC_ASSERTIONS)
    float a4 = 1.2e-2;
    float b4 = 10.0;
    (void) Arith_max(a4, b4);

    int a5 = 1;
    long b5 = 12;
    (void) Arith_min(a5, b5);

    double x2 = -12.e+4;
    long y2 = 6;
    (void) Arith_div(x2, y2);

    (void) Arith_ceiling(x2, y2);
#endif
#endif

    return EXIT_SUCCESS;
}

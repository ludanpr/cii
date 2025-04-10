#include "arith.h"

#if __STDC_VERSION__ < 201112L && !defined(__GNUC__)

int Arith_max(int a, int b)
{
    return (a > b) ? a : b;
}

int Arith_min(int a, int b)
{
    return (a < b) ? a : b;
}

int Arith_div(int a, int b)
{
    /* Two possible behaviors for division with different signs:
     * division truncates toward zero and b doesn't divide x evenly,
     * we have a/b - 1. Otherwise, a/b.
     */
    volatile int tzp = -13/5 == -2;  // truncates toward zero?
    if (tzp
        && ((a < 0) != (b < 0))
        && a%b) {
        return a/b - 1;
    }
    else {
        return a/b;
    }
}

int Arith_mod(int a, int b)
{
    return a - b*Arith_div(a, b);
}

int Arith_ceiling(int a, int b)
{
    return Arith_div(a, b) + (a % b != 0);
}

int Arith_floor(int a, int b)
{
    return Arith_div(a, b);
}

#elif __STDC_VERSION__ >= 201112L

#define ARITH_MAX__BODY(A, B) (((A) > (B)) ? (A) : (B))
#define ARITH_MIN__BODY(A, B) (((A) < (B)) ? (A) : (B))

#define ARITH_DIV__BODY(A, B)                   \
do {                                            \
    volatile int tzp = -13/5 == -2;             \
    if (tzp                                     \
        && ((A < 0) != (B < 0))                 \
        && A%B) {                               \
        return A/B - 1;                         \
    }                                           \
    else {                                      \
        return A/B;                             \
    }                                           \
} while (0)

#define ARITH_MOD__BODY(A, B) ((A) - (B)*Arith_div(A, B))

#define ARITH_CEILING__BODY(A, B) (Arith_div(A, B) + (A%B != 0))
#define ARITH_FLOOR__BODY(A, B) Arith_div(A, B)

int Arith_max__int(int a, int b)
{
    return ARITH_MAX__BODY(a, b);
}

long Arith_max__long(long a, long b)
{
    return ARITH_MAX__BODY(a, b);
}

long long Arith_max__long_long(long long a, long long b)
{
    return ARITH_MAX__BODY(a, b);
}

int Arith_min__int(int a, int b)
{
    return ARITH_MIN__BODY(a, b);
}

long Arith_min__long(long a, long b)
{
    return ARITH_MIN__BODY(a, b);
}

long long Arith_min__long_long(long long a, long long b)
{
    return ARITH_MIN__BODY(a, b);
}

int Arith_div__int(int a, int b)
{
    ARITH_DIV__BODY(a, b);
}

long Arith_div__long(long a, long b)
{
    ARITH_DIV__BODY(a, b);
}

long long Arith_div__long_long(long long a, long long b)
{
    ARITH_DIV__BODY(a, b);
}

int Arith_mod__int(int a, int b)
{
    return ARITH_MOD__BODY(a, b);
}

long Arith_mod__long(long a, long b)
{
    return ARITH_MOD__BODY(a, b);
}

long long Arith_mod__long_long(long long a, long long b)
{
    return ARITH_MOD__BODY(a, b);
}

int Arith_ceiling__int(int a, int b)
{
    return ARITH_CEILING__BODY(a, b);
}

long Arith_ceiling__long(long a, long b)
{
    return ARITH_CEILING__BODY(a, b);
}

long long Arith_ceiling__long_long(long long a, long long b)
{
    return ARITH_CEILING__BODY(a, b);
}

int Arith_floor__int(int a, int b)
{
    return ARITH_FLOOR__BODY(a, b);
}

long Arith_floor__long(long a, long b)
{
    return ARITH_FLOOR__BODY(a, b);
}

long long Arith_floor__long_long(long long a, long long b)
{
    return ARITH_FLOOR__BODY(a, b);
}

#endif

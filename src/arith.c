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

#elif __STDC_VERSION__ >= 201112L

#define ARITH_MAX__BODY(A, B) (((A) > (B)) ? (A) : (B))
#define ARITH_MIN__BODY(A, B) (((A) < (B)) ? (A) : (B))

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

#endif

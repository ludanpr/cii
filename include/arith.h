/**
 * @file arith.h
 */
#if __STDC_VERSION__ >= 201112L

int Arith_max__int(int, int);
long Arith_max__long(long, long);
long long Arith_max__long_long(long long, long long);
int Arith_min__int(int, int);
long Arith_min__long(long, long);
long long Arith_min__long_long(long long, long long);

#  define Arith_max(A, B)                            \
    _Generic((A)+(B),                                \
        int: Arith_max__int,                         \
        long: Arith_max__long,                       \
        short: Arith_max__int,                       \
        long long: Arith_max__long_long)(A, B)

#  define Arith_min(A, B)                            \
    _Generic((A)+(B),                                \
        int: Arith_min__int,                         \
        long: Arith_min__long,                       \
        short: Arith_min__int,                       \
        long long: Arith_min__long_long)(A, B)

#elif defined(__GNUC__)

#define ARITH_SIGNED_INTEGER_P(X)                                      \
    ({  __builtin_types_compatible_p(typeof(X), int)      ||           \
        __builtin_types_compatible_p(typeof(X), short)    ||           \
        __builtin_types_compatible_p(typeof(X), long)     ||           \
            __builtin_types_compatible_p(typeof(X), long long); })

#define ARITH_ASSERT_TYPES(A, B)                                             \
    _Static_assert((__builtin_types_compatible_p(typeof(A), typeof(B)) &&    \
                    ARITH_SIGNED_INTEGER_P(A) && ARITH_SIGNED_INTEGER_P(B)), \
        "Incompatibility of parameter's types.")

#  define Arith_max(A, B)                 \
    ({ ARITH_ASSERT_TYPES(A, B);          \
       typeof(A) a_ = (A);                \
       typeof(B) b_ = (B);                \
       a_ > b_ ? a_ : b_;  })

#  define Arith_min(A, B)                 \
    ({ ARITH_ASSERT_TYPES(A, B);          \
       typeof(A) a_ = (A);                \
       typeof(B) b_ = (B);                \
       a_ < b_ ? a_ : b_;  })

#else

extern int Arith_max(int, int);
extern int Arith_min(int, int);

#endif

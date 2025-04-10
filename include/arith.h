/**
 * @file arith.h
 */
#ifndef ARITH_H__
#define ARITH_H__ 1

/**
 * @func Arith_div(a, b)  Arith_mod(a, b)
 * @brief Returns the quotient obtained by dividing @a a by @a b.
 * @note When a and b are both positive or both negative, it is equal
 * to a/b and Arith_mod(a, b) is equal to a%b. When b is zero, Arith_div
 * and Arith_mod behave the same as a/b and a%b.
 * @note Arith_div and Arith_mod always truncate toward zero when their
 * operands have the same sign, and toward minus infinity when their signs
 * are different, so Arith_div(-13,5) returns -3.
 *
 * Arith_div(a, b) is the maximum integer that doesn't exceed the real
 * number c such that cb = a.
 * Arith_mod(a, b) is defined to be equal to (a - b).Arith_div(a,b).
 *
 * @func Arith_ceiling(a, b)  Arith_floor(a, b)
 * Follow similar conventions to @a Arith_div and @a Arith_mod.
 * Arith_ceiling(a, b) returns the least integer not less than the real
 * quotient of a/b.
 * Arith_floor(a, b) returns the greatest integer not exceeding the real
 * quotient of a/b.
 *
 * The C Standard insists that if x/y is representable, then (x/y)y + x%y
 * must be equal to x.
 */

#if __STDC_VERSION__ >= 201112L

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

#  define Arith_div(A, B)                            \
    _Generic((A)+(B),                                \
        int: Arith_div__int,                         \
        long: Arith_div__long,                       \
        short: Arith_div__int,                       \
        long long: Arith_div__long_long)(A, B)

#  define Arith_mod(A, B)                            \
    _Generic((A)+(B),                                \
        int: Arith_mod__int,                         \
        long: Arith_mod__long,                       \
        short: Arith_mod__int,                       \
        long long: Arith_mod__long_long)(A, B)

#  define Arith_ceiling(A, B)                        \
    _Generic((A)+(B),                                \
        int: Arith_ceiling__int,                     \
        long: Arith_ceiling__long,                   \
        short: Arith_ceiling__int,                   \
        long long: Arith_ceiling__long_long)(A, B)

#  define Arith_floor(A, B)                          \
    _Generic((A)+(B),                                \
        int: Arith_floor__int,                       \
        long: Arith_floor__long,                     \
        short: Arith_floor__int,                     \
        long long: Arith_floor__long_long)(A, B)


int Arith_max__int(int, int);
long Arith_max__long(long, long);
long long Arith_max__long_long(long long, long long);
int Arith_min__int(int, int);
long Arith_min__long(long, long);
long long Arith_min__long_long(long long, long long);

int Arith_div__int(int, int);
long Arith_div__long(long, long);
long long Arith_div__long_long(long long, long long);
int Arith_mod__int(int, int);
long Arith_mod__long(long, long);
long long Arith_mod__long_long(long long, long long);

int Arith_ceiling__int(int, int);
long Arith_ceiling__long(long, long);
long long Arith_ceiling__long_long(long long, long long);
int Arith_floor__int(int, int);
long Arith_floor__long(long, long);
long long Arith_floor__long_long(long long, long long);

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

#  define Arith_div(A, B)                 \
    ({ ARITH_ASSERT_TYPES(A, B);          \
       typeof(A) a_ = (A);                \
       typeof(B) b_ = (B);                \
       volatile int tzp = -13/5 == -2;    \
       (tzp                               \
           && ((a_ < 0) != (b_ < 0))      \
           && a_%b_)                      \
        ? a_/b_ - 1                       \
        : a_/b_;                          \
    })

#  define Arith_mod(A, B)                 \
    ({ ARITH_ASSERT_TYPES(A, B);          \
       typeof(A) a_ = (A);                \
       typeof(B) b_ = (B);                \
       volatile int tzp = -13/5 == -2;    \
       (tzp                               \
           && ((a_ < 0) != (b_ < 0))      \
           && a_%b_)                      \
        ? a_%b_ + b_                      \
        : a_%b_;                          \
    })

#  define Arith_ceiling(A, B)             \
    ({ ARITH_ASSERT_TYPES(A, B);          \
       typeof(A) a_ = (A);                \
       typeof(B) b_ = (B);                \
       volatile int tzp = -13/5 == -2;    \
       ((tzp                              \
           && ((a_ < 0) != (b_ < 0))      \
           && a_%b_)                      \
        ? a_/b_ - 1                       \
        : a_/b_) + (a_%b_ != 0);          \
    })

#  define Arith_floor(A, B)               \
    ({ ARITH_ASSERT_TYPES(A, B);          \
       typeof(A) a_ = (A);                \
       typeof(B) b_ = (B);                \
       volatile int tzp = -13/5 == -2;    \
       (tzp                               \
           && ((a_ < 0) != (b_ < 0))      \
           && a_%b_)                      \
        ? a_/b_ - 1                       \
        : a_/b_;                          \
    })
#else

extern int Arith_max(int, int);
extern int Arith_min(int, int);
extern int Arith_div(int, int);
extern int Arith_mod(int, int);
extern int Arith_ceiling(int, int);
extern int Arith_floor(int, int);

#endif

#endif

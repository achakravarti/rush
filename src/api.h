#if !defined REST_MICRO_SERVICE_HELPER
#define REST_MICRO_SERVICE_HELPER


#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <threads.h>


#if (defined __GNUC__ || defined __clang__)
#   define rush_pure __attribute__((pure))
#else
#   define rush_pure
#   warning rush_pure has no effect on non GCC-compatible compilers
#endif


#if (defined __GNUC__ || defined __clang__)
#   define rush_hot __attribute__((hot))
#else
#   define rush_hot
#   warning rush_hot has no effect on non GCC-compatible compilers
#endif


#if (defined __GNUC__ || defined __clang__)
#   define rush_cold __attribute__((cold))
#else
#   define rush_cold
#   warning rush_cold has no effect on non GCC-compatible compilers
#endif


#if (defined __GNUC__ || defined __clang__)
#   define rush_likely(p) (__builtin_expect(!!(p), 1))
#else
#   define rush_likely
#   warning rush_likely has no effect on non GCC-compatible compilers
#endif


#if (defined __GNUC__ || defined __clang__)
#   define rush_unlikely(p) (__builtin_expect(!!(p), 0))
#else
#   define rush_unlikely
#   warning rush_unlikely has no effect on non GCC-compatible compilers
#endif


typedef int rush_erno;
#define RUSH_ERNO_NIL ((rush_erno) 0x0)
#define RUSH_ERNO_HANDLE ((rush_erno) 0x1)
#define RUSH_ERNO_MPOOL ((rush_erno) 0x2)
#define RUSH_ERNO_RANGE ((rush_erno) 0x3)


#define rush_erno_get() \
        ((const rush_erno) rush__erno__)


#define rush_erno_set(e) \
        (rush__erno__ = (e))


#define RUSH_TRY                                         \
        register rush_erno rush__erno__ = RUSH_ERNO_NIL; \
        goto RUSH__TRY__;                                \
        RUSH__TRY__


#define RUSH_CATCH            \
        goto RUSH__FINALLY__; \
        RUSH__CATCH__


#define RUSH_FINALLY RUSH__FINALLY__


#define rush_assert(p, e) \
do {                                \
        if (!(p)) {                 \
                rush__erno__ = (e); \
                goto RUSH__CATCH__; \
        }                           \
} while (0)


#define rush_assert_handle(p) \
        rush_assert((p), RUSH_ERNO_HANDLE)


#define rush_assert_range(p) \
        rush_assert((p), RUSH_ERNO_RANGE)


#define rush_try(p)                 \
do {                                \
        if ((rush__erno__ = (p)))   \
                goto RUSH__CATCH__; \
} while (0)


extern rush_erno
rush_mpool_alloc(void **bfr, size_t sz);


extern rush_erno
rush_mpool_realloc(void **bfr, size_t sz);


#endif /* !defined REST_MICRO_SERVICE_HELPER */


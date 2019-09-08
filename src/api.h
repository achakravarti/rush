#if !defined REST_MICRO_SERVICE_HELPER
#define REST_MICRO_SERVICE_HELPER


#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
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
#define RUSH_ERNO_STRING ((rush_erno) 0x4)


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
        if (rush_unlikely (!(p))) { \
                rush__erno__ = (e); \
                goto RUSH__CATCH__; \
        }                           \
} while (0)


#define rush_assert_handle(p) \
        rush_assert((p), RUSH_ERNO_HANDLE)


#define rush_assert_range(p) \
        rush_assert((p), RUSH_ERNO_RANGE)


#define rush_assert_string(s) \
        rush_assert((s) && *(s), RUSH_ERNO_STRING)


#define rush_try(p)                             \
do {                                            \
        if (rush_unlikely (rush__erno__ = (p))) \
                goto RUSH__CATCH__;             \
} while (0)


extern void
rush_log_open(const char *path, bool flush);


extern void
rush_log_close(void);


extern void
rush_log_write__(const char, const char *, ...);


#define rush_log_trace(m, ...) \
        rush_log_write__('T', (m), ##__VA_ARGS__)


#define rush_log_warning(m, ...) \
        rush_log_write__('W', (m), ##__VA_ARGS__)


#define rush_log_error(m, ...) \
        rush_log_write__('E', (m), ##__VA_ARGS__)


extern rush_erno
rush_mpool_alloc(void **bfr, size_t sz);


extern rush_erno
rush_mpool_realloc(void **bfr, size_t sz);


typedef char rush_string;

extern rush_erno
rush_string_new(rush_string **ctx, const char *cstr);

inline rush_erno
rush_string_copy(rush_string **ctx, const rush_string *src)
{
        return rush_string_new (ctx, src);
}

extern rush_erno
rush_string_len(const rush_string *ctx, size_t *len);

extern rush_erno
rush_string_sz(const rush_string *ctx, size_t *sz);

extern rush_erno
rush_string_cmp(const rush_string *ctx, const rush_string *rhs, int *cmp);

extern rush_erno
rush_string_add(const rush_string **ctx, const rush_string *add);

extern rush_erno
rush_string_find(const rush_string *ctx, const rush_string *what, size_t *loc);

extern rush_erno
rush_string_replace_first(rush_string **ctx, const rush_string *what,
                          const rush_string *with);

extern rush_erno
rush_string_replace(rush_string **ctx, const rush_string *what,
                    const rush_string *with);


#endif /* !defined REST_MICRO_SERVICE_HELPER */


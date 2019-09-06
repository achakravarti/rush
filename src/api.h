#if !defined REST_MICRO_SERVICE_HELPER
#define REST_MICRO_SERVICE_HELPER


#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <threads.h>


typedef int rush_erno;
#define RUSH_ERNO_NIL ((rush_erno) 0x0)


#define rush_erno_get() \
        ((const rush_erno) rush__erno__


#define rush_erno_set(e) \
        (rush__erno__ = (e))


#define RUSH_TRY                                       \
        register rush_erno rush__erno_= RUSH_ERNO_NIL; \
        goto RUSH__TRY;                                \
        RUSH__TRY__


#define RUSH_CATCH         \
        goto RUSH_FINALLY; \
        RUSH__CATCH__


#define RUSH_FINALLY


#define rush_assert(p, e) \
do {                                \
        if (!(p)) {                 \
                rush__erno__ = (e); \
                goto RUSH__CATCH__; \
        }                           \
} while (0)


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


#if !defined REST_MICRO_SERVICE_HELPER
#define REST_MICRO_SERVICE_HELPER


#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <threads.h>


typedef int rush_erno;
#define RUSH_ERNO_NIL ((rush_erno) 0x0)


extern rush_erno
rush_mpool_alloc(void **bfr, size_t sz);


extern rush_erno
rush_mpool_realloc(void **bfr, size_t sz);


#endif /* !defined REST_MICRO_SERVICE_HELPER */


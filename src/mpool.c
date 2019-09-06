#include <gc.h>
#include "api.h"


static thread_local bool gc_flag = false;


static inline void
gc_init(void)
{
        if (!gc_flag) {
                GC_INIT();
                gc_flag = true;
        }
}


extern rush_erno
rush_mpool_alloc(void **bfr, size_t sz)
{
RUSH_TRY:
        rush_assert_handle(bfr);
        rush_assert_range(sz);

        gc_init();
        *bfr = GC_MALLOC(sz);
        rush_assert_handle(*bfr);

RUSH_CATCH:
        rush_erno_set(RUSH_ERNO_MPOOL);

RUSH_FINALLY:
        return rush_erno_get();
}


extern rush_erno
rush_mpool_realloc(void **bfr, size_t sz)
{
RUSH_TRY:
        rush_assert_handle(bfr);
        rush_assert_range(sz);

        gc_init();
        *bfr = GC_REALLOC(*bfr, sz);
        rush_assert_handle(*bfr);

RUSH_CATCH:
        rush_erno_set(RUSH_ERNO_MPOOL);

RUSH_FINALLY:
        return rush_erno_get();
}


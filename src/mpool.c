#include <gc.h>
#include "api.h"


static thread_local bool gc_init = false;


extern rush_erno
rush_mpool_alloc(void **bfr, size_t sz)
{
        if (!gc_init)
                GC_INIT();

        *bfr = GC_MALLOC(sz);
        return *bfr != 0;
}


extern rush_erno
rush_mpool_realloc(void **bfr, size_t sz)
{
        if (!gc_init)
                GC_INIT();

        *bfr = GC_REALLOC(*bfr, sz);
        return *bfr != 0;
}


#include <string.h>
#include "api.h"


#define NULLCHAR_OFFSET 1


static inline bool
utf8_continuation(char c)
{
    return (c & 0xC0) == 0x80;
}


static inline size_t
utf8_strlen(const char *str)
{
    register size_t i = 0, len = 0;

    while (str[i]) {
        if (!utf8_continuation (str[i]))
            len++;

        i++;
    }

    return len;
}


static rush_erno
replace_first(rush_string **ctx, const rush_string *what,
              const rush_string *with)
{
RUSH_TRY:
        ;char *pos = strstr (*ctx, what);
        if (!pos)
                return rush_string_copy(ctx, what);

        const size_t ctxsz = strlen (*ctx);
        const size_t whatsz = strlen (what);
        const size_t withsz = strlen (with);
        const size_t diffsz = withsz - whatsz;

        rush_string *tmp = NULL;
        rush_try (rush_mpool_alloc ((void **) &tmp,
                                    whatsz + diffsz + NULLCHAR_OFFSET));

        size_t shifts = pos - *ctx;
        memcpy (tmp, *ctx, shifts);
        memcpy (tmp + shifts, with, withsz);
        memcpy (tmp + shifts + withsz, pos + whatsz, ctxsz - shifts - whatsz);

        tmp [ctxsz + diffsz] = '\0';
        *ctx = tmp;

RUSH_CATCH:
        rush_erno_set (RUSH_ERNO_STRING);

RUSH_FINALLY:
        return rush_erno_get ();
}


extern rush_erno
rush_string_new(rush_string **ctx, const char *cstr)
{
RUSH_TRY:
        rush_assert_string (cstr);

        const size_t sz = strlen (cstr) + NULLCHAR_OFFSET;
        rush_try (rush_mpool_alloc ((void **) ctx, sz));
        (void) strncpy (*ctx, cstr, sz);

RUSH_CATCH:
        rush_erno_set (RUSH_ERNO_STRING);

RUSH_FINALLY:
        return rush_erno_get ();
}


extern inline rush_erno
rush_string_copy(rush_string **ctx, const rush_string *src);


extern rush_erno
rush_string_len(const rush_string *ctx, size_t *len)
{
RUSH_TRY:
        rush_assert_handle (ctx && len);

        *len = utf8_strlen (ctx);

RUSH_CATCH:
        rush_erno_set(RUSH_ERNO_STRING);

RUSH_FINALLY:
        return rush_erno_get();
}


extern rush_erno
rush_string_sz(const rush_string *ctx, size_t *sz)
{
RUSH_TRY:
        rush_assert_handle (ctx);

        *sz = strlen (ctx) + NULLCHAR_OFFSET;

RUSH_CATCH:
        rush_erno_set(RUSH_ERNO_STRING);

RUSH_FINALLY:
        return rush_erno_get();
}


extern rush_erno
rush_string_cmp(const rush_string *ctx, const rush_string *rhs, int *cmp)
{
RUSH_TRY:
        rush_assert_handle (ctx && rhs && cmp);

        *cmp = strcmp (ctx, rhs);

RUSH_CATCH:
        rush_erno_set(RUSH_ERNO_STRING);

RUSH_FINALLY:
        return rush_erno_get();
}


extern rush_erno
rush_string_add(const rush_string **ctx, const rush_string *add)
{
RUSH_TRY:
        rush_assert_handle (ctx && *ctx && add);

        const size_t llen = strlen (*ctx) + NULLCHAR_OFFSET;
        const size_t rlen = strlen (add) + NULLCHAR_OFFSET;

        rush_string *cat = NULL;
        rush_try (rush_mpool_alloc ((void **) &cat, llen + rlen));

        (void) strncpy (cat, *ctx, llen);
        *ctx = strncat (cat, add, rlen);

RUSH_CATCH:
        rush_erno_set(RUSH_ERNO_STRING);

RUSH_FINALLY:
        return rush_erno_get();
}


extern rush_erno
rush_string_find(const rush_string *ctx, const rush_string *what, size_t *loc)
{
RUSH_TRY:
        rush_assert_handle (ctx && what && loc);

        const size_t offset = 1;
        const rush_string *sub = strstr (ctx, what);
        *loc = sub ? (utf8_strlen (ctx) - utf8_strlen (sub) + offset) : 0;

RUSH_CATCH:
        rush_erno_set(RUSH_ERNO_STRING);

RUSH_FINALLY:
        return rush_erno_get();
}


extern rush_erno
rush_string_replace_first(rush_string **ctx, const rush_string *what,
                          const rush_string *with)
{
RUSH_TRY:
        rush_assert_handle (ctx && *ctx && what && with);

        return replace_first (ctx, what, with);

RUSH_CATCH:
        rush_erno_set(RUSH_ERNO_STRING);

RUSH_FINALLY:
        return rush_erno_get();
}

extern rush_erno
rush_string_replace(rush_string **ctx, const rush_string *what,
                    const rush_string *with)
{
RUSH_TRY:
        rush_assert_handle (ctx && *ctx && with);
        rush_assert_string (what);

        if (rush_likely (!strstr (with, what))) {
                rush_try (replace_first (ctx, what, with));

                while (strstr (*ctx, what))
                        rush_try (replace_first (ctx, what, with));
        }

        const char placeholder[] = { 0x1, 0x0 };
        rush_try (replace_first (ctx, what, placeholder));

        while (strstr (*ctx, what))
                rush_try (replace_first (ctx, what, placeholder));

        rush_try (replace_first (ctx, placeholder, with));

        while (strstr (*ctx, placeholder))
                rush_try (replace_first (ctx, placeholder, with));

RUSH_CATCH:
        rush_erno_set(RUSH_ERNO_STRING);

RUSH_FINALLY:
        return rush_erno_get();
}


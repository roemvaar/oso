#include "mem.h"

static MemBlock_t *stacks[BLOCK_COUNT];

void mem_init(void)
{
    return;
}

MemBlock_t *get_mem(void)
{
    return NULL;
}

void free_mem(MemBlock_t *block)
{
    return;
}

/* Define our own memset to avoid SIMD instructions emitted from the compiler */
void *memset(void *s, int c, size_t n)
{
    for (char* it = (char*)s; n > 0; --n) *it++ = c;

    return s;
}

/* Define our own memcpy to avoid SIMD instructions emitted from the compiler */
void *memcpy(void* restrict dest, const void* restrict src, size_t n)
{
    char* sit = (char*)src;
    char* cdest = (char*)dest;

    for (size_t i = 0; i < n; ++i) {
        *(cdest++) = *(sit++);
    }

    return dest;
}

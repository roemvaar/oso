#include "mm.h"

#include "peripherals/uart.h"   // TODO(roemvaar): Delete this - don't print from here

// static MemBlock_t stacks[BLOCK_COUNT];

static unsigned short mem_map[BLOCK_COUNT];

// void mem_init(void)
// {
//     for (int i = 0; i < BLOCK_COUNT; i++) {
//         stacks[i].mem[0] = i * 2;
//     }

//     for (int i = 0; i < BLOCK_COUNT; i++) {
//         uart_printf(CONSOLE, "stack %i: mem[0] = %d\r\n", (int)i, stacks[i].mem[0]);
//     }

//     return;
// }

// MemBlock_t *get_mem_by_tid(int tid)
// {
//     return &stacks[tid];
// }

void free_mem(MemBlock_t *block)
{
    (void)block;

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

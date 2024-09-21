#ifndef MM_H_
#define MM_H_

#include <stddef.h>     // TODO(roemvaar): DELETE THIS, create types.h and don't use stdlib

#include "sched.h"

#define MEM_BLOCK_SIZE 0x10000
#define BLOCK_COUNT NR_TASKS

// typedef struct mem_block {
//     int address;
//     struct mem_block *next;
// } MemBlock_t;

// typedef struct mem_block MemBlock_t;
typedef struct mem_block
{
    unsigned long mem[MEM_BLOCK_SIZE];
} MemBlock_t;

void mem_init(void);
MemBlock_t *get_mem_by_tid(int tid);
void free_mem(MemBlock_t *block);

void *memset(void *s, int c, size_t n);
void *memcpy(void *restrict dest, const void *restrict src, size_t n);

#endif  /* MM_H_ */

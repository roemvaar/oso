#ifndef MEM_H_
#define MEM_H_

#include <stddef.h>     // TODO(roemvaar): DELETE THIS - don't use stdlib

// Play with stack size from 1MB to 4MB
// If we pretend that we will use only half of the ram (1GB / 2 = 512 MB)
// Stack 1MB... up to 512 tasks running simultaneously
// Stack 4MB... up to 128 tasks running simultaneously

typedef struct _memory_block MemoryBlock_t;
typedef struct _memory_block
{
    int address;
    struct MemBlock *next;
} MemoryBlock_t;

// memory
void *memset(void *s, int c, size_t n);
void *memcpy(void* restrict dest, const void* restrict src, size_t n);

#endif  /* MEM_H_ */

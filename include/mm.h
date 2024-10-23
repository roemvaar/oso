#ifndef MM_H_
#define MM_H_

#include <stddef.h>     // TODO(roemvaar): DELETE THIS, create types.h and don't use stdlib

void *memset(void *s, int c, size_t n);
void *memcpy(void *restrict dest, const void *restrict src, size_t n);

#endif  /* MM_H_ */

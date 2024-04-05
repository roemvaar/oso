#ifndef UTIL_H_
#define UTIL_H_

#include <stddef.h>     // TODO(roemvaar): DELETE THIS - don't use stdlib

// #define NULL ((void*)0)

// conversions
int a2d(char ch);
char a2i(char ch, char **src, int base, int *nump);
void ui2a(unsigned int num, unsigned int base, char *bf);
void i2a(int num, char *bf);

// memory
void *memset(void *s, int c, size_t n);
void* memcpy(void* restrict dest, const void* restrict src, size_t n);

#endif  /* UTIL_H_ */

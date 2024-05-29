#ifndef UTIL_H_
#define UTIL_H_

#include <stddef.h>     // TODO(roemvaar): DELETE THIS - don't use stdlib

// #define NULL ((void*)0)

// conversions
int hex_char_to_int(char ch);
char a2i(char ch, char **src, int base, int *nump);
void ui2a(unsigned int num, unsigned int base, char *bf);
void i2a(int num, char *bf);

#endif  /* UTIL_H_ */

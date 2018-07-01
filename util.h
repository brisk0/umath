#ifndef UTIL_H
#define UTIL_H

#define _XOPEN_SOURCE

#include <stdlib.h>
#include <wchar.h>

/*
 * Nonspecific utility functions and macros
 */

#define max(a,b) ((a) >= (b) ? (a) : (b))

int mbwidth(char *str); 

#endif /* UTIL_H */

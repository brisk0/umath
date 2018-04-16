#ifndef BLOCK_SYM_H
#define BLOCK_SYM_H 

/*
 * Block creation routines for symbols
 */


#include "block.h"

// Dispatches to other bracket funcs based on bracket
// E.g. bracket(5,"{") → obrace(5);
Block
bracket(int height, const char *bracket);
// Creates an opening parenthesis of arbitrary height;
Block
oparen(int height);

// Creates a closing parenthesis of arbitrary height;
Block
cloparen(int height);

// [
Block
obracket(int height);

// ]
Block
clobracket(int height);

// {
Block
obrace(int height);

// }
Block
clobrace(int height);

#endif /* BLOCK_SYM_H */

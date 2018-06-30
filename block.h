#ifndef BLOCK_H
#define BLOCK_H

/*
 * Defines "Block" object for building arrays of terminal output.
 * Blocks are designed to operate as rectangular arrays of graphemes and are
 * represented by an array of strings. As unicode graphemes do not map to
 * chars, the strings may vary in length. 
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

typedef struct {
	int width;
	int height;
	// Array of length "height"
	char **lines;
} Block;

// Allocates a new block to be later cleaned up with cleanup_blocks()
// lines is safely duplicated, and so need not persist after the call
// to new_block()
Block *new_block(int width, int height, char **lines);

void cleanup_blocks();

void print_block(Block *block);

void free_block(Block *block);

// Create an arbitrarily sized block of spaces
Block *
spaces(int width, int height);

// Centers the given block in a field of spaces of shape width*height
// If either dimension is less than or equal to the dimension of the original
// block, the block is left untouched in that dimension.
// In case the block cannot be perfectly centred, it will be shifted towards
// the left-bottom of the new block
Block *
center(int width, int height, Block *block);

// Concats two blocks, one atop the other
Block *
concatv(Block *b1, Block *b2);

// Concatenates two blocks, side by side
Block *
concath(Block *b1, Block *b2);

// Horizontally stretches a single character to width "width"
// E.g. stretch1h(3, "-") → "---"
Block *
stretch1h(int width, char *fill);

// Stretches a 3-part symbol to arbitrary height
// E.g. stretchv(4,"⎛","⎜","⎝") produces:
// ⎛
// ⎜
// ⎜
// ⎝
Block *
stretch3v(int height, char * start, char *fill, char *end);

// Same as above but inserts "mid" in the center (or center +1 if odd)
Block *
stretch4v(int height, char * start, char *fill, char *mid, char *end);

// Same as above but inserts two mid characters at height/2 and height/2 + 1
// in the center
Block *
stretch5v(int height, char * start, char *fill, char *mid1, char *mid2, char *end);

// Returns a block containing a single grapheme
Block *
single(char *sym);

#endif /* BLOCK_H */

#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "util.h"
#include "token.h"
#include "block.h"
#include "block_sym.h"

void
error_expected(char *expect);

// Parse a sequence of tokens into a block, printable via print_block
// Not thread-safe
Block *
parse(struct Token *in);

#endif /* PARSE_H */

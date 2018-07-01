#include "token.h"
#include "parse.h"
#include "block.h"

char *umath(const char *input) {
	tokenize(input);
	char *output = str_block(parse(toklist));
	cleanup_blocks();
	return output;
}

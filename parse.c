#include "parse.h"

static struct Token *in;

void
error_expected(char *expect) {
	fprintf(stderr, "Parse error: Expected %s", expect);
	exit(EXIT_FAILURE);
}


// Determines whether the next token is of the requested type
// If so, the token pointer is advanced
// Else throw an error and exit program 
static bool
expect(enum TokenType t) {
	if(in == NULL) {
		fprintf(stderr, "Reached end of input before expected %s\n", tok_string[t]);
		exit(EXIT_FAILURE);
	}
	if(in->type == t) {
		in++;
		return true;
	} else {
		//TODO encode column num in tokens
		fprintf(stderr,"Expected %s, found %s instead\n", tok_string[t], tok_string[in->type]);
		exit(EXIT_FAILURE);
	}
}

// Consumes the next token if it is of the requested type and returns true 
static bool
accept(enum TokenType t) {
	if(in->type == t) {
		in++;
	return true;
	} 
	return false;
}

/*
 * Each nonterminal is represented by a function here. Terminals are
 * represented by token(TokenType). 
 * See grammar.ebnf for a mostly-formal grammar.
 */

static Block *factor();
static Block *term();
static Block *expression();

static Block *
value() {
	Block *block = NULL;
	if(in->type == NUM || in->type == VAR) {
		int height = 1;
		int width = mbwidth(in->name);
		char *lines[1];
		lines[0] = in->name;
		block = new_block(width, height, lines);
		in++;
	}
	return block;
}

static Block *
factor() {
	Block *block = NULL;
	if(accept(OPAREN)) {
		block = expression();
		expect(CLOPAREN);
		block = concath(oparen(block->height), block);
		block = concath(block, cloparen(block->height));
	} else if(accept(OBRACKET)) {
		block = expression();
		expect(CLOBRACKET);
		block = concath(obracket(block->height), block);
		block = concath(block, clobracket(block->height));
	} else if(accept(OBRACE)) {
		block = expression();
		expect(CLOBRACE);
		block = concath(obrace(block->height), block);
		block = concath(block, clobrace(block->height));
	} else {
		block = value();
	}
	return block;
}

static Block *
fraction() {
	Block *block;
	block = factor();
	if(block && accept(DIV)) {
		Block *block2 = fraction();
		if(block2) {
			block = concatv(block, stretch1h(max(block->width, block2->width),"⎯"));
			block = concatv(block, block2);
		}
	} 
	return block;
}

static Block *
term() {
	Block *block;
	block = fraction();
	if(accept(PROD)) {
		block = concath(block, single("⋅"));
		block = concath(block, term());
	} 
	return block;
}

static Block *
expression() {
	Block *block;
	block = term();
	if(accept(ADD)) {
		block = concath(block, single("+"));
		block = concath(block, expression());
	} else if(accept(SUB)) {
		block = concath(block, single("-"));
		block = concath(block, expression());
	}
	return block;
}

Block *
parse(struct Token *input)
{
	in = input;
	Block *block = expression();
	if(in->type != EOL) {
		fprintf(stderr, "Trailing characters; Possible missing operator before %s\n", in->name? in->name : tok_string[in->type]);
		exit(EXIT_FAILURE);
	}
	return block;	
}

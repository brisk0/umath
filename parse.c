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
 * expect() is a macro which makes the function return false if the result is
 * unacceptable.
 */

static Block factor();
static Block term();
static Block expression();


static Block
factor() {
	Block block;
	if(in->type == OPAREN) {
		in++;
		block = expression();
		expect(CLOPAREN);
		block = concath(oparen(block.height), block);
		block = concath(block, cloparen(block.height));
	} else if(in->type == NUM) {
		block.height = 1;
		block.width = strlen(in->name);
		block.lines = calloc(1, sizeof(char *));
		block.lines[0] = strdup(in->name);
		in++;
	} else if(in->type == VAR) {
		block.height = 1;
		block.width = strlen(in->name);
		block.lines = calloc(1, sizeof(char *));
		block.lines[0] = strdup(in->name);
		in++;
	} else {
		fprintf(stderr,"Expected factor, found %s instead\n", tok_string[in->type]);
		exit(EXIT_FAILURE);
	}
	return block;
}

static Block
term() {
	Block block = factor();
	while(in->type == PROD || in->type == DIV) {
		if(in->type == PROD) {
			in++;
			// For explicit mul:
			//block = concath(block, single("×"));
			block = concath(block, factor());
		} else if(in->type == DIV) {
			in++;
			Block block2 = factor();
			block = concatv(block, stretch1h(max(block.width, block2.width),"⎯"));
			block = concatv(block, block2);
		} 
	}

	return block;
}

static Block
expression() {
	Block block = term();
	if(in->type == ADD) {
		in++;
		block = concath(block, single("+"));
		block = concath(block, expression());
	} else if (in->type == SUB) {
		in++;
		block = concath(block, single("−"));
		block = concath(block, expression());
	}
	return block;
}

Block
parse(struct Token *input)
{
	in = input;
	Block block = expression();
	if(in->type != EOL) {
		fprintf(stderr, "Trailing characters; Possible missing operator before %s\n", in->name? in->name : tok_string[in->type]);
		exit(EXIT_FAILURE);
		
	}
	return block;
	
}

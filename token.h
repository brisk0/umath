#ifndef TOKEN_H
#define TOKEN_H

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>

enum TokenType {
	NONE,
	START_OP,
	PROD,
	DIV,
	ADD,
	SUB,
	EXP,
	END_OP,
	OPAREN,
	CLOPAREN,
	OBRACE,
	CLOBRACE,
	OBRACKET,
	CLOBRACKET,
	NUM,
	VAR,
	EOL
};

// Strings for error messages
extern const char *tok_string[];

struct Token {
	enum TokenType type;
	double val; // for numeric types (or possibly not if we never need to know their value)
	char *name; // for variable types
	int line;
	int col;
};

struct Token *toklist;
int tokcount;

void tokenize(const char * in);
#endif

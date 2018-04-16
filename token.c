#include "token.h"

static int tokcap = 8;
static const char *in;

const char *tok_string[] = {
	"NOT AN OPERATOR",
	"NOT AN OPERATOR",
	"'*'",
	"'/'",
	"'+'",
	"'-'",
	"'^'",
	"NOT AN OPERATOR",
	"'('",
	"')'",
	"'{'",
	"'}'",
	"'['",
	"']'",
	"a number",
	"a variable",
	"end of line"
};

void tok_add(struct Token token) {
	if(tokcount >= tokcap) {
		tokcap = tokcap*1.5;
		toklist = realloc(toklist, tokcap * sizeof *toklist);
	}
	toklist[tokcount] = token;
	tokcount++;
}

bool tokisop(struct Token tok) {
	switch(tok.type) {
		case START_OP ... END_OP:
			return true;
			break;
		default:
			return false;
			break;

	}
}

// Valid characters for variable names
bool issym(char c) {
	switch(c) {
		case 'A' ... 'Z':
		case 'a' ... 'z':
		case '_': // Subscripts valid in variable names. Superscripts are not because of exponentiation
		case '\'': // prime. This *may* become a differentiation operator at some point
			return true;
			break;
		default:
			return false;
			break;
	}
}

static struct Token tok_var() {
	int n = 0;
	const char *start = in;
	while (*in && issym(*in)) {
		in++;
		n++;
	}
	struct Token tok = {.type = VAR, .name=strndup(start, n)};
	return tok;
}

// Number format {'0'..'9'}['.'{'0'..'9'}][('e'|'E')['+'|'-']{'0'..'9'}['.'{'0'..'9'}]]
// e.g. 1.25e23
static struct Token tok_num() {
	int n = 0;
	const char *start = in;
	while(isdigit(*in)) {
		in++;
		n++;
	}
	if(*in == '.') {
		in++;
		n++;
		while(isdigit(*in)) {
			in++;
			n++;
		}
	}
	if(*in == 'e') {
		while(isdigit(*in)) {
			in++;
			n++;
		}
		if(*in == '.') {
			in++;
			n++;
			while(isdigit(*in)) {
				in++;
				n++;
			}
		}
	}
	struct Token tok;
	tok.type = NUM;
	tok.name = strndup(start, n);
	tok.val = strtod(start, NULL);
	return tok;
}


void tokenize(const char * input) {
	tokcount = 0;
	in = input;

	struct Token tok;

	// init toklist
	toklist = malloc(tokcap * sizeof *toklist);

	while(*in) {
		tok.type = NONE;
		switch(*in) {
			case '+': tok.type = ADD; break;
			case '-': tok.type = SUB; break;
			case '*': tok.type = PROD; break;
			case '/': tok.type = DIV; break;
			case '^': tok.type = EXP; break;
			case '(': tok.type = OPAREN; break;
			case ')': tok.type = CLOPAREN; break;
			case '{': tok.type = OBRACE; break;
			case '}': tok.type = CLOBRACE; break;
			case '[': tok.type = OBRACKET; break;
			case ']': tok.type = CLOBRACKET; break;
			case '0' ... '9': tok.type = NUM; break;
			case 'a' ... 'z':
			case 'A' ... 'Z': tok.type = VAR; break;
			case '\n': tok.type = EOL; break;
			default: break;
		}
		if(tok.type == NUM) {
			//char *end = NULL;
			//errno = 0;
			//tok.val = strtod(in, &end);
			//if(errno) {
			//	perror("string-number conversion");
			//}
			//if(in == end) {
			//	printf("Invalid Number %s\n", in);
			//	in++;
			//} else {
			//	in = (const char *)end;
			//}
			tok = tok_num();
		} else if(tok.type == VAR){
			tok = tok_var();
		} else {
			in++;
		}
		if(tok.type != NONE) {
			tok_add(tok);
		}
	}
}

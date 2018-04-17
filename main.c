// UMATH terminal based natural input calculator utilising unicode mathsyms

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "token.h"
#include "parse.h"

void print_tok(struct Token tok) {
	switch(tok.type) {
		case PROD: printf("PROD"); break;
		case DIV:  printf("DIV"); break;
		case ADD:  printf("ADD"); break;
		case SUB:  printf("SUB"); break;
		case EXP:  printf("EXP"); break;
		case NUM:  printf("NUM(%s)", tok.name); break;
		case VAR:  printf("VAR(%s)", tok.name); break;
		default: printf("UNKNOWNTOKEN"); break;
	}
}

int main(int argc, char *argv[]) {
	char *input;
	size_t n;

	//while(true) {
		n = 0;
		input = NULL;

		getline(&input, &n, stdin);
		tokenize(input);
		// printf("Completed tokenization\n");
		//for(int i = 0; i < tokcount; i++) {
		//	print_tok(toklist[i]);
		//	printf(" ");
		//}
		// printf("\nCompleted printing\n");
		print_block(parse(toklist));

		free(input);
	//}
	return EXIT_SUCCESS;
}

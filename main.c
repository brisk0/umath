// UMATH terminal based natural input calculator utilising unicode mathsyms

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "umath.h"

int main(int argc, char *argv[]) {
	char *input;

	input = readline("> ");
	if(!input) {
		return EXIT_SUCCESS;
	}
	
	char *output = umath(input);
	printf("%s", output);

	free(output);
	free(input);

	return EXIT_SUCCESS;
}

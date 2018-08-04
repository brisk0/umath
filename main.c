// UMATH terminal based natural input calculator utilising unicode mathsyms

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include "umath.h"

#define _POSIX_C_SOURCE 200809L

int main(int argc, char *argv[]) {
	char *input = NULL;

	// Input modes
	if(argc >= 2) {
		// Cmdline argument
		input = argv[1];
	} else if(isatty(fileno(stdin))) {
		// Interactive terminal
		input = readline("> ");
	} else {
		// Pipe
		size_t n = 0;
		ssize_t result = getline(&input, &n, stdin);
		if(result == -1) {
			if(errno == EINVAL) {
				fprintf(stderr, "Bad argument to getline()\n");
			} else if (errno == ENOMEM) {
				fprintf(stderr, "Line allocation failed\n");
			}
		}
		// Strip newline
		if(input[result - 1] == '\n') {
			input[result - 1] = '\0';
		}
	}

	if(!input) {
		return EXIT_SUCCESS;
	}

	char *output = umath(input);
	printf("%s", output);

	free(output);
	if(argc < 2) free(input);

	return EXIT_SUCCESS;
}

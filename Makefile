FILENAME=umath
SRCNAME=main.c
DEPS=umath.c token.c block.c block_sym.c parse.c util.c
STD=gnu11

all: $(FILENAME)

release: *.h *.c
	clang $(SRCNAME) $(DEPS) -o$(FILENAME) -std=$(STD) -lm -lz -lreadline -Wall -O2

$(FILENAME): *.h *.c
	clang $(SRCNAME) $(DEPS) -o$(FILENAME) -std=$(STD) -lm -lz -lreadline -Wall -O0 -g

debug: *.h *.c
	clang $(SRCNAME) $(DEPS) -o$(FILENAME) -std=$(STD) -lm -lz -lreadline -Wall -O0 -g -fsanitize=address -fsanitize=undefined

run: $(FILENAME)
	./$(FILENAME)

.PHONY: all run

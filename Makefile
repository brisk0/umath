FILENAME=umath
SRCNAME=main.c
DEPS=umath.c token.c block.c block_sym.c parse.c util.c
STD=gnu11
CC=clang

all: release

release: *.h *.c
	$(CC) $(SRCNAME) $(DEPS) -o$(FILENAME) -std=$(STD) -lm -lz -lreadline -Wall -O2

$(FILENAME): *.h *.c
	$(CC) $(SRCNAME) $(DEPS) -o$(FILENAME) -std=$(STD) -lm -lz -lreadline -Wall -O0 -g

debug: *.h *.c
	$(CC) $(SRCNAME) $(DEPS) -o$(FILENAME) -std=$(STD) -lm -lz -lreadline -Wall -O0 -g -fsanitize=address -fsanitize=undefined

run: $(FILENAME)
	./$(FILENAME)

.PHONY: all release run

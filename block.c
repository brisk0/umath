#include "block.h"

/*
 *  Block Memory management
 */

static Block ** block_list = NULL;
static int block_count = 0;
static int block_cap = 0;

Block *new_block(int width, int height, char **lines){
	// Init list
	if(!block_list){
		block_list = malloc(8 * sizeof(Block *));
		block_cap = 8;
	}

	// Expand list
	if(block_count == block_cap) {
		block_list = realloc(block_list, 1.5 * block_cap * sizeof(Block *));
		block_cap = 1.5 * block_cap;
	}

	// Copy lines so that we control their lifetime
	char **lines_dup = malloc(height * sizeof(char *));
	for(int i = 0; i < height; i++) {
		lines_dup[i] = strdup(lines[i]);
	}
	
	Block * new_block = malloc(sizeof(Block));
	*new_block = (Block){width, height, lines_dup};
	//printf("count:%d, cap:%d, allocation:\n", block_count, block_cap);
	//new_block? print_block(new_block) : printf("NULL\n");

	block_list[block_count++] = new_block;
	return new_block;
}

void cleanup_blocks() {
	for(int i = 0; i < block_count; i++) {
		free_block(block_list[i]);
	}
	free(block_list);
	block_list = NULL;
}

/*
 *  Block Construction Operations
 */

char *str_block(Block *block) {
	int bufsize = 0;
	for(int i = 0; i < block->height; i++) {
		bufsize += strlen(block->lines[i]) + 1;
	}
	char *buffer = malloc(bufsize + 1);
	char *head = buffer;

	for(int i = 0; i < block->height; i++) {
		head += sprintf(head, "%s\n", block->lines[i]);
	}

	return buffer;
}

void print_block(Block *block) {
	if(!block) return;
	for(int i = 0; i < block->height; i++) {
		printf("%s\n", block->lines[i]);
	}
}

void free_block(Block *block) {
	for(int i=0; i < block->height; i++) {
		free(block->lines[i]);
	}
	free(block->lines);
	free(block);
}

Block *
spaces(int width, int height) {
	//Block * block = malloc(sizeof(Block));
	//block->height = height;
	//block->width = width;
	//block->lines = calloc(height, sizeof(char *));
	char line[width + 1];

	for(int i=0; i < width; i++) {
		line[i] = ' ';
	}
	line[width] = '\0';

	char *lines[height];
	for(int i=0; i < height; i++) {
		lines[i] = line;
	}

	return new_block(width, height, lines);

}

Block *
center(int width, int height, Block *block) {
	if(!block) return NULL;
	// Width
	if(width > block->width) {
		int diff = (width - block->width);
		int leftmargin = diff/2;
		int rightmargin = diff/2 + diff%2;
		Block *left = spaces(leftmargin, block->height);
		Block *right = spaces(rightmargin, block->height);
		block = concath(left, block);
		block = concath(block, right);
	}
	
	// Height
	if(height > block->height) {
		int diff = (height - block->height);
		int topmargin = diff/2 + diff%2;
		int botmargin = diff/2;
		Block *top = spaces(block->width, topmargin);
		Block *bottom = spaces(block->width, botmargin);
		block = concatv(top, block);
		block = concatv(block, bottom);
	}
	return block;
}

Block *
concatv(Block *b1, Block *b2) {
	if(!b1) return b2;
	if(!b2) return b1;

	int width = max(b1->width, b2->width);
	int height = b1->height + b2->height;
	char *lines[height];

	Block *top    = center(width, 0, b1);
	Block *bottom = center(width, 0, b2);

	for(int i = 0; i < height; i++) {
		if(i < top->height) {
			lines[i] = top->lines[i];
		} else {
			lines[i] = bottom->lines[i - top->height];
		}
	}

	return new_block(width, height, lines);
}

Block *
concath(Block *b1, Block *b2) {
	if(!b1) return b2;
	if(!b2) return b1;

	int height = max(b1->height, b2->height);
	int width = b1->width + b2->width;
	b1 = center(b1->width, height, b1);
	b2 = center(b2->width, height, b2);

	// Concatenate each line
	char *lines[height];
	for(int i=0; i < height; i++) {
		lines[i] = calloc(strlen(b1->lines[i]) + strlen(b2->lines[i]) + 1, sizeof(char));
		lines[i] = strcpy(lines[i], b1->lines[i]);
		lines[i] = strcat(lines[i], b2->lines[i]);
	}

	Block *block = new_block(width, height, lines);

	// Cleanup
	for(int i=0; i < height; i++) {
		free(lines[i]);
	}

	return block;
}

Block *
stretch1h(int width, const char *fill) {
	int height = 1;

	char *lines[1];
	char line[strlen(fill)*width + 1];
	lines[0] = line;

	lines[0][0] = '\0';
	for(int i=0; i < width; i++) {
		lines[0] = strcat(lines[0], fill);
	}

	return new_block(width, height, lines);
}

Block *
stretch3v(int height, const char * start, const char *fill, const char *end) {
	int width = 1;
	char *lines[height];
	lines[0] = (char *)start;
	lines[height-1] = (char *)end;
	for(int i=1; i < height - 1; i++) {
		lines[i] = (char *)fill;
	}

	return new_block(width, height, lines);
}

Block *
stretch4v(int height, const char * start, const char *fill, const char *mid, const char *end) {
	Block *block = stretch3v(height, start, fill, end);
	free(block->lines[height/2]);
	block->lines[height/2] = strdup(mid);

	return block;
}

Block *
stretch5v(int height, const char * start, const char *fill, const char *mid1, const char *mid2, const char *end) {
	Block *block = stretch3v(height, start, fill, end);
	free(block->lines[height/2]);
	block->lines[height/2] = strdup(mid1);
	free(block->lines[height/2 + height%2]);
	block->lines[height/2 + height%2] = strdup(mid2);

	return block;
}

Block *
single(const char *sym) {
	int width = 1;
	int height = 1;
	char *lines[] = {(char *)sym};

	return new_block(width, height, lines);
}

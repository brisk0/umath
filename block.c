#include "block.h"
/*
 *  Block Construction Operations
 */

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
	Block * block = malloc(sizeof(Block));
	block->height = height;
	block->width = width;
	block->lines = calloc(height, sizeof(char *));
	char line[width + 1];

	for(int i=0; i < width; i++) {
		line[i] = ' ';
	}
	line[width] = '\0';

	for(int i=0; i < height; i++) {
		block->lines[i] = strdup(line);
	}

	return block;
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
		free_block(left);
		free_block(right);
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
		free_block(top);
		free_block(bottom);
	}
	return block;
}

Block *
concatv(Block *b1, Block *b2) {
	if(!b1) return b2;
	if(!b2) return b1;

	Block *block = malloc(sizeof(Block));
	block->width = max(b1->width, b2->width);
	block->height = b1->height + b2->height;
	block->lines = calloc(block->height, sizeof(char *));

	Block *top    = center(block->width, 0, b1);
	Block *bottom = center(block->width, 0, b2);

	for(int i = 0; i < block->height; i++) {
		if(i < top->height) {
			block->lines[i] = strdup(top->lines[i]);
		} else {
			block->lines[i] = strdup(bottom->lines[i - top->height]);
		}
	}

	//free_block(top);
	//free_block(bottom);

	return block;
}

Block *
concath(Block *b1, Block *b2) {
	if(!b1) return b2;
	if(!b2) return b1;

	if(b1->lines == NULL) {
		printf("1st block has no lines\n");
	}
	if(b2->lines == NULL) {
		printf("2nd block has no lines\n");
	}

	Block * block = malloc(sizeof(Block));
	if(b1->height != b2->height) {
		block->height = max(b1->height, b2->height);
		b1 = center(b1->width, block->height, b1);
		b2 = center(b2->width, block->height, b2);
	} else {
		block->height = b1->height;
	}
	block->width = b1->width + b2->width;

	// Concatenate each line
	block->lines = calloc(block->height, sizeof(char *));
	for(int i=0; i < b1->height; i++) {
		if(b1->lines[i] == NULL) {
			printf("Line %d is missing from block 1\nHeight is %d\n", i, b1->height);
		}
		if(b2->lines[i] == NULL) {
			printf("Line %d is missing from block 2\n", i);
		}
		block->lines[i] = calloc(strlen(b1->lines[i]) + strlen(b2->lines[i]) + 1, sizeof(char));
		block->lines[i] = strcpy(block->lines[i], b1->lines[i]);
		block->lines[i] = strcat(block->lines[i], b2->lines[i]);
	}
	return block;
}

Block *
stretch1h(int width, char *fill) {
	Block * block = malloc(sizeof(Block));
	block->height = 1;
	block->width = width;

	block->lines = calloc(1, sizeof(char *));
	block->lines[0] = calloc(strlen(fill)*width + 1, sizeof(char)) ;

	block->lines[0][0] = '\0';
	for(int i=0; i < width; i++) {
		block->lines[0] = strcat(block->lines[0], fill);
	}

	return block;
}

Block *
stretch3v(int height, char * start, char *fill, char *end) {
	Block * block = malloc(sizeof(Block));
	block->height = height;
	block->width = 1;
	block->lines = calloc(height, sizeof (char *));
	block->lines[0] = strdup(start);
	block->lines[height-1] = strdup(end);
	for(int i=1; i < height - 1; i++) {
		block->lines[i] = strdup(fill);
	}

	return block;
}

Block *
stretch4v(int height, char * start, char *fill, char *mid, char *end) {
	Block *block = stretch3v(height, start, fill, end);
	block->lines[height/2 + height%2] = mid;

	return block;
}

Block *
stretch5v(int height, char * start, char *fill, char *mid1, char *mid2, char *end) {
	Block *block = stretch3v(height, start, fill, end);
	block->lines[height/2] = mid1;
	block->lines[height/2 + height%2] = mid2;

	return block;
}

Block *
single(char *sym) {
	Block *block = malloc(sizeof(Block));
	block->width = 1;
	block->height = 1;
	block->lines = calloc(1, sizeof(char *));
	block->lines[0] = strdup(sym);
	return block;
}

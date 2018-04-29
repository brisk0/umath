#include "block_sym.h"

Block *
bracket(int height, const char *bracket) {
	Block *block;
	switch(bracket[0]) {
		case '(': block = oparen(height); break;
		case ')': block = cloparen(height); break;
		case '[': block = obracket(height); break;
		case ']': block = clobracket(height); break;
		case '{': block = obrace(height); break;
		case '}': block = clobrace(height); break;
	}
	return block;
}

Block *
oparen(int height) {
		if(height == 1) return single("(");
		return stretch3v(height, "⎛", "⎜", "⎝");
}


Block *
cloparen(int height) {
		if(height == 1) return single(")");
		return stretch3v(height, "⎞", "⎟", "⎠");
}

Block *
obracket(int height) {
		if(height == 1) return single("[");
		return stretch3v(height, "⎡", "⎢", "⎣");
}

Block *
clobracket(int height) {
		if(height == 1) return single("]");
		return stretch3v(height, "⎤", "⎥", "⎦");
}

Block *
obrace(int height) {
	if(height == 1) return single("{");
	if(height == 2) return concath(single("⎰"), single("⎱"));
	if(height % 2 == 0) {
		return stretch5v(height, "⎧", "⎪", "⎭", "⎫", "⎩");
	} else {
		return stretch4v(height, "⎧", "⎪", "⎨", "⎩");
	}
}

Block *
clobrace(int height) {
	if(height == 1) return single("}");
	if(height == 2) return concath(single("⎱"), single("⎰"));
	if(height % 2 == 0) {
		return stretch5v(height,"⎫", "⎪", "⎩", "⎧", "⎭");
	} else {
		return stretch4v(height, "⎫", "⎪", "⎬", "⎭");
	}
}

#include <stdlib.h>
#include <string.h>
#include "buffer.h"

void appendAbuf(Abuf *ab, const char *s, int len) {
	char *new = realloc(ab->b, ab->len + len);

	if(new == NULL) return;

	memcpy(&new[ab->len], s, len);
	ab->b = new;
	ab->len += len;
	
}

void freeAbuf(Abuf *ab){
	free(ab->b);
}

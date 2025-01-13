#ifndef _BUFFER
#define _BUFFER

#define ABUF_INIT {}

typedef struct abuf{
	int len;
	char* b;
}Abuf;

void appendAbuf(Abuf *, const char *, int);
void freeAbuf(Abuf *);

#endif

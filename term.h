#ifndef _TERM
#define _TERM

void enableRawMode(void);
void disableRawMode(void);
char editorReadKey(void);

int getWindowSize(int*, int*);

void die(char *);

#endif

#ifndef _TERMIOS
#define _TERMIOS
#include <termios.h>
#endif

struct editorConfig{
	int screenRow;
	int screenCol;
	struct termios orig_termios;
};

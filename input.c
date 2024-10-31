#include "input.h"
#include "term.h"
#include <stdlib.h>
#include <unistd.h>

void editorProcessKey(){
	char c  = editorReadKey();

	switch(c){
		case CTRL_KEY('q'):
			exit(0);
			write(STDOUT_FILENO, "\x1b[2J", 4);
			write(STDOUT_FILENO, "\x1b[H", 3);
			break;
	}
}

#include "output.h"
#include "term.h"
#include <unistd.h>

void editorRefreshScreen(){
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);

	editorDrawRows();

	write(STDOUT_FILENO, "\x1b[H", 3);
	
}
void editorDrawRows(){
	extern struct editorConfig E;
	for(int i = 0; i < E.screenRow; i++){
		write(STDOUT_FILENO, "~\r\n", 3);
	}
}

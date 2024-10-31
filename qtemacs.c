#include "term.h"
#include "input.h"
#include "output.h"

/*
  notas:
  parei em window size na mão de fallback
*/

void initEditor(){
	extern struct editorConfig E;
	if(getWindowSize( &E.screenRow, &E.screenCol) == -1)
		die("getWindowSize");
}

int main(int argc, char** argv){

	enableRawMode();
	initEditor();
	
	while(1){
		editorRefreshScreen();
		editorProcessKey();
	}
	
	return 0;
}

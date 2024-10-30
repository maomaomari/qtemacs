#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include "term.h"
#include "utils.h"
#include "input.h"

/*
  notas:
  parei em key factoring, cap III
*/

int main(int argc, char** argv){

	enableRawMode();
	
	char c;
	while(1){
		char c = '\0';
		if(read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
			die("read");
		
		if(iscntrl(c)){
			printf("%d\r\n", c);
		} else {
			printf("%d (%c)\r\n", c, c);
		}
		if(c == CTRL_KEY('q')) break;
	}
	

	return 0;
}

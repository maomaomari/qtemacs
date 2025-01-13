#include "output.h"
#include "term.h"
#include <stdio.h>
#include <unistd.h>
#include "buffer.h"
#include "version.h"

void editorRefreshScreen(){
	Abuf ab = ABUF_INIT;

	appendAbuf(&ab, "\x1b[?25l", 6);
	appendAbuf(&ab, "\x1b[H", 3);

	editorDrawRows(&ab);

	appendAbuf(&ab, "\x1b[H", 3);
	appendAbuf(&ab, "\x1b[?25h", 6);
	
	write(STDOUT_FILENO, ab.b, ab.len);
	freeAbuf(&ab);
	
}
void editorDrawRows(Abuf *ab){
	extern struct editorConfig E;
	for(int i = 0; i < E.screenRow; i++){
		if(i == E.screenRow / 3){
			char msg[80];
			int msglen = snprintf(msg, sizeof(msg),
								  "qtemacs version %s",
								  QTEMACS_VERSION
								  );
			if(msglen > E.screenCol)
				msglen = E.screenCol;
			int pad = (E.screenCol - msglen) / 2;
			if(pad){
				appendAbuf(ab, "~", 1);
				pad--;
			}
			while(pad--)
				appendAbuf(ab, " ", 1);
			appendAbuf(ab, msg, msglen);
		} else {
			appendAbuf(ab, "~", 1);
		}
		
		appendAbuf(ab, "\x1b[K", 3);
		if(i < E.screenRow -1){
		appendAbuf(ab, "\r\n", 2);
		}
	}
}

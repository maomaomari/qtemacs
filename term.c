#include "term.h"
#include <asm-generic/ioctls.h>
#include <errno.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <ctype.h>

struct editorConfig E;

void enableRawMode(){

	if(tcgetattr(STDIN_FILENO, &E.orig_termios) == -1) die("tcgetattr");
	atexit(disableRawMode);
	
	struct termios raw = E.orig_termios;

	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN  | ISIG);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

void disableRawMode(){
	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1)
		die("tcsetattr");
}
char editorReadKey(){
	int nread;
	char c;
	while((nread = read(STDIN_FILENO, &c, 1) != 1)){
		if(nread == -1 && errno != EAGAIN)
			die("read");
	}
	return c;
}

void die(char *s){
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
	perror(s);
	exit(1);
}

int getWindowSize(int *row, int *col){
	struct winsize w;
	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1 || w.ws_col == 0){
		if(write(STDOUT_FILENO,"\x1b[999C\x1b[999B", 12) != 12)
			return -1;
		return getCursorPosition(row, col);
	} else {
		*col = w.ws_col;
		*row = w.ws_row;
		return 0;
	}
}

int getCursorPosition(int *row, int *col){
	char buf[32];
	unsigned int i = 0;
	
	if(write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1;

	while(i < sizeof(buf) - 1){
		if(read(STDOUT_FILENO, &buf[i], 1) != 1)
			break;
		if(buf[i] == 'R')
			break;
		i++;
	}
	buf[i] = '\0';

	if(buf[0] != '\x1b' || buf[1] != '[')
		return -1;
	if(sscanf(&buf[2], "%d;%d", row, col) != 2)
		return -1;

	return 0;
}

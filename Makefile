CC = gcc
CFLAGS = -std=c2x

SRC = input.c output.c term.c qtemacs.c
OBJ = ${SRC:.c=.o}


all: qtemacs

.c.o:
	echo compilando $<
	$(CC) $(CFLAGS) -c $<

qtemacs: $(OBJ)
	echo lincando $(OBJ) em $@
	$(CC) -o $@ $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ) qtemacs

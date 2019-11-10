CC=gcc
CFLAGS=-Wall -ansi -pedantic -g -lm
DEP = text.h

all: a4
	$(CC) $(CFLAGS) -o a4 a4.o

a4: a4.c a4.h
	$(CC) $(CFLAGS) -c a4.c -o a4.o

clean:
	rm bin/*
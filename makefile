CC = gcc
CFLAGS = -ansi -Wall -pedantic

all: sustituir

sustituir: sustituir.o
	$(CC) $(CFLAGS) -o sustituir sustituir.o

sustituir.o:
	$(CC) $(CFLAGS) -c sustituir.c

clean:
	rm *.o sustituir
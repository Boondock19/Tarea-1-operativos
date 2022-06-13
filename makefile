CC = gcc
CFLAGS = -ansi -Wall -pedantic

all: main

main: main.o
	$(CC) $(CFLAGS) -o main main.o

main.o:
	$(CC) $(CFLAGS) -c main.c

clean:
	rm *.o main
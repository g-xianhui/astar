all: main

CC = gcc
CFLAGS = -g

main: astar.o test.o
	$(CC) $(CFLAGS) -o $@ $^

astar.o: astar.c
test.o: test.c

clean:
	rm -f *.o main core.*

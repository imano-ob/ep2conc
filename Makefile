CFLAGS = -fopenmp -lm -Wall
CC = gcc

ep: main.o fatorial.o
	$(CC) $(CFLAGS) -o $@ main.o fatorial.o

fatorial.o: fatorial.c fatorial.h
	$(CC) -c fatorial.c $(CFLAGS) -o $@

main.o: main.c	
	$(CC) -c main.c $(CFLAGS) -o $@

.PHONY: clean
clean:
	rm -vf *.o ep
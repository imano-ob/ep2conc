CFLAGS = -fopenmp -lm -Wall -lgmp -lgmpxx -g
CC = g++

ep: main.o fatorial.o
	$(CC) $(CFLAGS) -o $@ main.o fatorial.o

fatorial.o: fatorial.cc fatorial.h
	$(CC) -c fatorial.cc $(CFLAGS) -o $@

main.o: main.cc	
	$(CC) -c main.cc $(CFLAGS) -o $@

.PHONY: clean
clean:
	rm -vf *.o ep
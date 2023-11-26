CC=gcc
CFLAGS=-g -Wall -pg

all: KL

KL: Main.o KLGenerator.o Graph.o Heap.o Helper.o
	$(CC) $(CFLAGS) Main.o KLGenerator.o Graph.o Heap.o Helper.o -lm -pg -o KL 

Main.o: Main.c KLGenerator.h
	$(CC) $(CFLAGS) -c Main.c

KLGenerator.o: KLGenerator.c KLGenerator.h Graph.h Heap.h
	$(CC) $(CFLAGS) -c KLGenerator.c

Graph.o: Graph.c Graph.h Helper.h
	$(CC) $(CFLAGS) -c Graph.c

Heap.o: Heap.c Heap.h Helper.h
	$(CC) $(CFLAGS) -c Heap.c

Helper.o: Helper.c Helper.h
	$(CC) $(CFLAGS) -c Helper.c

clean:
	$(RM) KL *.o *~

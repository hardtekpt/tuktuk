#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -Wall -std=c99 -O3

#  Sources
SOURCES =  utils.c problem.c file.c heap.c main.c 

#  Objects
OBJECTS = utils.o problem.o file.o heap.o main.o 

tuktuk: $(OBJECTS)
	gcc -o $@ $(OBJECTS)

problem.o: problem.c problem.h

utils.o: utils.h utils.c

file.o: file.h file.c

heap.o: heap.c heap.h

clean::
	rm -f *.o core a.out tuktuk *~

# DO NOT DELETE

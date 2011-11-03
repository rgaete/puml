CC=g++
CFLAGS=-g -Wall

all: pUML

pUML: pUML.h pUML.cpp nodes.o diagrams.o utilities.o
	$(CC) $(CFLAGS) pUML.cpp nodes.o diagrams.o utilities.o -o pUML

nodes.o: constants.h nodes.h nodes.cpp
	$(CC) $(CFLAGS) -c nodes.cpp

diagrams.o: constants.h diagrams.h diagrams.cpp
	$(CC) $(CFLAGS) -c diagrams.cpp

utilities.o: constants.h utilities.h utilities.cpp
	$(CC) $(CFLAGS) -c utilities.cpp

clean:
	rm -rf *.o callgrind.out.* pUML

tar:
	tar -cvf pUML.tar nodes.cpp diagrams.cpp utilities.cpp pUML.cpp pUML.h makefile

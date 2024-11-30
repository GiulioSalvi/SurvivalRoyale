CC=gcc

CV=99
PLT=macos
CCFLAGS=-g -std=c$(CV)

all: clear vector ansi main

vector: src/vector.c
	$(CC) $(CCFLAGS) -c src/vector.c -o bin/objects/vector-c$(CV).o

ansi: src/ansi.c
	$(CC) $(CCFLAGS) -c src/ansi.c -o bin/objects/ansi-$(PLT)-c$(CV).o

main: src/main.c bin/objects/ansi-$(PLT)-c$(CV).o bin/objects/vector-c$(CV).o
	$(CC) $(CCFLAGS) src/main.c bin/objects/ansi-$(PLT)-c$(CV).o bin/objects/vector-c$(CV).o -o bin/exec/project

clear:
	rm bin/exec/project
	rm bin/objects/ansi-$(PLT)-c$(CV).o
	rm bin/objects/vector-c$(CV).o
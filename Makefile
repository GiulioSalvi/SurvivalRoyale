CC=gcc

CV=99
CCFLAGS=-g -std=c$(CV) -I./h/

all: clear config config_file utility vector ansi main
go: all
	./bin/exec/project

config: src/config.c
	$(CC) $(CCFLAGS) -c src/config.c -o bin/objects/config-c$(CV).o

config_file: src/config_file.c
	$(CC) $(CCFLAGS) -c src/config_file.c -o bin/objects/config-file-c$(CV).o

utility: src/utility.c
	$(CC) $(CCFLAGS) -c src/utility.c -o bin/objects/utility-c$(CV).o

vector: src/vector.c
	$(CC) $(CCFLAGS) -c src/vector.c -o bin/objects/vector-c$(CV).o

ansi: src/ansi.c
	$(CC) $(CCFLAGS) -c src/ansi.c -o bin/objects/ansi-c$(CV).o

main: src/main.c bin/objects/ansi-c$(CV).o bin/objects/vector-c$(CV).o bin/objects/utility-c$(CV).o bin/objects/config-c$(CV).o bin/objects/config-file-c$(CV).o
	$(CC) $(CCFLAGS) src/main.c bin/objects/ansi-c$(CV).o bin/objects/vector-c$(CV).o bin/objects/utility-c$(CV).o bin/objects/config-c$(CV).o bin/objects/config-file-c$(CV).o -o bin/exec/project

clear:
	rm bin/exec/project
	rm bin/objects/ansi-c$(CV).o
	rm bin/objects/vector-c$(CV).o
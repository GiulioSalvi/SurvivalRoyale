CV=99
CC=gcc
CCFLAGS=-g -std=c$(CV) -I./h/

# Rileva il sistema operativo
ifeq ($(OS), Windows_NT)
    EXE_EXT=.exe
    MKDIR=mkdir
    RM=del /Q
else
    EXE_EXT=
    MKDIR=mkdir -p
    RM=rm -rf
endif

all: cli config config_file utility vector ansi gui main

setup:
	$(MKDIR) bin
	$(MKDIR) bin/exec
	$(MKDIR) bin/objects

gen-docs:
	doxygen docs/Doxyfile

go: all
	./bin/exec/game$(EXE_EXT) --go --dont-ask-config-options

cli: src/cli.c
	$(CC) $(CCFLAGS) -c src/cli.c -o bin/objects/cli-c$(CV).o

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

gui: src/gui.c
	$(CC) $(CCFLAGS) -c src/gui.c -o bin/objects/gui-c$(CV).o

main: src/main.c bin/objects/ansi-c$(CV).o bin/objects/vector-c$(CV).o bin/objects/utility-c$(CV).o bin/objects/config-c$(CV).o bin/objects/config-file-c$(CV).o bin/objects/cli-c$(CV).o bin/objects/gui-c$(CV).o
	$(CC) $(CCFLAGS) src/main.c bin/objects/ansi-c$(CV).o bin/objects/vector-c$(CV).o bin/objects/utility-c$(CV).o bin/objects/config-c$(CV).o bin/objects/config-file-c$(CV).o bin/objects/cli-c$(CV).o bin/objects/gui-c$(CV).o -o bin/exec/game$(EXE_EXT) -lm

clean:
	$(RM) bin/objects/* bin/exec/game$(EXE_EXT)
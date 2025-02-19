CV=99
CC=gcc
CCFLAGS=-g -O2 -std=c$(CV) -I./h/

ifeq ($(OS), Windows_NT)
    EXE_EXT=.exe
endif

all: cli config config_file utility vector ansi tui log main

tests:
	@echo "Move into the 'test' folder. Then type 'make <test_name>' for compiling one of the available tests or type 'make all' to compile all the available tests."

setup:
	mkdir bin logs
	cd bin && mkdir exec objects

gen-docs:
	doxygen docs/Doxyfile

go: all
	./bin/exec/game$(EXE_EXT) --go --dont-ask-config-options --use-tui

go-verbose: all
	./bin/exec/game$(EXE_EXT) --go --dont-ask-config-options --use-tui --verbose

go-classic:	all
	./bin/exec/game$(EXE_EXT) --go --dont-ask-config-options

go-classic-verbose:
	./bin/exec/game$(EXE_EXT) --go --dont-ask-config-options --verbose

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

tui: src/tui.c
	$(CC) $(CCFLAGS) -c src/tui.c -o bin/objects/tui-c$(CV).o

log: src/logs.c
	$(CC) $(CCFLAGS) -c src/logs.c -o bin/objects/logs-c$(CV).o

main: src/main.c bin/objects/ansi-c$(CV).o bin/objects/vector-c$(CV).o bin/objects/utility-c$(CV).o bin/objects/config-c$(CV).o bin/objects/config-file-c$(CV).o bin/objects/cli-c$(CV).o bin/objects/tui-c$(CV).o bin/objects/logs-c$(CV).o
	$(CC) $(CCFLAGS) src/main.c bin/objects/ansi-c$(CV).o bin/objects/vector-c$(CV).o bin/objects/utility-c$(CV).o bin/objects/config-c$(CV).o bin/objects/config-file-c$(CV).o bin/objects/cli-c$(CV).o bin/objects/tui-c$(CV).o bin/objects/logs-c$(CV).o -o bin/exec/game$(EXE_EXT) -lm

CV=99
CC=gcc
CCFLAGS=-g -std=c$(CV)

ifeq ($(OS), Windows_NT)
    EXE_EXT=.exe
endif

all: log-test term-card-test term-card-colors-test term-card-colors-old-test

setup:
	mkdir exec

log-test:
	$(CC) $(CCFLAGS) fileLoggingTest.c -o ./exec/fileLoggingTest$(EXE_EXT)

term-card-test:
	$(CC) $(CCFLAGS) terminalCardTest.c -o ./exec/terminalCardTest$(EXE_EXT)

term-card-colors-test:
	$(CC) $(CCFLAGS) terminalCardTestColors.c -o ./exec/terminalCardTestColors$(EXE_EXT)

term-card-colors-old-test:
	$(CC) $(CCFLAGS) terminalCardTestColorsOld.c -o ./exec/terminalCardTestColorsOld$(EXE_EXT)
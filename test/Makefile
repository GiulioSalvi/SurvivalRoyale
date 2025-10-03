# Copyright (C) 2025  Giulio Salvi, Jacopo Paradisi
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

CV=99
CC=gcc
CCFLAGS=-g --std=c$(CV)

.PHONY: all setup term-card-test term-card-colors-test term-card-colors-old-test

ifeq ($(OS), Windows_NT)
    EXE_EXT=.exe
endif

all: term-card-test term-card-colors-test term-card-colors-old-test

setup:
	mkdir exec

term-card-test:
	$(CC) $(CCFLAGS) terminalCardTest.c -o ./exec/terminalCardTest$(EXE_EXT)

term-card-colors-test:
	$(CC) $(CCFLAGS) terminalCardTestColors.c -o ./exec/terminalCardTestColors$(EXE_EXT)

term-card-colors-old-test:
	$(CC) $(CCFLAGS) terminalCardTestColorsOld.c -o ./exec/terminalCardTestColorsOld$(EXE_EXT)

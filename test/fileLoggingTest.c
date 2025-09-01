// Copyright (C) 2025  Giulio Salvi, Jacopo Paradisi
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int randomInt(int min, int max);
char randomLetter();

int main(void) {
	srand(time(NULL));
	FILE* logFile = fopen("./exec/log.txt", "w");

	printf("Writing first data\n");
	char* buffer = (char*)calloc(256 + 1, sizeof(char));
	for(int i = 0; i < 256; i++)
		buffer[i] = randomLetter();

	fputs(buffer, logFile);
	fputs("\n", logFile);
	fclose(logFile);
	free(buffer);

	printf("\nWaiting...\n");
	sleep(5);

	logFile = fopen("./log.txt", "a+");

	printf("\nWriting second data\n");
	buffer = (char*)calloc(256 + 1, sizeof(char));
	for(int i = 0; i < 256; i++)
		buffer[i] = randomLetter();

	fputs(buffer, logFile);
	fputs("\n", logFile);
	fclose(logFile);
	free(buffer);	

	return 0;
}

int randomInt(int min, int max) {
	return rand()%(max - min + 1) + min;
}

char randomLetter() {
	return (char)randomInt('a', 'z');
}

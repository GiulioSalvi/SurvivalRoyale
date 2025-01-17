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

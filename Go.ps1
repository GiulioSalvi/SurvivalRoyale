Clear-Host

gcc -w -c src/ansi.c -o bin/objects/ansi-macos-c99.o -std=c99
gcc -w src/main.c bin/objects/ansi-macos-c99.o -o bin/exec/project -std=c99

./bin/exec/project

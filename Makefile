all:
	clang -O3 -lSDL *.c -o bin/test

debug:
	clang -g  -lSDL *.c -o bin/test

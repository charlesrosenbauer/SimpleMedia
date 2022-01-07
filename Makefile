all:
	clang -O3 -lSDL src/*.c -o bin/test

debug:
	clang -g  -lSDL src/*.c -o bin/test

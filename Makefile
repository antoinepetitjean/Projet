comet: main.c pentomino.h pentomino.c
	gcc -Wall -g -std=c99 main.c pentomino.c `sdl-config --cflags --libs` -lm -o penta

clean:
	rm -f penta

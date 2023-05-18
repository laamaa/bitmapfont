CC=gcc
CFLAGS=`pkg-config sdl2 SDL2_ttf --cflags --libs` -Wall -O2

bitmapfont: main.c
	$(CC) -o bitmapfont main.c $(CFLAGS)

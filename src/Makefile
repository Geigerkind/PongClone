CC=gcc
CFLAGS=-I"C:\SDL2_image\include" -I"C:\SDL2_ttf\include" -I"C:\SDL2\include"
LDFLAGS=-L"C:\SDL2_image\lib" -L"C:\SDL2_ttf\lib" -L"C:\SDL2\lib" -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lSDL2_ttf -lSDL2_image

# Hack to get main.c rebuilt
hack := $(shell touch main.c)

all: run

Pong.exe: main.c audio.o
	$(CC) $(CFLAGS) -o Pong.exe main.c audio.o $(LDFLAGS)

audio.o: audio.o
	$(CC) $(CFLAGS) -c audio.c $(LDFLAGS)

.PHONY: Pong.exe

run: Pong.exe
	Pong.exe


CC=g++
CFLAGS=-c -Wall
DEPENCE=-lSDL -lSDL_image -lSDL_ttf -lSDL_mixer

all: stroopColor

stroopColor : memory.o color_game.o button.o
		$(CC) -o stroopColor memory.o color_game.o button.o $(DEPENCE)

memory.o : memory.cpp memory.h
		$(CC) $(CFLAGS) memory.cpp

color_game.o : color_game.cpp
		$(CC) $(CFLAGS) color_game.cpp

button.o : button.cpp button.h
		$(CC) $(CFLAGS) button.cpp

clean :
		rm *.o stroopColor

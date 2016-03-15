main=src/main.cpp
files= src/Graphics.cpp src/Game.cpp src/Board.cpp
libs=-lSDL2 -lSDL2_ttf
inc=-I/usr/include/SDL2 -I./headers
CC=g++

all: $(file)
	$(CC) $(main) $(files) $(libs) $(inc)
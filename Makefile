main=src/main.cpp
files= src/Graphics.cpp src/Game.cpp
libs=-lSDL2 -lSDL2_image
inc=-I/usr/include/SDL2 -I./headers
CC=g++

all: $(file)
	$(CC) $(main) $(files) $(libs) $(inc)
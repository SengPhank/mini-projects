
CC = g++
CFLAGS = -std=c++17 -Iinclude -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

.PHONY = build run clean

SRCFILES = src/main.cpp src/mineSweeper.cpp src/gameWindow.cpp src/helper.cpp src/gridMouseTracker.cpp
HEADERFILES = include/constants.h include/mineSweeper.h include/gameWindow.h include/helper.h include/gridMouseTracker.h

build: 
	${CC} ${SRCFILES} $(CFLAGS)

run:	
	./a.out

clean:
	rm a.out


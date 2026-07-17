
CC = g++
CFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

.PHONY = build run clean

SRCFILES = main.cpp mineSweeper.cpp gameWindow.cpp helper.cpp gridMouseTracker.cpp
HEADERFILES = constants.h mineSweeper.h gameWindow.h helper.h gridMouseTracker.h

build: 
	${CC} ${SRCFILES} $(CFLAGS)

run:	
	./a.out

clean:
	rm a.out


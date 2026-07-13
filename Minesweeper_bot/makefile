
CC = g++
CFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

.PHONY = build run clean

SRCFILES = main.cpp minesweeper.cpp
HEADERFILES = minesweeper.h

build: 
	${CC} ${SRCFILES} $(CFLAGS)

run:	
	./a.out

clean:
	rm a.out


.POSIX:
.SUFFIXES:

CC = g++
SDL_CFLAGS = $(shell sdl2-config --cflags)
CFLAGS = -g -Wall -Wextra -pedantic $(SDL_CFLAGS)
SDL_LDFLAGS = $(shell sdl2-config --libs)
LDLIBS = $(SDL_LDFLAGS) -lSDL2_image

all: asteroids
asteroids: asteroids.o
	$(CC) $(LDFLAGS) -o asteroids asteroids.o $(LDLIBS)
asteroids.o: asteroids.cpp
clean:
	rm -f asteroids asteroids.o

.SUFFIXES: .cpp .o
.cpp.o:
	$(CC) $(CFLAGS) -c $<

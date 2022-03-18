.POSIX:
.SUFFIXES:

CC = g++
SDL_CFLAGS = $(shell sdl2-config --cflags)
CFLAGS = -g -Og -Wall -Wextra -pedantic $(SDL_CFLAGS)
SDL_LDFLAGS = $(shell sdl2-config --libs)
LDLIBS = $(SDL_LDFLAGS) -lSDL2_image

all: asteroids
asteroids: asteroids.o handle_input.o utility.o
	$(CC) $(LDFLAGS) -o asteroids asteroids.o handle_input.o utility.o $(LDLIBS)
asteroids.o: asteroids.cpp handle_input.h SDL_Exception.h utility.h
handle_input.o: handle_input.cpp handle_input.h
utility.o: utility.cpp utility.h SDL_Exception.h
clean:
	rm -f asteroids *.o

.SUFFIXES: .cpp .o
.cpp.o:
	$(CC) $(CFLAGS) -c $<

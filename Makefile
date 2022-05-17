.POSIX:
.SUFFIXES:

CC = g++
OPT = -g -Og
SDL_CFLAGS = $(shell sdl2-config --cflags)
CFLAGS = $(OPT) -Wall -Wextra -Weffc++ -Wsign-conversion -pedantic -std=c++17 $(SDL_CFLAGS)
SDL_LDFLAGS = $(shell sdl2-config --libs)
LDLIBS = $(SDL_LDFLAGS) -lSDL2_image

all: asteroids
asteroids: obj/asteroids.o obj/utility.o obj/GameLoop.o obj/Entity.o obj/Vec2d.o
	$(CC) $(LDFLAGS) -o asteroids obj/asteroids.o obj/utility.o obj/GameLoop.o obj/Entity.o obj/Vec2d.o $(LDLIBS)
obj/asteroids.o: src/asteroids.cpp inc/Colors.hpp inc/KeyFlag.hpp inc/Entity.hpp inc/GameLoop.hpp inc/utility.hpp inc/Vec2d.hpp
	$(CC) $(CFLAGS) -o obj/asteroids.o -c src/asteroids.cpp
obj/utility.o: src/utility.cpp inc/utility.hpp inc/Entity.hpp
	$(CC) $(CFLAGS) -o obj/utility.o -c src/utility.cpp
obj/GameLoop.o: src/GameLoop.cpp inc/GameLoop.hpp inc/KeyFlag.hpp inc/Entity.hpp
	$(CC) $(CFLAGS) -o obj/GameLoop.o -c src/GameLoop.cpp
obj/Entity.o: src/Entity.cpp inc/Entity.hpp inc/KeyFlag.hpp inc/utility.hpp inc/Vec2d.hpp
	$(CC) $(CFLAGS) -o obj/Entity.o -c src/Entity.cpp
obj/Vec2d.o: src/Vec2d.cpp inc/Vec2d.hpp
	$(CC) $(CFLAGS) -o obj/Vec2d.o -c src/Vec2d.cpp
clean:
	rm -f asteroids obj/*.o

.SUFFIXES: .cpp .o
.cpp.o:
	$(CC) $(CFLAGS) -c $<

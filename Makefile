.POSIX:
.SUFFIXES:

CC = g++
OPT = -g -Og
SDL_CFLAGS = $(shell sdl2-config --cflags)
CFLAGS = $(OPT) -Wall -Wextra -Weffc++ -Wsign-conversion -pedantic -std=c++17
SDL_LDFLAGS = $(shell sdl2-config --libs)
LDLIBS = -lSDL2_image

all: asteroids
tool: fps-analysis.cpp
	$(CC) $(CFLAGS) -o fps-analysis fps-analysis.cpp
asteroids: obj/asteroids.o obj/Engine.o obj/Entity.o obj/GameLoop.o obj/Gun.o obj/Hyperdrive.o obj/PhysicsComponent.o obj/Player.o obj/Ship.o obj/utility.o obj/Vec2d.o
	$(CC) $(LDFLAGS) -o asteroids obj/asteroids.o obj/Engine.o obj/Entity.o obj/GameLoop.o obj/Gun.o obj/Hyperdrive.o obj/PhysicsComponent.o obj/Player.o obj/Ship.o obj/utility.o obj/Vec2d.o $(SDL_LDFLAGS) $(LDLIBS)
obj/asteroids.o: src/asteroids.cpp inc/Colors.hpp inc/KeyFlag.hpp inc/Entity.hpp inc/GameLoop.hpp inc/PhysicsComponent.hpp inc/Player.hpp inc/utility.hpp inc/Vec2d.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/asteroids.o -c src/asteroids.cpp
obj/Engine.o: src/Engine.cpp inc/Engine.hpp inc/Ship.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/Engine.o -c src/Engine.cpp
obj/Entity.o: src/Entity.cpp inc/Entity.hpp inc/Colors.hpp inc/KeyFlag.hpp inc/GameWorld.hpp inc/utility.hpp inc/Vec2d.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/Entity.o -c src/Entity.cpp
obj/GameLoop.o: src/GameLoop.cpp inc/GameLoop.hpp inc/KeyFlag.hpp inc/Entity.hpp inc/PhysicsComponent.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/GameLoop.o -c src/GameLoop.cpp
obj/Gun.o: src/Gun.cpp inc/Gun.hpp inc/Gun.hpp inc/Ship.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/Gun.o -c src/Gun.cpp
obj/Hyperdrive.o: src/Hyperdrive.cpp inc/Hyperdrive.hpp inc/Player.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/Hyperdrive.o -c src/Hyperdrive.cpp
obj/PhysicsComponent.o: src/PhysicsComponent.cpp inc/PhysicsComponent.hpp inc/Box.hpp inc/Entity.hpp inc/Vec2d.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/PhysicsComponent.o -c src/PhysicsComponent.cpp
obj/Player.o: src/Player.cpp inc/Player.hpp inc/GameWorld.hpp inc/Hyperdrive.hpp inc/PhysicsComponent.hpp inc/Ship.hpp inc/Vec2d.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/Player.o -c src/Player.cpp
obj/Ship.o: src/Ship.cpp inc/Ship.hpp inc/Engine.hpp inc/GameWorld.hpp inc/Gun.hpp inc/PhysicsComponent.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/Ship.o -c src/Ship.cpp
obj/utility.o: src/utility.cpp inc/utility.hpp inc/Colors.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/utility.o -c src/utility.cpp
obj/Vec2d.o: src/Vec2d.cpp inc/Vec2d.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/Vec2d.o -c src/Vec2d.cpp
clean:
	rm -f asteroids obj/*.o

.SUFFIXES: .cpp .o
.cpp.o:
	$(CC) $(CFLAGS) $(SDL_CFLAGS)-c $<

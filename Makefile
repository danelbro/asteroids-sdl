.POSIX:
.SUFFIXES:

CC = g++
OPT = -g
SDL_CFLAGS = $(shell sdl2-config --cflags)
CFLAGS = $(OPT) -Wall -Wextra -Weffc++ -Wsign-conversion -pedantic -std=c++17
SDL_LDFLAGS = $(shell sdl2-config --libs)
LDLIBS = -lSDL2_ttf
OBJ = obj/asteroids.o obj/AIComponent.o obj/Asteroid.o obj/Bullet.o obj/Engine.o obj/Entity.o obj/EntityManager.o obj/GameLoop.o obj/Gun.o obj/Hyperdrive.o obj/PhysicsComponent.o obj/PhysicsEntity.o obj/PhysicsManager.o obj/Player.o obj/ScoreManager.o obj/Ship.o obj/TextObject.o obj/utility.o obj/Vec2d.o obj/VectorDraw.o

all: asteroids
asteroids: $(OBJ)
	$(CC) $(LDFLAGS) -o asteroids $(OBJ) $(SDL_LDFLAGS) $(LDLIBS)
obj/asteroids.o: src/asteroids.cpp inc/Asteroid.hpp inc/Colors.hpp inc/Entity.hpp inc/EntityManager.hpp inc/PhysicsManager.hpp inc/FlagEnums.hpp inc/GameLoop.hpp inc/GameWorld.hpp inc/PhysicsComponent.hpp inc/Player.hpp inc/ScoreManager.hpp inc/utility.hpp inc/Vec2d.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/asteroids.o -c src/asteroids.cpp
obj/AIComponent.o: inc/AIComponent.hpp src/AIComponent.cpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/AIComponent.o -c src/AIComponent.cpp
obj/Asteroid.o: src/Asteroid.cpp inc/Asteroid.hpp inc/Colors.hpp inc/FlagEnums.hpp inc/GameWorld.hpp inc/PhysicsComponent.hpp inc/PhysicsEntity.hpp inc/Vec2d.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/Asteroid.o -c src/Asteroid.cpp
obj/Bullet.o: src/Bullet.cpp inc/Bullet.hpp inc/FlagEnums.hpp inc/GameWorld.hpp inc/PhysicsComponent.hpp inc/PhysicsEntity.hpp inc/Ship.hpp inc/Vec2d.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/Bullet.o -c src/Bullet.cpp
obj/Engine.o: src/Engine.cpp inc/Engine.hpp inc/Ship.hpp inc/PhysicsComponent.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/Engine.o -c src/Engine.cpp
obj/Entity.o: src/Entity.cpp inc/Entity.hpp inc/Colors.hpp inc/FlagEnums.hpp inc/GameWorld.hpp inc/VectorDraw.hpp inc/Vec2d.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/Entity.o -c src/Entity.cpp
obj/EntityManager.o: src/EntityManager.cpp inc/EntityManager.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/EntityManager.o -c src/EntityManager.cpp
obj/GameLoop.o: src/GameLoop.cpp inc/GameLoop.hpp inc/FlagEnums.hpp inc/Entity.hpp inc/EntityManager.hpp inc/GameWorld.hpp inc/PhysicsComponent.hpp inc/PhysicsManager.hpp inc/Player.hpp inc/ScoreManager.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/GameLoop.o -c src/GameLoop.cpp
obj/Gun.o: src/Gun.cpp inc/Gun.hpp inc/EntityManager.hpp inc/GameWorld.hpp inc/PhysicsComponent.hpp inc/PhysicsManager.hpp inc/Ship.hpp inc/Vec2d.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/Gun.o -c src/Gun.cpp
obj/Hyperdrive.o: src/Hyperdrive.cpp inc/Hyperdrive.hpp inc/Player.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/Hyperdrive.o -c src/Hyperdrive.cpp
obj/PhysicsComponent.o: src/PhysicsComponent.cpp inc/PhysicsComponent.hpp inc/Box.hpp inc/GameWorld.hpp inc/Entity.hpp inc/Vec2d.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/PhysicsComponent.o -c src/PhysicsComponent.cpp
obj/PhysicsEntity.o: src/PhysicsEntity.cpp inc/PhysicsEntity.hpp inc/Entity.hpp inc/FlagEnums.hpp inc/GameWorld.hpp inc/GameWorld.hpp inc/PhysicsComponent.hpp inc/Vec2d.hpp inc/VectorDraw.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/PhysicsEntity.o -c src/PhysicsEntity.cpp
obj/PhysicsManager.o: src/PhysicsManager.cpp inc/PhysicsManager.hpp inc/Asteroid.hpp inc/Bullet.hpp inc/Enemy.hpp inc/Entity.hpp inc/FlagEnums.hpp inc/GameWorld.hpp inc/PhysicsComponent.hpp inc/Player.hpp inc/ScoreManager.hpp inc/Ship.hpp inc/Vec2d.hpp inc/VectorDraw.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/PhysicsManager.o -c src/PhysicsManager.cpp
obj/Player.o: src/Player.cpp inc/Player.hpp inc/Colors.hpp inc/FlagEnums.hpp inc/GameWorld.hpp inc/Hyperdrive.hpp inc/PhysicsComponent.hpp inc/Ship.hpp inc/Vec2d.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/Player.o -c src/Player.cpp
obj/ScoreManager.o: src/ScoreManager.cpp inc/ScoreManager.hpp inc/Colors.hpp inc/GameWorld.hpp inc/TextObject.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/ScoreManager.o -c src/ScoreManager.cpp
obj/Ship.o: src/Ship.cpp inc/Ship.hpp inc/Colors.hpp inc/Engine.hpp inc/FlagEnums.hpp inc/GameWorld.hpp inc/Gun.hpp inc/PhysicsComponent.hpp inc/PhysicsEntity.hpp inc/Vec2d.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/Ship.o -c src/Ship.cpp
obj/TextObject.o: src/TextObject.cpp inc/TextObject.hpp inc/Entity.hpp inc/FlagEnums.hpp inc/GameWorld.hpp inc/utility.hpp inc/Vec2d.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/TextObject.o -c src/TextObject.cpp
obj/utility.o: src/utility.cpp inc/utility.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/utility.o -c src/utility.cpp
obj/Vec2d.o: src/Vec2d.cpp inc/Vec2d.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/Vec2d.o -c src/Vec2d.cpp
obj/VectorDraw.o: src/VectorDraw.cpp inc/VectorDraw.hpp inc/Box.hpp inc/Colors.hpp inc/GameWorld.hpp inc/Vec2d.hpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o obj/VectorDraw.o -c src/VectorDraw.cpp
clean:
	rm -f asteroids obj/*.o

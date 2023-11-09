.POSIX:
.SUFFIXES:

CC = g++
CFLAGS = -Wall -Wextra -Wsign-conversion -pedantic -std=c++17 -Weffc++
INC_DIRS = -iquote inc/

## ’Release’ mode
MODE_FLAGS = -O2
SDL_CFLAGS = -Idep/linux_64/SDL2/include/SDL2 -D_REENTRANT -Idep/linux_64/SDL2_ttf/include/SDL2
SDL_LDFLAGS = -Wl,-rpath,dep/linux_64/SDL2/lib -Wl,--enable-new-dtags -lSDL2 -Ldep/linux_64/SDL2_ttf/lib/ -lSDL2_ttf

## ’Debug’ mode
# MODE_FLAGS = -Og -g -D_DEBUG
# SDL_CFLAGS = -Idep/linux_64/SDL2_d/include/SDL2 -D_REENTRANT -Idep/linux_64/SDL2_ttf_d/include/SDL2
# SDL_LDFLAGS = -Wl,-rpath,dep/linux_64/SDL2_d/lib -Wl,--enable-new-dtags -lSDL2 -Ldep/linux_64/SDL2_ttf_d/lib/ -lSDL2_ttf

OBJ = obj/AIComponent.o obj/Asteroid.o obj/AsteroidsApp.o obj/asteroids.o obj/Bullet.o obj/Enemy.o obj/Engine.o obj/GameOver.o obj/Gun.o obj/Hyperdrive.o obj/MainLevel.o obj/PhysicsComponent.o obj/PhysicsEntity.o obj/PhysicsManager.o obj/Player.o obj/ScoreManager.o obj/Ship.o obj/StageManager.o obj/TextObject.o obj/TitleScreen.o obj/utility.o obj/ValtrAlgorithm.o obj/Vec2d.o obj/VectorDraw.o

all: asteroids
release: asteroids
asteroids: $(OBJ)
	$(CC) $(INC_DIRS) $(LDFLAGS) $(MODE_FLAGS) -o asteroids $(OBJ) $(SDL_LDFLAGS)
debug: $(OBJ)
	$(CC) $(INC_DIRS) $(LDFLAGS) $(MODE_FLAGS) -o asteroids_debug $(OBJ) $(SDL_LDFLAGS)
obj/asteroids.o: src/asteroids.cpp inc/Box.hpp inc/Colors.hpp inc/StageManager.hpp inc/TitleScreen.hpp inc/utility.hpp inc/Vec2d.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/asteroids.o -c src/asteroids.cpp
obj/AIComponent.o: inc/AIComponent.hpp src/AIComponent.cpp inc/Enemy.hpp inc/Player.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/AIComponent.o -c src/AIComponent.cpp
obj/Asteroid.o: src/Asteroid.cpp inc/Asteroid.hpp inc/Colors.hpp inc/GameWorld.hpp inc/PhysicsComponent.hpp inc/PhysicsEntity.hpp inc/Vec2d.hpp inc/utility.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/Asteroid.o -c src/Asteroid.cpp
obj/AsteroidsApp.o: src/AsteroidsApp.cpp inc/AsteroidsApp.hpp inc/Application.hpp inc/Box.hpp inc/StageManager.hpp inc/TitleScreen.hpp inc/utility.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/AsteroidsApp.o -c src/AsteroidsApp.cpp
obj/Bullet.o: src/Bullet.cpp inc/Bullet.hpp inc/GameWorld.hpp inc/PhysicsComponent.hpp inc/PhysicsEntity.hpp inc/Ship.hpp inc/Vec2d.hpp inc/utility.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/Bullet.o -c src/Bullet.cpp
obj/Enemy.o: src/Enemy.cpp inc/Enemy.hpp inc/AIComponent.hpp inc/Colors.hpp inc/GameWorld.hpp inc/Ship.hpp inc/PhysicsComponent.hpp inc/Vec2d.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/Enemy.o -c src/Enemy.cpp
obj/Engine.o: src/Engine.cpp inc/Engine.hpp inc/Ship.hpp inc/PhysicsComponent.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/Engine.o -c src/Engine.cpp
obj/GameOver.o: src/GameOver.cpp inc/GameOver.hpp inc/GameWorld.hpp inc/PhysicsManager.hpp inc/Stage.hpp inc/TextObject.hpp inc/utility.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/GameOver.o -c src/GameOver.cpp
obj/Gun.o: src/Gun.cpp inc/Gun.hpp inc/PhysicsComponent.hpp inc/PhysicsManager.hpp inc/Ship.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/Gun.o -c src/Gun.cpp
obj/Hyperdrive.o: src/Hyperdrive.cpp inc/Hyperdrive.hpp inc/PhysicsComponent.hpp inc/Player.hpp inc/utility.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/Hyperdrive.o -c src/Hyperdrive.cpp
obj/MainLevel.o: src/MainLevel.cpp inc/MainLevel.hpp inc/Box.hpp inc/GameWorld.hpp inc/ScoreManager.hpp inc/Stage.hpp inc/StageManager.hpp inc/PhysicsEntity.hpp inc/PhysicsManager.hpp inc/Player.hpp inc/utility.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/MainLevel.o -c src/MainLevel.cpp
obj/PhysicsComponent.o: src/PhysicsComponent.cpp inc/PhysicsComponent.hpp inc/Box.hpp inc/GameWorld.hpp inc/PhysicsEntity.hpp inc/Vec2d.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/PhysicsComponent.o -c src/PhysicsComponent.cpp
obj/PhysicsEntity.o: src/PhysicsEntity.cpp inc/PhysicsEntity.hpp inc/Colors.hpp inc/Entity.hpp inc/GameWorld.hpp inc/PhysicsComponent.hpp inc/Vec2d.hpp inc/VectorDraw.hpp inc/utility.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/PhysicsEntity.o -c src/PhysicsEntity.cpp
obj/PhysicsManager.o: src/PhysicsManager.cpp inc/PhysicsManager.hpp inc/Asteroid.hpp inc/Bullet.hpp inc/Enemy.hpp inc/Entity.hpp inc/GameWorld.hpp inc/PhysicsComponent.hpp inc/Player.hpp inc/ScoreManager.hpp inc/Ship.hpp inc/Vec2d.hpp inc/VectorDraw.hpp inc/utility.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/PhysicsManager.o -c src/PhysicsManager.cpp
obj/Player.o: src/Player.cpp inc/Player.hpp inc/Colors.hpp inc/GameWorld.hpp inc/Hyperdrive.hpp inc/PhysicsComponent.hpp inc/Ship.hpp inc/Vec2d.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/Player.o -c src/Player.cpp
obj/ScoreManager.o: src/ScoreManager.cpp inc/ScoreManager.hpp inc/Colors.hpp inc/GameWorld.hpp inc/TextObject.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/ScoreManager.o -c src/ScoreManager.cpp
obj/Ship.o: src/Ship.cpp inc/Ship.hpp inc/Colors.hpp inc/Engine.hpp inc/GameWorld.hpp inc/Gun.hpp inc/PhysicsEntity.hpp inc/Vec2d.hpp inc/utility.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/Ship.o -c src/Ship.cpp
obj/StageManager.o: src/StageManager.cpp inc/StageManager.hpp inc/GameOver.hpp inc/MainLevel.hpp inc/Stage.hpp inc/TitleScreen.hpp inc/utility.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/StageManager.o -c src/StageManager.cpp
obj/TextObject.o: src/TextObject.cpp inc/TextObject.hpp inc/Colors.hpp inc/Entity.hpp inc/GameWorld.hpp inc/utility.hpp inc/Vec2d.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/TextObject.o -c src/TextObject.cpp
obj/TitleScreen.o: src/TitleScreen.cpp inc/TitleScreen.hpp inc/Box.hpp inc/GameWorld.hpp inc/Stage.hpp inc/TextObject.hpp inc/utility.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/TitleScreen.o -c src/TitleScreen.cpp
obj/utility.o: src/utility.cpp inc/utility.hpp inc/GameWorld.hpp inc/Vec2d.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/utility.o -c src/utility.cpp
obj/ValtrAlgorithm.o: src/ValtrAlgorithm.cpp inc/ValtrAlgorithm.hpp inc/Vec2d.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/ValtrAlgorithm.o -c src/ValtrAlgorithm.cpp
obj/Vec2d.o: src/Vec2d.cpp inc/Vec2d.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/Vec2d.o -c src/Vec2d.cpp
obj/VectorDraw.o: src/VectorDraw.cpp inc/VectorDraw.hpp inc/Box.hpp inc/Colors.hpp inc/GameWorld.hpp inc/Vec2d.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/VectorDraw.o -c src/VectorDraw.cpp
clean:
	rm -f asteroids asteroids_debug exception.log fps.log obj/*.o
clean_release:
	rm -f asteroids obj/*.o
clean_debug:
	rm -f asteroids_debug exception.log fps.log obj/*.o

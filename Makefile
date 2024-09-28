.POSIX:
.SUFFIXES:

CC = g++
CFLAGS = -Wall -Wextra -Wsign-conversion -pedantic -std=c++17 -Weffc++

## ’Release’ mode
MODE_FLAGS = -O2
SDL_CFLAGS = -Idep/linux_64/SDL2/include/SDL2 -D_REENTRANT -Idep/linux_64/SDL2_ttf/include/SDL2
SDL_LDFLAGS = -Wl,-rpath,dep/linux_64/SDL2/lib -Wl,--enable-new-dtags -lSDL2 -Ldep/linux_64/SDL2_ttf/lib/ -lSDL2_ttf

## ’Debug’ mode
# MODE_FLAGS = -Og -g -D_DEBUG
# SDL_CFLAGS = -Idep/linux_64/SDL2_d/include/SDL2 -D_REENTRANT -Idep/linux_64/SDL2_ttf_d/include/SDL2
# SDL_LDFLAGS = -Wl,-rpath,dep/linux_64/SDL2_d/lib -Wl,--enable-new-dtags -lSDL2 -Ldep/linux_64/SDL2_ttf_d/lib/ -lSDL2_ttf

OBJ = obj/AIComponent.o obj/Asteroid.o obj/AsteroidsApp.o obj/asteroids.o obj/Bullet.o obj/Enemy.o obj/Engine.o obj/GameOver.o obj/Gun.o obj/Hyperdrive.o obj/MainLevel.o obj/PhysicsComponent.o obj/PhysicsEntity.o obj/PhysicsManager.o obj/Player.o obj/SDL_Interface.o obj/ScoreManager.o obj/Ship.o obj/StageManager.o obj/TextObject.o obj/TitleScreen.o obj/utility.o obj/ValtrAlgorithm.o obj/Vec2d.o obj/VectorDraw.o

all: asteroids
release: asteroids
asteroids: $(OBJ)
	$(CC) $(INC_DIRS) $(LDFLAGS) $(MODE_FLAGS) -o asteroids $(OBJ) $(SDL_LDFLAGS)
debug: $(OBJ)
	$(CC) $(INC_DIRS) $(LDFLAGS) $(MODE_FLAGS) -o asteroids_debug $(OBJ) $(SDL_LDFLAGS)
obj/asteroids.o: src/asteroids.cpp src/Box.hpp src/Colors.hpp src/StageManager.hpp src/TitleScreen.hpp src/utility.hpp src/Vec2d.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/asteroids.o -c src/asteroids.cpp
obj/AIComponent.o: src/AIComponent.hpp src/AIComponent.cpp src/Enemy.hpp src/Player.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/AIComponent.o -c src/AIComponent.cpp
obj/Asteroid.o: src/Asteroid.cpp src/Asteroid.hpp src/Colors.hpp src/GameWorld.hpp src/PhysicsComponent.hpp src/PhysicsEntity.hpp src/Vec2d.hpp src/utility.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/Asteroid.o -c src/Asteroid.cpp
obj/AsteroidsApp.o: src/AsteroidsApp.cpp src/AsteroidsApp.hpp src/Application.hpp src/Box.hpp src/StageManager.hpp src/TitleScreen.hpp src/utility.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/AsteroidsApp.o -c src/AsteroidsApp.cpp
obj/Bullet.o: src/Bullet.cpp src/Bullet.hpp src/GameWorld.hpp src/PhysicsComponent.hpp src/PhysicsEntity.hpp src/Ship.hpp src/Vec2d.hpp src/utility.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/Bullet.o -c src/Bullet.cpp
obj/Enemy.o: src/Enemy.cpp src/Enemy.hpp src/AIComponent.hpp src/Colors.hpp src/GameWorld.hpp src/Ship.hpp src/PhysicsComponent.hpp src/Vec2d.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/Enemy.o -c src/Enemy.cpp
obj/Engine.o: src/Engine.cpp src/Engine.hpp src/Ship.hpp src/PhysicsComponent.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/Engine.o -c src/Engine.cpp
obj/GameOver.o: src/GameOver.cpp src/GameOver.hpp src/GameWorld.hpp src/PhysicsManager.hpp src/Stage.hpp src/TextObject.hpp src/utility.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/GameOver.o -c src/GameOver.cpp
obj/Gun.o: src/Gun.cpp src/Gun.hpp src/PhysicsComponent.hpp src/PhysicsManager.hpp src/Ship.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/Gun.o -c src/Gun.cpp
obj/Hyperdrive.o: src/Hyperdrive.cpp src/Hyperdrive.hpp src/PhysicsComponent.hpp src/Player.hpp src/utility.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/Hyperdrive.o -c src/Hyperdrive.cpp
obj/MainLevel.o: src/MainLevel.cpp src/MainLevel.hpp src/Box.hpp src/GameWorld.hpp src/ScoreManager.hpp src/Stage.hpp src/StageManager.hpp src/PhysicsEntity.hpp src/PhysicsManager.hpp src/Player.hpp src/utility.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/MainLevel.o -c src/MainLevel.cpp
obj/PhysicsComponent.o: src/PhysicsComponent.cpp src/PhysicsComponent.hpp src/Box.hpp src/GameWorld.hpp src/PhysicsEntity.hpp src/Vec2d.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/PhysicsComponent.o -c src/PhysicsComponent.cpp
obj/PhysicsEntity.o: src/PhysicsEntity.cpp src/PhysicsEntity.hpp src/Colors.hpp src/Entity.hpp src/GameWorld.hpp src/PhysicsComponent.hpp src/Vec2d.hpp src/VectorDraw.hpp src/utility.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/PhysicsEntity.o -c src/PhysicsEntity.cpp
obj/PhysicsManager.o: src/PhysicsManager.cpp src/PhysicsManager.hpp src/Asteroid.hpp src/Bullet.hpp src/Enemy.hpp src/Entity.hpp src/GameWorld.hpp src/PhysicsComponent.hpp src/Player.hpp src/ScoreManager.hpp src/Ship.hpp src/Vec2d.hpp src/VectorDraw.hpp src/utility.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/PhysicsManager.o -c src/PhysicsManager.cpp
obj/Player.o: src/Player.cpp src/Player.hpp src/Colors.hpp src/GameWorld.hpp src/Hyperdrive.hpp src/PhysicsComponent.hpp src/Ship.hpp src/Vec2d.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/Player.o -c src/Player.cpp
obj/SDL_Interface.o: src/SDL_Interface.cpp src/SDL_Interface.hpp src/GameWorld.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/SDL_Interface.o -c src/SDL_Interface.cpp
obj/ScoreManager.o: src/ScoreManager.cpp src/ScoreManager.hpp src/Colors.hpp src/GameWorld.hpp src/TextObject.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/ScoreManager.o -c src/ScoreManager.cpp
obj/Ship.o: src/Ship.cpp src/Ship.hpp src/Colors.hpp src/Engine.hpp src/GameWorld.hpp src/Gun.hpp src/PhysicsEntity.hpp src/Vec2d.hpp src/utility.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/Ship.o -c src/Ship.cpp
obj/StageManager.o: src/StageManager.cpp src/StageManager.hpp src/GameOver.hpp src/MainLevel.hpp src/Stage.hpp src/TitleScreen.hpp src/utility.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/StageManager.o -c src/StageManager.cpp
obj/TextObject.o: src/TextObject.cpp src/TextObject.hpp src/Colors.hpp src/Entity.hpp src/GameWorld.hpp src/utility.hpp src/Vec2d.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/TextObject.o -c src/TextObject.cpp
obj/TitleScreen.o: src/TitleScreen.cpp src/TitleScreen.hpp src/Box.hpp src/GameWorld.hpp src/Stage.hpp src/TextObject.hpp src/utility.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/TitleScreen.o -c src/TitleScreen.cpp
obj/utility.o: src/utility.cpp src/utility.hpp src/GameWorld.hpp src/Vec2d.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/utility.o -c src/utility.cpp
obj/ValtrAlgorithm.o: src/ValtrAlgorithm.cpp src/ValtrAlgorithm.hpp src/Vec2d.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/ValtrAlgorithm.o -c src/ValtrAlgorithm.cpp
obj/Vec2d.o: src/Vec2d.cpp src/Vec2d.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/Vec2d.o -c src/Vec2d.cpp
obj/VectorDraw.o: src/VectorDraw.cpp src/VectorDraw.hpp src/Box.hpp src/Colors.hpp src/GameWorld.hpp src/Vec2d.hpp
	$(CC) $(INC_DIRS) $(MODE_FLAGS) $(CFLAGS) $(SDL_CFLAGS) -o obj/VectorDraw.o -c src/VectorDraw.cpp
clean:
	rm -f asteroids asteroids_debug exception.log fps.log obj/*.o
clean_release:
	rm -f asteroids obj/*.o
clean_debug:
	rm -f asteroids_debug exception.log fps.log obj/*.o

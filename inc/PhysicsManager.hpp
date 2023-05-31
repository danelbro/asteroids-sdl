#pragma once

#pragma once

// PhysicsManager class to create, store and destroy instances of PhysicsEntity

#include <memory>
#include <random>
#include <vector>

#include <SDL.h>

#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Entity.hpp"
#include "GameWorld.hpp"
#include "PhysicsComponent.hpp"
#include "Player.hpp"
#include "Vec2d.hpp"

class PhysicsManager {
public:
	PhysicsManager();

	void make_bullet(GameWorld* new_GameWorld, Vec2d origin,
		double power, double angle, Ship* new_owner);

	void make_asteroid(GameWorld* new_GameWorld, double scale,
		std::mt19937& rng);

	void make_asteroids(GameWorld* new_GameWorld, int num,
		double scale, std::mt19937& rng);

	void make_enemy();

	std::shared_ptr<Player> make_player(GameWorld* new_GameWorld);

	void clean_up();

	std::vector<std::shared_ptr<Entity>> physEntities;
	std::vector<std::unique_ptr<PhysicsComponent>> physMan;
};
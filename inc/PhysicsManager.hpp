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
#include "ScoreManager.hpp"
#include "Ship.hpp"
#include "Vec2d.hpp"
#include "VectorDraw.hpp"

class PhysicsManager {
public:
	PhysicsManager();

	void make_bullet(GameWorld& new_GameWorld, Vec2d origin,
		double power, double angle);

	void make_asteroid(GameWorld& new_GameWorld, double scale,
		Vec2d pos, std::mt19937& rng);

	void make_asteroids(GameWorld& new_GameWorld,
		int num, double scale, bool isNew, std::mt19937& rng,
		Player* player = nullptr, Vec2d pos = { 0.0, 0.0 });

	void make_enemy(GameWorld& new_GameWorld, std::mt19937& rng,
		Player* player);

	Player* make_player(GameWorld& new_GameWorld, std::mt19937& rng);

	void clean_up(GameWorld& gw, ScoreManager& scoreMan, std::mt19937& rng);

	bool wasPlayerKilled(Player* player);
    void checkPlayerHit(Player* player);
	void checkBulletsHit();

	std::vector<std::unique_ptr<PhysicsEntity>> physEntities;
	std::vector<std::unique_ptr<PhysicsComponent>> physMan;
};

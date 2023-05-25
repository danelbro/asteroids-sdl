#pragma once

// EntityManager class to create, store and destroy entities

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

class EntityManager {
public:
	EntityManager(std::vector<std::unique_ptr<PhysicsComponent>> &physMan);

	void make_bullet(Vec2d origin, double power, Vec2d angle);

	void make_asteroid(GameWorld* new_GameWorld, Vec2d pos,
		std::vector<Vec2d> shape, SdlColor color, double scale, double mass,
		double impulseMin, double impulseMax, double radius, std::mt19937& rng);

	void make_asteroids(GameWorld* new_GameWorld, int num,
		double scale, std::mt19937& rng);

	void make_enemy();

	std::shared_ptr<Player> make_player(GameWorld* new_GameWorld, Vec2d pos, 
		std::vector<Vec2d> shape, SdlColor color, double scale, double mass, 
		double power, double turnSpeed, double shotPower,
		double warpTimer, int new_lives);

	std::vector<std::shared_ptr<Entity>> entities{ };
protected:
	std::vector<std::unique_ptr<PhysicsComponent>> &m_physMan;
};
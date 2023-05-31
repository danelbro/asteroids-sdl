#include "../inc/EntityManager.hpp"

#include <memory>
#include <random>
#include <vector>

#include "../inc/Asteroid.hpp"
#include "../inc/Bullet.hpp"
#include "../inc/Enemy.hpp"
#include "../inc/Entity.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/PhysicsComponent.hpp"
#include "../inc/Player.hpp"
#include "../inc/Vec2d.hpp"

EntityManager::EntityManager(std::vector<std::unique_ptr<PhysicsComponent>> &physMan)
	:m_physMan{ physMan }
{}

void EntityManager::make_bullet()
{
	return;
}


void EntityManager::make_asteroid(GameWorld* new_GameWorld, Vec2d pos, 
	std::vector<Vec2d> shape, SdlColor color, double scale, double mass,
	double impulseMin, double impulseMax, double radius, std::mt19937& rng)
{
	m_physMan.push_back(std::make_unique<PhysicsComponent>(mass, nullptr));

	entities.push_back(std::make_shared<Asteroid>(new_GameWorld, pos,
		shape, color, scale, m_physMan.back().get(), impulseMin, impulseMax, 
		radius, rng));
}

void EntityManager::make_asteroids(GameWorld* new_GameWorld, int num,
	double scale, std::mt19937& rng)
{
	constexpr double radiusMin = 5.0;
	constexpr double radiusMax = 30.0;
	std::uniform_real_distribution<double> radiusDist(radiusMin, radiusMax);

	std::uniform_real_distribution<double> xDist(0, new_GameWorld->screen.w);
	std::uniform_real_distribution<double> yDist(0, new_GameWorld->screen.h);

	const SdlColor color{ 0xff, 0xff, 0xff, 0xff }; // white

	const double mass{ 1.0 };
	constexpr double impulseMin{ 250'000.0 };
	constexpr double impulseMax{ 500'000.0 };
	
	for (int i { num }; i > 0; i--)
	{
		Vec2d pos{ xDist(rng), yDist(rng) };
		std::vector<Vec2d> shape{ };
		make_asteroid(new_GameWorld, pos, shape, color, scale,
			mass, impulseMin, impulseMax, radiusDist(rng), rng);
	}
}

void EntityManager::make_enemy()
{
	return;
}

std::shared_ptr<Player> EntityManager::make_player(GameWorld* new_GameWorld, 
	Vec2d pos, std::vector<Vec2d> shape, SdlColor color, double scale, double mass, 
	double power, double turnSpeed, double shotPower,
	double warpTimer, int new_lives)
{
	m_physMan.push_back(std::make_unique<PhysicsComponent>(mass, nullptr));

	std::shared_ptr<Player> player{
		std::make_shared<Player>(new_GameWorld, pos, shape, color, scale,
		power, turnSpeed, shotPower, m_physMan.back().get(), warpTimer, new_lives)
	};
	
	entities.push_back(player);

	return player;
}

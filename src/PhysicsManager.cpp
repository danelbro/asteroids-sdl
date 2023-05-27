#include "../inc/PhysicsManager.hpp"

#include <memory>
#include <random>
#include <vector>

#include "../inc/Asteroid.hpp"
#include "../inc/Bullet.hpp"
#include "../inc/Enemy.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/PhysicsComponent.hpp"
#include "../inc/Player.hpp"
#include "../inc/Ship.hpp"
#include "../inc/Vec2d.hpp"

PhysicsManager::PhysicsManager()
	: physEntities{ }, physMan{ }
{}

void PhysicsManager::make_bullet(GameWorld* new_GameWorld, Vec2d origin,
	double power, double angle, Ship* new_owner)
{
	constexpr double mass{ 0.003 };
	constexpr double scale{ 1.0 };
	constexpr double lifespan{ 2.0 }; // seconds

	const std::vector<Vec2d> shape{ {-1, -4}, {1, -4}, {1, 4}, {-1, 4} };
	const SdlColor color{ 0xff, 0xff, 0xff, 0xff }; // white

	physMan.push_back(std::make_unique<PhysicsComponent>(mass, nullptr));
	physMan.back()->setAngle(angle);
	physMan.back()->setFrameImpulse(power);

	physEntities.push_back(std::make_shared<Bullet>(new_GameWorld, origin, shape,
		color, scale, physMan.back().get(), new_owner, lifespan));
}


void PhysicsManager::make_asteroid(GameWorld* new_GameWorld, Vec2d pos,
	std::vector<Vec2d> shape, SdlColor color, double scale, double mass,
	double impulseMin, double impulseMax, double radius, std::mt19937& rng)
{
	physMan.push_back(std::make_unique<PhysicsComponent>(mass, nullptr));

	physEntities.push_back(std::make_shared<Asteroid>(new_GameWorld, pos,
		shape, color, scale, physMan.back().get(), impulseMin, impulseMax,
		radius, rng));
}

void PhysicsManager::make_asteroids(GameWorld* new_GameWorld, int num,
	double scale, std::mt19937& rng)
{
	constexpr double radiusMin = 20.0;
	constexpr double radiusMax = 25.0;
	std::uniform_real_distribution<double> radiusDist(radiusMin, radiusMax);

	std::uniform_real_distribution<double> xDist(0, new_GameWorld->screen.w);
	std::uniform_real_distribution<double> yDist(0, new_GameWorld->screen.h);

	const SdlColor color{ 0xff, 0xff, 0xff, 0xff }; // white

	const double mass{ 1.0 };
	constexpr double impulseMin{ 250'000.0 };
	constexpr double impulseMax{ 500'000.0 };

	for (int i{ num }; i > 0; i--)
	{
		Vec2d pos{ xDist(rng), yDist(rng) };
		std::vector<Vec2d> shape{ };
		make_asteroid(new_GameWorld, pos, shape, color, scale,
			mass, impulseMin, impulseMax, radiusDist(rng), rng);
	}
}

void PhysicsManager::make_enemy()
{
	return;
}

std::shared_ptr<Player> PhysicsManager::make_player(GameWorld* new_GameWorld,
	Vec2d pos, std::vector<Vec2d> shape, SdlColor color, double scale, double mass,
	double power, double turnSpeed, double shotPower,
	double warpTimer, int new_lives)
{
	physMan.push_back(std::make_unique<PhysicsComponent>(mass, nullptr));

	std::shared_ptr<Player> player{
		std::make_shared<Player>(new_GameWorld, pos, shape, color, scale,
		power, turnSpeed, shotPower, physMan.back().get(), warpTimer, new_lives)
	};

	physEntities.push_back(player);

	return player;
}

void PhysicsManager::clean_up()
{
	for (size_t i{ 0 }; i < physEntities.size(); i++)
		if (physEntities[i]->kill_it())
		{
			physMan.erase(physMan.begin() + i);
			physEntities.erase(physEntities.begin() + i);
		}
}
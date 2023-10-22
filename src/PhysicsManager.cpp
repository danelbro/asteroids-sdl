#include "../inc/PhysicsManager.hpp"

#include <memory>
#include <random>
#include <vector>

#include "../inc/Asteroid.hpp"
#include "../inc/Bullet.hpp"
#include "../inc/Enemy.hpp"
#include "../inc/Entity.hpp"
#include "../inc/FlagEnums.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/PhysicsComponent.hpp"
#include "../inc/Player.hpp"
#include "../inc/ScoreManager.hpp"
#include "../inc/Ship.hpp"
#include "../inc/Vec2d.hpp"
#include "../inc/VectorDraw.hpp"

PhysicsManager::PhysicsManager()
	: physEntities{ }, physMan{ }
{}

void PhysicsManager::make_bullet(GameWorld& new_GameWorld, Vec2d origin,
	double power, double angle, Ship& new_owner)
{
	constexpr double mass{ 0.003 };
	constexpr double scale{ 1.0 };
	constexpr double lifespan{ 1.0 }; // seconds

	const std::vector<Vec2d> shape{ {1, -3}, {-1, -3}, {-2, 3}, {2, 3} };

	physMan.push_back(std::make_unique<PhysicsComponent>(mass, nullptr));
	physMan.back()->setAngle(angle);
	physMan.back()->setFrameImpulse(power);

	physEntities.push_back(std::make_unique<Bullet>(new_GameWorld, origin,
		shape, customCols::bullet_col, scale, physMan.back().get(),
		new_owner, lifespan));
}


void PhysicsManager::make_asteroid(GameWorld& new_GameWorld, double scale,
	Vec2d pos, std::mt19937& rng)
{
	const double mass{ 1.0 };

	constexpr double radiusMin = 20.0;
	constexpr double radiusMax = 25.0;
	std::uniform_real_distribution<double> radiusDist(radiusMin, radiusMax);
	double radius{ radiusDist(rng) };

	constexpr double impulseMin{ 750'000.0 };
	constexpr double impulseMax{ 1'500'000.0 };
	std::uniform_real_distribution<double> impulseDist(
		impulseMin, impulseMax
	);
	double impulse{ impulseDist(rng) };

	std::uniform_real_distribution<double> angleDist(0.0, 360.0);
	double angle{ angleDist(rng) };

	std::vector<Vec2d> shape{ };
	int vertexes{ 13 };
	std::normal_distribution<double> cragDistLow(-5.0, 0.5);
	std::normal_distribution<double> cragDistHigh(5.0, 0.5);
	std::uniform_int_distribution<> coinFlip(1, 2);
	double sliceAngle{ (2 * M_PI / vertexes) };
	for (int i{ 0 }; i < vertexes; ++i)
	{
		double cragDepth{ };
		int coin{ coinFlip(rng) };
		if (coin == 2)
			cragDepth = cragDistHigh(rng);
		else
			cragDepth = cragDistLow(rng);
		shape.push_back(Vec2d{std::sin(sliceAngle * i) * (radius + cragDepth),
			-std::cos(sliceAngle * i) * (radius + cragDepth)});
	}

	physMan.push_back(std::make_unique<PhysicsComponent>(mass, nullptr));

	physEntities.push_back(std::make_unique<Asteroid>(new_GameWorld, pos,
		shape, customCols::asteroid_col, scale, physMan.back().get(), impulse,
		angle, radius));
}

static Vec2d findRandomDistantPos(std::mt19937& rng,
	Entity* distant, double distance, int w, int h)
{
	Vec2d new_pos{ };
	bool isTooClose{ true };
	do {
		new_pos = utl::randomPos(rng, w, h);

		Vec2d distanceToPlayer{ new_pos - distant->pos() };
		if (distanceToPlayer.magnitude() > distance)
			isTooClose = false;
	} while (isTooClose);
	return new_pos;
}

void PhysicsManager::make_asteroids(GameWorld& new_GameWorld, int num,
	double scale, bool isNew, std::mt19937& rng, Player* player, Vec2d pos)
{
	constexpr double asteroidDistance{ 50.0 };

	for (int i{ num }; i > 0; i--)
	{
		if (isNew) {
			Vec2d new_pos{ findRandomDistantPos(rng, player,
				asteroidDistance * scale, new_GameWorld.screen.w,
				new_GameWorld.screen.h) };
			make_asteroid(new_GameWorld, scale, new_pos, rng);
		}
		else {
			make_asteroid(new_GameWorld, scale, pos, rng);
		}
	}
}

// shaped mostly like the player
static const std::vector<Vec2d> enemyPointy
{
	{0, -30},  // top
	{15, -10}, // top right
	{-15, -10}, {15, -10}, // cross bar
	{20, 30},  // bottom right
	{0, 15},   // bottom
	// {0, -30}, {0, 15}, // dorsal line
	{-20, 30}, // bottom right
	{-15, -10} // top left
};

// more ufo shaped
static const std::vector<Vec2d> enemyUFO
{
	{ 20, -20 },
	{ 40, 0 }, { 45, 0 },
	{ -45, 0 }, { 45, 0 },
	{ 40, 20 }, { -40, 20 },
	{ -45, 0 }, { -40, 0 },
	{ -20, -20 }
};

void PhysicsManager::make_enemy(GameWorld& gameWorld, std::mt19937& rng,
	Player* player)
{
	const std::vector<Vec2d> shape{ enemyPointy };

	constexpr double scale{ 1.0 };
	constexpr double power{ 5000.0 };
	constexpr double turnSpeed{ 300.0 };
	constexpr double shotPower{ 20000.0 };
	constexpr double mass{ 0.1 };

	constexpr double enemyDistance{ 100.0 };

	Vec2d new_pos{ findRandomDistantPos(rng, player, enemyDistance * scale,
		gameWorld.screen.w, gameWorld.screen.h) };

	physMan.push_back(std::make_unique<PhysicsComponent>(mass, nullptr));

	physEntities.push_back(std::make_unique<Enemy>(gameWorld, new_pos, shape,
		customCols::enemy_col, scale, power, turnSpeed, shotPower,
		physMan.back().get()));
}

static const std::vector<Vec2d> playerShape
{
	{0, -30},
	{20, 30},
	{-20, 30}
};

Player* PhysicsManager::make_player(GameWorld& gameWorld, std::mt19937& rng)
{
	const Vec2d pos{ gameWorld.screen.w / 2.0, gameWorld.screen.h / 2.0 };
	const std::vector<Vec2d> shape{ playerShape };
	constexpr double scale{ 1.0 };
	constexpr double power{ 5000.0 };
	constexpr double turnSpeed{ 300.0 };
	constexpr double shotPower{ 20000.0 };
	constexpr double mass{ 0.1 };
	constexpr double warpLength{ 1.0 };
	constexpr int lives{ 3 };
    constexpr double respawnLength{ 2.0 };
    constexpr double flashLength{ 0.2 };

	physMan.push_back(std::make_unique<PhysicsComponent>(mass, nullptr));

	auto player(std::make_unique<Player>( gameWorld, pos, shape,
		customCols::player_col, scale, power, turnSpeed, shotPower,
        physMan.back().get(), rng, warpLength,
        lives, respawnLength, flashLength));

	Player* plPtr = player.get();
	physEntities.push_back(std::move(player));

	return plPtr;
}

void PhysicsManager::clean_up(GameWorld& gw, ScoreManager& scoreMan,
	std::mt19937& rng)
{
	constexpr int BASE_AST_SCORE = 300;
	constexpr int BASE_ENEMY_SCORE = 500;
	constexpr int PENALTY = -5;

	for (size_t i{ 0 }; i < physEntities.size(); i++) {
		PhysicsEntity* phys = physEntities[i].get();
		if (phys->toBeKilled())
		{
			switch (phys->type)
			{
			case EntityFlag::ASTEROID:
				scoreMan.update_score(
					static_cast<int>(BASE_AST_SCORE / phys->scale()));
				if (phys->scale() > 1.0) {
					make_asteroids(gw, 2, phys->scale() - 1.0, false, rng,
						nullptr, phys->pos());
				}
				break;
			case EntityFlag::ENEMY:
				scoreMan.update_score(BASE_ENEMY_SCORE);
				break;
			case EntityFlag::BULLET:
				if (phys->wayward)
					scoreMan.update_score(PENALTY);
				break;
			default:
				break;
			}

			physMan.erase(physMan.begin() + static_cast<long>(i));
			physEntities.erase(physEntities.begin() + static_cast<long>(i));
		}
	}
}

// checks whether the player got hit and whether they're out of lives.
// return true if out of lives
void PhysicsManager::checkPlayerHit(Player* plr)
{
    for (auto& ent : physEntities) {
        if (ent->type == EntityFlag::ASTEROID
            || ent->type == EntityFlag::ENEMY
            || ent->type == EntityFlag::ENEMY_BULLET) {
            if (utl::PointInPolygon(plr->pos(), ent->fillShape())) {
                plr->kill_it();
            }
        }
    }
}

bool PhysicsManager::wasPlayerKilled(Player* plr)
{
    if (plr->toBeKilled()) return true;

    return false;
}

void PhysicsManager::checkBulletsHit()
{
	for (auto& bul : physEntities) {
		if (bul->type == EntityFlag::BULLET && !bul->toBeKilled()) {
			for (auto& target : physEntities) {
				if (target->type == EntityFlag::ASTEROID
					|| target->type == EntityFlag::ENEMY) {
					if (utl::PointInPolygon(bul->pos(), target->fillShape())) {
						target->kill_it();
						bul->kill_it();
						bul->wayward = false;
						break;
					}
				}
			}
		}
	}
}

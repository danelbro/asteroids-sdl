#include "../inc/PhysicsManager.hpp"

#include <memory>
#include <random>
#include <vector>

#include "../inc/Asteroid.hpp"
#include "../inc/Bullet.hpp"
#include "../inc/Enemy.hpp"
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

void PhysicsManager::make_bullet(GameWorld* new_GameWorld, Vec2d origin,
	double power, double angle, Ship* new_owner)
{
	constexpr double mass{ 0.003 };
	constexpr double scale{ 1.0 };
	constexpr double lifespan{ 1.0 }; // seconds

	const std::vector<Vec2d> shape{ {1, -3}, {-1, -3}, {-2, 3}, {2, 3} };

	physMan.push_back(std::make_unique<PhysicsComponent>(mass, nullptr));
	physMan.back()->setAngle(angle);
	physMan.back()->setFrameImpulse(power);

	physEntities.push_back(std::make_unique<Bullet>(new_GameWorld, origin, shape,
		customCols::bullet_col, scale, physMan.back().get(), new_owner, lifespan));
}


void PhysicsManager::make_asteroid(GameWorld* new_GameWorld, double scale, Vec2d pos,
	std::mt19937& rng)
{
	const double mass{ 1.0 };

	constexpr double radiusMin = 20.0;
	constexpr double radiusMax = 25.0;
	std::uniform_real_distribution<double> radiusDist(radiusMin, radiusMax);
	double radius{ radiusDist(rng) };

	constexpr double impulseMin{ 750'000.0 };
	constexpr double impulseMax{ 1'500'000.0 };
	std::uniform_real_distribution<double> impulseDist(impulseMin, impulseMax);
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
		shape.push_back(Vec2d{ std::sin(sliceAngle * i) * (radius + cragDepth),
			-std::cos(sliceAngle * i) * (radius + cragDepth) });
	}

	physMan.push_back(std::make_unique<PhysicsComponent>(mass, nullptr));

	physEntities.push_back(std::make_unique<Asteroid>(new_GameWorld, pos, shape,
		customCols::asteroid_col, scale, physMan.back().get(), impulse, angle, radius));
}

void PhysicsManager::make_asteroids(GameWorld* new_GameWorld, int num,
	double scale, char flag, std::mt19937& rng, Player* player, Vec2d pos)
{
	std::uniform_real_distribution<double> xDist(0, new_GameWorld->screen.w);
	std::uniform_real_distribution<double> yDist(0, new_GameWorld->screen.h);
	Vec2d new_pos{ };

	for (int i{ num }; i > 0; i--)
	{
		if (flag == 'n') {
			bool isTooClose{ true };
			while (isTooClose) {
				new_pos.x = xDist(rng);
				new_pos.y = yDist(rng);

				Vec2d distanceToPlayer{ new_pos - player->pos() };
				if (distanceToPlayer.magnitude() > 30.0 * scale)
					isTooClose = false;
			}

			make_asteroid(new_GameWorld, scale, new_pos, rng);
		}
		else {
			make_asteroid(new_GameWorld, scale, pos, rng);
		}
	}
}

void PhysicsManager::make_enemy()
{
	return;
}

Player* PhysicsManager::make_player(GameWorld* gameWorld)
{
	const Vec2d pos{ gameWorld->screen.w / 2.0, gameWorld->screen.h / 2.0 };
	const std::vector<Vec2d> shape{ {0, -30}, {20, 30}, {-20, 30} };
	constexpr double scale{ 1.0 };
	constexpr double power{ 5000.0 };
	constexpr double turnSpeed{ 300.0 };
	constexpr double shotPower{ 20000.0 };
	constexpr double mass{ 0.1 };
	constexpr double warpTimer{ 1.0 };
	constexpr int lives{ 3 };

	physMan.push_back(std::make_unique<PhysicsComponent>(mass, nullptr));

	std::unique_ptr<Player> player(new Player{ gameWorld, pos, shape, customCols::player_col, scale,
		power, turnSpeed, shotPower, physMan.back().get(), warpTimer, lives });

	Player* plPtr = player.get();
	physEntities.push_back(std::move(player));

	return plPtr;
}

void PhysicsManager::clean_up(GameWorld* gw, ScoreManager* scoreMan, std::mt19937& rng)
{
	constexpr int BASE_AST_SCORE = 300;
	constexpr int PENALTY = -5;

	for (size_t i{ 0 }; i < physEntities.size(); i++) {
		PhysicsEntity* phys = physEntities[i].get();
		if (phys->toBeKilled())
		{
			switch (phys->type)
			{
			case EntityFlag::ASTEROID:
				scoreMan->update_score(static_cast<int>(BASE_AST_SCORE / phys->scale()));
				if (phys->scale() > 1.0) {
					make_asteroids(gw, 2, phys->scale() - 1.0, '\0', rng, nullptr, phys->pos());
				}
				break;
			case EntityFlag::BULLET:
				if (phys->wayward)
					scoreMan->update_score(PENALTY);
				break;
			default:
				break;
			}

			physMan.erase(physMan.begin() + static_cast<long>(i));
			physEntities.erase(physEntities.begin() + static_cast<long>(i));
		}
	}
}

bool PhysicsManager::check_player_hit()
{
	for (auto& plr : physEntities) {
		if (plr->type == EntityFlag::PLAYER) {
			for (auto& ast : physEntities) {
				if (ast->type == EntityFlag::ASTEROID) {
					bool hit{ PointInPolygon(plr->pos(), ast->fillShape()) };
					if (hit) {
						plr->kill_it();
						return false;
					}
				}
			}
		}
	}

	return true;
}

bool PhysicsManager::check_asteroids_hit()
{
	bool hits{ false };
	for (auto& bul : physEntities) {
		if (bul->type == EntityFlag::BULLET) {
			for (auto& ast : physEntities) {
				if (ast->type == EntityFlag::ASTEROID) {
					if (PointInPolygon(bul->pos(), ast->fillShape())) {
						ast->kill_it();
						bul->kill_it();
						bul->wayward = false;
						hits = true;
						break;
					}
				}
			}
		}
	}

	return hits;
}

#include "PhysicsManager.hpp"

#include <memory>
#include <random>
#include <type_traits>
#include <vector>

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
#include "utility.hpp"
#include "ValtrAlgorithm.hpp"

PhysicsManager::PhysicsManager(GameWorld& gameWorld, std::mt19937& rng)
	: physEntities{ }, m_gameWorld{ gameWorld }, m_rng{ rng },
      m_player{ make_player() }
{
    physEntities.reserve(500);
}

void PhysicsManager::make_bullet(Vec2d origin, double power, double angle)
{
	constexpr double mass{ 0.003 };
	constexpr double scale{ 1.0 };
	constexpr double lifespan{ 1.0 }; // seconds

	const std::vector<Vec2d> shape{ {1, -3}, {-1, -3}, {-2, 3}, {2, 3} };

	physEntities.emplace_back(std::make_unique<Bullet>(m_gameWorld, origin,
                                                       shape,
                                                       customCols::bullet_col,
                                                       scale, mass, lifespan,
                                                       angle, power));
}


void PhysicsManager::make_asteroid(double scale, Vec2d pos)
{
	const double mass{ 1.0 };

	constexpr double radiusMin = 25.0;
	constexpr double radiusMax = 30.0;
	std::uniform_real_distribution<double> radiusDist{ radiusMin, radiusMax };
	double radius{ radiusDist(m_rng) };

	constexpr double impulseMin{ 750'000.0 };
	constexpr double impulseMax{ 1'500'000.0 };
	std::uniform_real_distribution<double> impulseDist{
		impulseMin, impulseMax
	};
	double impulse{ impulseDist(m_rng) };

	std::uniform_real_distribution<double> angleDist{ 0.0, 360.0 };
	double angle{ angleDist(m_rng) };

    std::uniform_int_distribution<int> vertexDist{ 8, 10 };
	int vertexes{ vertexDist(m_rng) };

	std::vector<Vec2d> shape{ };
    shape.reserve(static_cast<size_t>(vertexes));

    shape = utl::genRandConvexPolygon(vertexes, radius, m_rng);

	physEntities.emplace_back(
        std::make_unique<Asteroid>(m_gameWorld, pos, shape,
                                   customCols::asteroid_col, scale, mass,
                                   impulse, angle, radius));
}

static Vec2d findRandomDistantPos(std::mt19937& rng,
	Entity& distant, double distance, int w, int h)
{
	Vec2d new_pos{ };
	bool isTooClose{ true };
	do {
		new_pos = utl::randomPos(rng, w, h);

		Vec2d distanceToPlayer{ new_pos - distant.pos() };
		if (distanceToPlayer.magnitude() > distance)
			isTooClose = false;
	} while (isTooClose);
	return new_pos;
}

void PhysicsManager::make_asteroids(int num, double scale, bool isNew,
                                    Vec2d pos)
{
	constexpr double asteroidDistance{ 50.0 };

	for (int i{ num }; i > 0; i--)
	{
		if (isNew) {
			Vec2d new_pos{ findRandomDistantPos(m_rng, m_player,
				asteroidDistance * scale, m_gameWorld.screen.w,
				m_gameWorld.screen.h) };
			make_asteroid(scale, new_pos);
		}
		else {
			make_asteroid(scale, pos);
		}
	}
}

// shaped mostly like the player
static const std::vector<Vec2d> enemyPointy
{
	{0, -30},  // top
	{15, -10}, // top right
	// {-15, -10}, {15, -10}, // cross bar
	{20, 30},  // bottom right
	// {0, 15},   // bottom
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

void PhysicsManager::make_enemy()
{
	const std::vector<Vec2d> shape{ enemyPointy };

	constexpr double scale{ 1.0 };
	constexpr double power{ 5000.0 };
	constexpr double turnSpeed{ 300.0 };
	constexpr double shotPower{ 20000.0 };
	constexpr double mass{ 0.1 };
    constexpr double cooldown{ 1.0 };

	constexpr double enemyDistance{ 75.0 };

	Vec2d new_pos{ findRandomDistantPos(m_rng, m_player,
                                        enemyDistance * scale,
                                        m_gameWorld.screen.w,
                                        m_gameWorld.screen.h) };

	physEntities.emplace_back(std::make_unique<Enemy>( m_gameWorld, new_pos,
                                                    shape,
                                                    customCols::enemy_col,
                                                    scale, power, turnSpeed,
                                                    shotPower, mass,
                                                    cooldown));
}

static const std::vector<Vec2d> playerShape
{
	{0, -30},
	{20, 30},
	{-20, 30}
};

Player& PhysicsManager::make_player()
{
	const Vec2d pos{ m_gameWorld.screen.w / 2.0, m_gameWorld.screen.h / 2.0 };
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
    constexpr double cooldown{ 0.25 };

	physEntities.emplace_back(std::make_unique<Player>(m_gameWorld, pos, shape,
                                                       customCols::player_col,
                                                       scale, power, turnSpeed,
                                                       shotPower, mass, m_rng,
                                                       warpLength, lives,
                                                       respawnLength,
                                                       flashLength, cooldown));

	return dynamic_cast<Player&>(*physEntities.back());
}

void PhysicsManager::clean_up(ScoreManager& scoreMan)
{
	constexpr int baseAsteroidScore = 300;
	constexpr int baseEnemyScore = 500;
	constexpr int penalty = -5;
    constexpr int newAsteroids = 2;

	for (size_t i{ 0 }; i < physEntities.size(); i++) {
		PhysicsEntity& phys = *physEntities[i];
		if (phys.toBeKilled()) {
			switch (phys.type)
            {
			case utl::EntityFlag::ASTEROID:
				scoreMan.update_score(
					static_cast<int>(baseAsteroidScore / phys.scale()));
				if (phys.scale() > 1.0)
					make_asteroids(newAsteroids, phys.scale() - 1.0,
                                   false, phys.pos());
				break;
			case utl::EntityFlag::ENEMY:
				scoreMan.update_score(baseEnemyScore);
				break;
			case utl::EntityFlag::BULLET:
				if (phys.wayward)
					scoreMan.update_score(penalty);
				break;
			default:
				break;
			}

			physEntities.erase(physEntities.begin() + static_cast<long>(i));
		}
	}
}

// checks whether the player got hit and whether they're out of lives.
// return true if out of lives
void PhysicsManager::checkPlayerHit()
{
    for (auto& ent : physEntities) {
        if (ent->type == utl::EntityFlag::ASTEROID
            || ent->type == utl::EntityFlag::ENEMY
            || ent->type == utl::EntityFlag::ENEMY_BULLET) {
            if (utl::areColliding(m_player, *ent)) {
                m_player.kill_it();
            }
        }
    }
}

bool PhysicsManager::wasPlayerKilled()
{
    if (m_player.toBeKilled()) return true;

    return false;
}

void PhysicsManager::checkBulletsHit()
{
	for (auto& bul : physEntities) {
		if (bul->type == utl::EntityFlag::BULLET && !bul->toBeKilled()) {
			for (auto& target : physEntities) {
				if (target->type == utl::EntityFlag::ASTEROID
					|| target->type == utl::EntityFlag::ENEMY) {
					if (utl::PointInPolygon(bul->pos(), target->collider())) {
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

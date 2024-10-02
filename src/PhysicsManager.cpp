#include "PhysicsManager.hpp"

#include <memory>
#include <random>
#include <vector>

#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Colors.hpp"
#include "Enemy.hpp"
#include "Entity.hpp"
#include "flags.hpp"
#include "GameWorld.hpp"
#include "PhysicsComponent.hpp"
#include "Player.hpp"
#include "ScoreManager.hpp"
#include "SDL_Interface.hpp"
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

void PhysicsManager::make_bullet(const Vec2d& origin, const double& power,
								 const double& angle, const utl::Colour& col,
								 const utl::EntityFlag& flag)
{
	constexpr double mass{ 0.003 };
	constexpr double scale{ 1.0 };
	constexpr double lifespan{ 1.0 }; // seconds

	const std::vector<Vec2d> shape{ {1, -3}, {-1, -3}, {-2, 3}, {2, 3} };

 	physEntities.push_back(std::make_unique<Bullet>(m_gameWorld, origin,
                                                    shape, col,
                                                    scale, mass, lifespan,
                                                    angle, power, flag));
}

void PhysicsManager::make_bullet(const PhysicsEntity& oldBullet)
{
	physEntities.emplace_back(
		std::make_unique<Bullet>(m_gameWorld, oldBullet.getPos(),
			oldBullet.shape(), oldBullet.color(), oldBullet.scale(),
			oldBullet.physicsComponent.mass(), 1.0,
			oldBullet.physicsComponent.angle(), 20000,
			utl::EntityFlag::BULLET));
	physEntities.back()->physicsComponent.setOwner(physEntities.back().get());
}

void PhysicsManager::make_asteroid(const double& scale, const Vec2d& pos)
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
                                   utl::customCols::asteroid_col, scale, mass,
                                   impulse, angle));
}

void PhysicsManager::make_asteroid(const PhysicsEntity& oldAsteroid)
{
	physEntities.emplace_back(
		std::make_unique<Asteroid>(m_gameWorld, oldAsteroid.getPos(),
			oldAsteroid.shape(), oldAsteroid.color(), oldAsteroid.scale(),
			oldAsteroid.physicsComponent.mass(), oldAsteroid.physicsComponent.impulse(),
			oldAsteroid.physicsComponent.angle()));
	physEntities.back()->physicsComponent.setOwner(physEntities.back().get());
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

void PhysicsManager::make_asteroids(int num, const double& scale, bool isNew,
                                    const Vec2d& pos)
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

static constexpr double enemy_scale{ 1.0 };
static constexpr double enemy_power{ 5000.0 };
static constexpr double enemy_turnSpeed{ 300.0 };
static constexpr double enemy_minVel{ 150.0 };
static constexpr double enemy_maxVel{ 300.0 };
static constexpr double enemy_shotPower{ 20000.0 };
static constexpr double enemy_mass{ 0.1 };
static constexpr double enemy_cooldown{ 1.0 };
static constexpr double enemy_distance{ 75.0 };

void PhysicsManager::make_enemy()
{
	const std::vector<Vec2d> shape{ enemyPointy };

	Vec2d new_pos{ findRandomDistantPos(m_rng, m_player,
                                        enemy_distance * enemy_scale,
                                        m_gameWorld.screen.w,
                                        m_gameWorld.screen.h) };

	physEntities.emplace_back(
		std::make_unique<Enemy>(m_gameWorld, new_pos, shape,
			utl::customCols::enemy_col, enemy_scale, enemy_power,
            enemy_turnSpeed, enemy_minVel, enemy_maxVel, enemy_shotPower,
            enemy_mass, enemy_cooldown, &m_player, *this, m_rng));
}

void PhysicsManager::make_enemy(const PhysicsEntity& oldEnemy)
{
	physEntities.emplace_back(
		std::make_unique<Enemy>(m_gameWorld, oldEnemy.getPos(),
			oldEnemy.shape(), oldEnemy.color(), oldEnemy.scale(), enemy_power,
            enemy_turnSpeed, enemy_minVel, enemy_maxVel, enemy_shotPower,
			oldEnemy.physicsComponent.mass(), enemy_cooldown, nullptr, *this,
			m_rng));
	physEntities.back()->physicsComponent.setOwner(physEntities.back().get());
}

static const std::vector<Vec2d> playerShape
{
	{0, -30},
	{20, 30},
	{-20, 30}
};

static constexpr double playerScale{ 1.0 };
static constexpr double playerEnginePower{ 5000.0 };
static constexpr double playerTurnSpeed{ 300.0 };
static constexpr double playerShotPower{ 20000.0 };
static constexpr double playerMass{ 0.1 };
static constexpr double playerWarpLength{ 1.0 };
static constexpr int playerLives{ 3 };
static constexpr double playerRespawnLength{ 2.0 };
static constexpr double playerFlashLength{ 0.2 };
static constexpr double playerGunCooldown{ 0.25 };

Player& PhysicsManager::make_player()
{
	const Vec2d playerPos{ m_gameWorld.screen.w / 2.0, m_gameWorld.screen.h / 2.0 };

	physEntities.emplace_back(
		std::make_unique<Player>(m_gameWorld, playerPos, playerShape,
								 utl::customCols::player_col, playerScale, playerEnginePower,
								 playerTurnSpeed, playerShotPower, playerMass, m_rng,
								 playerWarpLength, playerLives, playerRespawnLength,
								 playerFlashLength, playerGunCooldown));

	return static_cast<Player&>(*physEntities.back());
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
			switch (utl::entityStringMap[phys.type()])
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
            {
                Bullet& bulref = static_cast<Bullet&>(phys);
				if (bulref.wayward())
					scoreMan.update_score(penalty);
				break;
            }
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
        if (ent->type() == utl::entityMap[utl::EntityFlag::ASTEROID]
            || ent->type() == utl::entityMap[utl::EntityFlag::ENEMY]
            || ent->type() == utl::entityMap[utl::EntityFlag::ENEMY_BULLET]) {
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
	for (auto& physEnt : physEntities) {
		if (physEnt->type() == utl::entityMap[utl::EntityFlag::BULLET]
                        && !physEnt->toBeKilled()) {
            Bullet& bul{ static_cast<Bullet&>(*physEnt) };
			for (auto& target : physEntities) {
				if (target->type() == utl::entityMap[utl::EntityFlag::ASTEROID]
					|| target->type() == utl::entityMap[utl::EntityFlag::ENEMY]) {
					if (utl::PointInPolygon(bul.pos(), target->collider())) {
						target->kill_it();
						bul.kill_it();
						bul.wayward() = false;
						break;
					}
				}
			}
		}
	}
}

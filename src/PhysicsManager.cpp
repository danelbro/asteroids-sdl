#include "PhysicsManager.hpp"

#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Colors.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "ScoreManager.hpp"
#include "constants.hpp"
#include "flags.hpp"

#include <memory>
#include <random>
#include <utl_Entity.hpp>
#include <utl_GameWorld.hpp>
#include <utl_SDLInterface.hpp>
#include <utl_ValtrAlgorithm.hpp>
#include <utl_Vec2d.hpp>
#include <utl_VecGraphPhysComp.hpp>
#include <utl_VecGraphPhysEnt.hpp>
#include <utl_VectorDraw.hpp>
#include <utl_utility.hpp>
#include <vector>

static void copyPhysicsProperties(const utl::VecGraphPhysComp& physIn,
                                  utl::VecGraphPhysComp& physOut)
{
    physOut.setVelocity(physIn.velocity());
    physOut.setAcceleration(physIn.acceleration());
    physOut.setAngle(physIn.facing());
    physOut.setFrameImpulse(physIn.impulse());
}

PhysicsManager::PhysicsManager(utl::GameWorld& gameWorld, std::mt19937& rng)
    : physEntities{}, m_gameWorld{gameWorld}, m_rng{rng},
      m_player{make_player()}
{
    physEntities.reserve(500);
}

void PhysicsManager::make_bullet(const utl::Vec2d& origin, const double& power,
                                 const double& angle, const utl::Colour& col,
                                 const ENTITY_FLAG& flag)
{
    physEntities.push_back(std::make_unique<Bullet>(
        m_gameWorld, origin, constants::bulletShape, col,
        constants::bulletScale, constants::bulletMass,
        constants::bulletLifespan, angle, power, flag, true, true));
}

void PhysicsManager::make_bullet(const utl::VecGraphPhysEnt& oldBullet)
{
    physEntities.emplace_back(std::make_unique<Bullet>(
        m_gameWorld, oldBullet.pos(), oldBullet.shape(), oldBullet.color(),
        oldBullet.scale(), oldBullet.physicsComponent.mass(), 1.0,
        oldBullet.physicsComponent.facing(), 20'000, ENTITY_FLAG::BULLET, true,
        true));
    physEntities.back()->physicsComponent.setOwner(physEntities.back().get());
    copyPhysicsProperties(oldBullet.physicsComponent,
                          physEntities.back()->physicsComponent);
}

void PhysicsManager::make_asteroid(const double& scale, const utl::Vec2d& pos)
{
    std::uniform_real_distribution<double> radiusDist{
        constants::asteroidRadiusMin, constants::asteroidRadiusMax};
    double radius{radiusDist(m_rng)};

    std::uniform_real_distribution<double> impulseDist{
        constants::asteroidImpulseMin, constants::asteroidImpulseMax};
    double impulse{impulseDist(m_rng)};

    std::uniform_real_distribution<double> angleDist{0.0, 360.0};
    double angle{angleDist(m_rng)};

    std::uniform_int_distribution<int> vertexDist{
        constants::minAsteroidVertices, constants::maxAsteroidVertices};
    int vertexes{vertexDist(m_rng)};

    std::vector<utl::Vec2d> shape{};
    shape.reserve(static_cast<size_t>(vertexes));
    shape = utl::genRandConvexPolygon(vertexes, radius, m_rng);

    physEntities.emplace_back(std::make_unique<Asteroid>(
        m_gameWorld, pos, shape, customCols::asteroid_col, scale,
        constants::asteroidMass, impulse, angle, true, false));
}

void PhysicsManager::make_asteroid(const utl::VecGraphPhysEnt& oldAsteroid)
{
    physEntities.emplace_back(std::make_unique<Asteroid>(
        m_gameWorld, oldAsteroid.pos(), oldAsteroid.shape(),
        oldAsteroid.color(), oldAsteroid.scale(),
        oldAsteroid.physicsComponent.mass(),
        oldAsteroid.physicsComponent.impulse(),
        oldAsteroid.physicsComponent.facing(), true, false));
    physEntities.back()->physicsComponent.setOwner(physEntities.back().get());
    copyPhysicsProperties(oldAsteroid.physicsComponent,
                          physEntities.back()->physicsComponent);
}

static utl::Vec2d findRandomDistantPos(std::mt19937& rng, utl::Entity& distant,
                                       double distance, int w, int h)
{
    utl::Vec2d new_pos{};
    bool isTooClose{true};
    do {
        new_pos = utl::randomPos(rng, w, h);

        utl::Vec2d distanceToPlayer{new_pos - distant.pos()};
        if (distanceToPlayer.magnitude() > distance)
            isTooClose = false;
    } while (isTooClose);
    return new_pos;
}

void PhysicsManager::make_asteroids(int num, const double& scale, bool isNew,
                                    const utl::Vec2d& pos)
{
    constexpr double asteroidDistance{50.0};

    for (int i{num}; i > 0; i--) {
        if (isNew) {
            utl::Vec2d new_pos{findRandomDistantPos(
                m_rng, m_player, asteroidDistance * scale, m_gameWorld.screen.w,
                m_gameWorld.screen.h)};
            make_asteroid(scale, new_pos);
        } else {
            make_asteroid(scale, pos);
        }
    }
}

void PhysicsManager::make_enemy()
{
    const std::vector<utl::Vec2d> shape{constants::enemyShape};

    utl::Vec2d new_pos{findRandomDistantPos(
        m_rng, m_player, constants::enemyDistance * constants::enemyScale,
        m_gameWorld.screen.w, m_gameWorld.screen.h)};

    physEntities.emplace_back(std::make_unique<Enemy>(
        m_gameWorld, new_pos, shape, customCols::enemy_col,
        constants::enemyScale, constants::enemyPower, constants::enemyTurnSpeed,
        constants::enemyMinVel, constants::enemyMaxVel,
        constants::enemyShotPower, constants::enemyMass,
        constants::enemyCooldown, &m_player, *this, m_rng));
}

void PhysicsManager::make_enemy(const utl::VecGraphPhysEnt& oldEnemy)
{
    physEntities.emplace_back(std::make_unique<Enemy>(
        m_gameWorld, oldEnemy.pos(), oldEnemy.shape(), oldEnemy.color(),
        oldEnemy.scale(), constants::enemyPower, constants::enemyTurnSpeed,
        constants::enemyMinVel, constants::enemyMaxVel,
        constants::enemyShotPower, oldEnemy.physicsComponent.mass(),
        constants::enemyCooldown, nullptr, *this, m_rng));
    physEntities.back()->physicsComponent.setOwner(physEntities.back().get());
    copyPhysicsProperties(oldEnemy.physicsComponent,
                          physEntities.back()->physicsComponent);
}

Player& PhysicsManager::make_player()
{
    const utl::Vec2d playerPos{m_gameWorld.screen.w / 2.0,
                               m_gameWorld.screen.h / 2.0};

    physEntities.emplace_back(std::make_unique<Player>(
        m_gameWorld, playerPos, constants::playerShape, customCols::player_col,
        constants::playerScale, constants::playerEnginePower,
        constants::playerTurnSpeed, constants::playerShotPower,
        constants::playerMass, m_rng, constants::playerWarpLength,
        constants::playerLives, constants::playerRespawnLength,
        constants::playerFlashLength, constants::playerGunCooldown));

    return static_cast<Player&>(*physEntities.back());
}

void PhysicsManager::clean_up(ScoreManager& scoreMan, bool gameOver)
{
    constexpr int baseAsteroidScore = 300;
    constexpr int baseEnemyScore = 500;
    constexpr int penalty = -5;
    constexpr int newAsteroids = 2;

    for (size_t i{0}; i < physEntities.size(); i++) {
        utl::VecGraphPhysEnt& phys{*physEntities[i]};
        if (phys.toBeKilled()) {
            switch (ENTITY_STRING_MAP[phys.type()]) {
            case ENTITY_FLAG::ASTEROID: {
                if (!gameOver) {
                    scoreMan.update_score(
                        static_cast<int>(baseAsteroidScore / phys.scale()));
                }
                if (phys.scale() > 1.0) {
                    make_asteroids(newAsteroids, phys.scale() - 1.0, false,
                                   phys.pos());
                }
                break;
            }
            case ENTITY_FLAG::ENEMY: {
                if (!gameOver) {
                    scoreMan.update_score(baseEnemyScore);
                }
                break;
            }
            case ENTITY_FLAG::BULLET: {
                Bullet& bulref = static_cast<Bullet&>(phys);
                if (bulref.wayward() && scoreMan.lives > 0)
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
void PhysicsManager::check_player_hit()
{
    for (auto& ent : physEntities) {
        if (ent->type() == ENTITY_MAP[ENTITY_FLAG::ASTEROID]
            || ent->type() == ENTITY_MAP[ENTITY_FLAG::ENEMY]
            || ent->type() == ENTITY_MAP[ENTITY_FLAG::ENEMY_BULLET]) {
            if (utl::areColliding(m_player, *ent)) {
                m_player.kill_it();
            }
        }
    }
}

bool PhysicsManager::was_player_killed()
{
    if (m_player.toBeKilled())
        return true;

    return false;
}

void PhysicsManager::check_bullet_hits(bool gameOver)
{
    for (auto& physEnt : physEntities) {
        if ((physEnt->type() == ENTITY_MAP[ENTITY_FLAG::BULLET]
             || (gameOver
                 && physEnt->type() == ENTITY_MAP[ENTITY_FLAG::ENEMY_BULLET]))
            && !physEnt->toBeKilled()) {
            Bullet& bul{static_cast<Bullet&>(*physEnt)};
            for (auto& target : physEntities) {
                if (target->type() == ENTITY_MAP[ENTITY_FLAG::ASTEROID]
                    || (!gameOver
                        && target->type() == ENTITY_MAP[ENTITY_FLAG::ENEMY])) {
                    if (utl::isPointInPolygon(bul.pos(), target->collider())) {
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

bool PhysicsManager::do_entities_remain_of_type(
    ENTITY_FLAG entityType,
    const std::vector<std::unique_ptr<utl::VecGraphPhysEnt>>& entities)
{
    for (auto& ent : entities) {
        if (ent->type() == ENTITY_MAP[entityType]) {
            return true;
        }
    }

    return false;
}

void PhysicsManager::kill_entities_of_type(
    ENTITY_FLAG entityType,
    std::vector<std::unique_ptr<utl::VecGraphPhysEnt>>& entities)
{
    for (auto& physEnt : entities) {
        if (physEnt->type() == ENTITY_MAP[entityType]) {
            physEnt->kill_it();
        }
    }
}

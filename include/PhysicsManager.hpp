#pragma once

// PhysicsManager class to create, store and destroy instances of PhysicsEntity

#include "flags.hpp"

#include <memory>
#include <random>
#include <utl_GameWorld.hpp>
#include <utl_PhysicsEntity.hpp>
#include <utl_SDLInterface.hpp>
#include <utl_Vec2d.hpp>
#include <vector>

class Player;
class ScoreManager;

class PhysicsManager {
public:
    PhysicsManager(utl::GameWorld& gameWorld, std::mt19937& rng);

    void make_bullet(const utl::Vec2d& origin, const double& power,
                     const double& angle, const utl::Colour& col,
                     const ENTITY_FLAG& flag);
    void make_bullet(const utl::VecGraphPhysEnt& oldBullet);

    void make_asteroid(const double& scale, const utl::Vec2d& pos);
    void make_asteroid(const utl::VecGraphPhysEnt& oldAsteroid);

    void make_asteroids(int num, const double& scale, bool isNew,
                        const utl::Vec2d& pos = {0.0, 0.0});

    void make_enemy();
    void make_enemy(const utl::VecGraphPhysEnt& oldEnemy);

    Player& make_player();

    void clean_up(ScoreManager& scoreMan, bool gameOver);

    bool was_player_killed();
    void check_player_hit();
    void check_bullet_hits(bool gameOver);

    bool do_entities_remain_of_type(
        ENTITY_FLAG entityType,
        const std::vector<std::unique_ptr<utl::VecGraphPhysEnt>>& physEntities);

    void kill_entities_of_type(
        ENTITY_FLAG entityType,
        std::vector<std::unique_ptr<utl::VecGraphPhysEnt>>& physEntities);

    Player& player() { return m_player; }

    std::vector<std::unique_ptr<utl::VecGraphPhysEnt>> physEntities;

private:
    utl::GameWorld& m_gameWorld;
    std::mt19937& m_rng;
    Player& m_player;
};

#pragma once

// PhysicsManager class to create, store and destroy instances of PhysicsEntity

#include <memory>
#include <random>
#include <vector>

#include "SDL_Interface.hpp"

#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "utility.hpp"
#include "Vec2d.hpp"

struct GameWorld;

class Enemy;
class PhysicsEntity;
class Player;
class ScoreManager;

class PhysicsManager {
public:
	PhysicsManager(GameWorld& gameWorld, std::mt19937& rng);

	void make_bullet(const Vec2d& origin, const double& power,
					 const double& angle, const utl::Colour& col,
					 const utl::EntityFlag& flag);
	void make_bullet(const Bullet& oldBullet);

	void make_asteroid(const double& scale, const Vec2d& pos);
	void make_asteroid(const Asteroid& oldAsteroid);

	void make_asteroids(int num, const double& scale, bool isNew,
                        const Vec2d& pos = { 0.0, 0.0 });

	void make_enemy();
	void make_enemy(const Enemy& oldEnemy);

	Player& make_player();

	void clean_up(ScoreManager& scoreMan);

	bool wasPlayerKilled();
    void checkPlayerHit();
	void checkBulletsHit();

    Player& player() { return m_player; }

	std::vector<std::unique_ptr<PhysicsEntity>> physEntities;
private:
    GameWorld& m_gameWorld;
    std::mt19937& m_rng;
    Player& m_player;
};

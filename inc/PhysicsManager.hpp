#pragma once

// PhysicsManager class to create, store and destroy instances of PhysicsEntity

#include <memory>
#include <random>
#include <vector>

#include <SDL.h>

#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Colors.hpp"
#include "GameWorld.hpp"
#include "Player.hpp"
#include "ScoreManager.hpp"
#include "Ship.hpp"
#include "Vec2d.hpp"
#include "VectorDraw.hpp"
#include "utility.hpp"

class PhysicsManager {
public:
	PhysicsManager(GameWorld& gameWorld, std::mt19937& rng);

	void make_bullet(Vec2d origin, double power, double angle,
                     SdlColor col, utl::EntityFlag flag);

	void make_asteroid(double scale, Vec2d pos);

	void make_asteroids(int num, double scale, bool isNew,
                        Vec2d pos = { 0.0, 0.0 });

	void make_enemy();

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

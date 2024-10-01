#pragma once

#include <random>
#include <vector>

#include "AIComponent.hpp"
#include "Ship.hpp"
#include "SDL_Interface.hpp"

struct GameWorld;
struct Vec2d;

class PhysicsManager;
class Player;

class Enemy : public Ship {
public:
    Enemy(GameWorld& new_gameWorld, const Vec2d& pos,
          const std::vector<Vec2d>& shape, const utl::Colour& colour,
          const double& scale, const double& power, const double& turnSpeed,
          const double& maxVel, const double& shotPower, const double& mass,
          const double& cooldown, Player* plr, PhysicsManager& physMan,
          std::mt19937& rng);

    ~Enemy() = default;
    Enemy(const Enemy&) = default;
    Enemy& operator=(const Enemy&) = delete;

    double maxVel() const { return m_maxVel; }

    void update(double t, double dt) override;
    void playerKilled() { m_plr = nullptr; }

private:
    double m_maxVel;
    AIComponent m_aiComponent;
    Player* m_plr;
};

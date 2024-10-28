#pragma once

#include "AIComponent.hpp"
#include "Ship.hpp"

#include <random>
#include <utl_GameWorld.hpp>
#include <utl_SDLInterface.hpp>
#include <utl_Vec2d.hpp>
#include <vector>

class PhysicsManager;
class Player;

class Enemy : public Ship {
public:
    Enemy(utl::GameWorld& new_gameWorld, const utl::Vec2d& pos,
          const std::vector<utl::Vec2d>& shape, const utl::Colour& colour,
          const double& scale, const double& power, const double& turnSpeed,
          const double& minVel, const double& maxVel, const double& shotPower,
          const double& mass, const double& cooldown, Player* plr,
          PhysicsManager& physMan, std::mt19937& rng);

    ~Enemy() = default;
    Enemy(const Enemy&) = default;
    Enemy& operator=(const Enemy&) = delete;

    Enemy(Enemy&&) = default;
    Enemy& operator=(Enemy&&) = delete;

    double minVel() const { return m_minVel; }
    double maxVel() const { return m_maxVel; }

    void update(double t, double dt) override;
    void playerKilled() { m_plr = nullptr; }
    void clearedScreen() { m_isScreenClear = true; }

private:
    double m_minVel;
    double m_maxVel;
    AIComponent m_aiComponent;
    Player* m_plr;
    bool m_isScreenClear;
};

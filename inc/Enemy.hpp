#pragma once

#include <vector>

#include "AIComponent.hpp"
#include "Colors.hpp"
#include "GameWorld.hpp"
#include "PhysicsManager.hpp"
#include "Ship.hpp"
#include "Vec2d.hpp"

class Enemy : public Ship {
public:
    Enemy(GameWorld& new_gameWorld, Vec2d pos, std::vector<Vec2d> shape,
          SdlColor colour, double scale, double power, double turnSpeed,
          double maxVel, double shotPower, double mass, double cooldown,
          Player* plr, PhysicsManager& physMan);

    ~Enemy() = default;
    Enemy(const Enemy&) = delete;
    Enemy& operator=(const Enemy&) = delete;

    double maxVel() const { return m_maxVel; }

    void update(double t, double dt) override;
    void playerKilled() { m_plr = nullptr; }

private:
    double m_maxVel;
    AIComponent m_aiComponent;
    Player* m_plr;
};

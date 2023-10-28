#pragma once

#include <memory>
#include <vector>

#include "AIComponent.hpp"
#include "Colors.hpp"
#include "GameWorld.hpp"
#include "Ship.hpp"
#include "PhysicsComponent.hpp"
#include "Vec2d.hpp"

class Enemy : public Ship {
public:
    Enemy(GameWorld& new_gameWorld, Vec2d pos, std::vector<Vec2d> shape,
        SdlColor colour, double scale, double power, double turnSpeed,
        double shotPower, double mass);

    void update(double t, double dt) override;

private:
    AIComponent aiComponent;
};

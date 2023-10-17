#pragma once

#include <memory>
#include <vector>

#include "Colors.hpp"
#include "GameWorld.hpp"
#include "Ship.hpp"
#include "PhysicsComponent.hpp"
#include "Vec2d.hpp"

class AIComponent;

class Enemy : public Ship {
public:
    Enemy(GameWorld* new_gameWorld, Vec2d pos, std::vector<Vec2d> shape, 
        SdlColor colour, double scale, double power, double turnSpeed, 
        double shotPower, PhysicsComponent* new_physicsComponent);

    void update(double t, double dt) override;

private:
    std::unique_ptr<AIComponent> aiComponent;
};

#pragma once

#include <string>
#include <vector>

#include "Colors.hpp"
#include "Engine.hpp"
#include "FlagEnums.hpp"
#include "PhysicsEntity.hpp"
#include "Gun.hpp"
#include "Vec2d.hpp"

struct GameWorld;
class PhysicsComponent;

class Ship : public PhysicsEntity {
public:
    Engine engine;
    Gun gun;

    Ship(const Ship&) = delete;
    Ship & operator=(const Ship&) = delete;

    Vec2d nose() const;

protected:
    Ship(EntityFlag new_type, GameWorld *new_gameWorld, Vec2d pos,
         std::vector<Vec2d> shape, SdlColor color, double scale,
         double power, double turnSpeed,
         double shotPower,
         PhysicsComponent *new_physicsComponent);
};

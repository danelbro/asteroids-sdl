#pragma once

#include <vector>

#include "Colors.hpp"
#include "Engine.hpp"
#include "Gun.hpp"
#include "PhysicsEntity.hpp"
#include "Vec2d.hpp"
#include "utility.hpp"

struct GameWorld;

class Ship : public PhysicsEntity {
public:
    virtual ~Ship() = default;
    Ship(const Ship&) = delete;
    Ship& operator=(const Ship&) = delete;

    Vec2d nose() const { return m_fillShape.at(0); }

    Engine engine;
    Gun gun;
protected:
    Ship(utl::EntityFlag new_type, GameWorld& new_gameWorld, Vec2d pos,
         std::vector<Vec2d> shape, SdlColor color, double scale,
         double power, double turnSpeed, double shotPower, double mass,
         double cooldown);
};

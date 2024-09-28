#pragma once

#include <vector>

#include "Engine.hpp"
#include "flags.hpp"
#include "Gun.hpp"
#include "PhysicsEntity.hpp"
#include "SDL_Interface.hpp"
#include "utility.hpp"

struct GameWorld;
struct Vec2d;

class Ship : public PhysicsEntity {
public:
    virtual ~Ship() = default;
    Ship(const Ship&) = default;
    Ship& operator=(const Ship&) = delete;

    const Vec2d& nose() const { return m_fillShape.at(0); }

    Engine engine;
    Gun gun;
protected:
    Ship(const utl::EntityFlag& new_type, GameWorld& new_gameWorld,
         const Vec2d& pos, const std::vector<Vec2d>& shape,
         const utl::Colour& color, const double& scale, const double& power,
         const double& turnSpeed, const double& shotPower, const double& mass,
         const double& cooldown);
};

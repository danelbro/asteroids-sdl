#pragma once

#include <vector>

#include "PhysicsEntity.hpp"
#include "SDL_Interface.hpp"
#include "Vec2d.hpp"

struct GameWorld;

class PhysicsComponent;

class Asteroid : public PhysicsEntity {
public:
    Asteroid(GameWorld& new_gameWorld, const Vec2d& pos,
             const std::vector<Vec2d>& shape, const utl::Colour& color,
             const double& scale, const double& mass, const double& impulse,
             const double& angle);
};

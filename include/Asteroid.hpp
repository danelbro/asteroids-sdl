#pragma once

#include "utl_GameWorld.hpp"
#include "utl_PhysicsEntity.hpp"
#include "utl_SDLInterface.hpp"
#include "utl_Vec2d.hpp"

#include <vector>

class Asteroid : public utl::VecGraphPhysEnt {
public:
    Asteroid(utl::GameWorld& new_gameWorld, const utl::Vec2d& pos,
             const std::vector<utl::Vec2d>& shape, const utl::Colour& color,
             const double& scale, const double& mass, const double& impulse,
             const double& angle);
};

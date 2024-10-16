#pragma once

#include "Engine.hpp"
#include "Gun.hpp"
#include "flags.hpp"

#include <utl_GameWorld.hpp>
#include <utl_PhysicsEntity.hpp>
#include <utl_SDLInterface.hpp>
#include <utl_Vec2d.hpp>
#include <vector>

class Ship : public utl::VecGraphPhysEnt {
public:
    virtual ~Ship() = default;
    Ship(const Ship&) = default;
    Ship& operator=(const Ship&) = delete;

    const utl::Vec2d& nose() const { return m_collider.at(0); }

    Engine engine;
    Gun gun;

protected:
    Ship(const ENTITY_FLAG& new_type, utl::GameWorld& new_gameWorld,
         const utl::Vec2d& pos, const std::vector<utl::Vec2d>& shape,
         const utl::Colour& color, const double& scale, const double& power,
         const double& turnSpeed, const double& shotPower, const double& mass,
         const double& cooldown);
};

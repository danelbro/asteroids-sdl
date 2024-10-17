#include "Ship.hpp"

#include "Engine.hpp"
#include "Gun.hpp"
#include "flags.hpp"

#include <utl_GameWorld.hpp>
#include <utl_VecGraphPhysEnt.hpp>
#include <utl_Vec2d.hpp>
#include <utl_utility.hpp>

Ship::Ship(const ENTITY_FLAG& new_type, utl::GameWorld& new_gameWorld,
           const utl::Vec2d& pos, const std::vector<utl::Vec2d>& shape,
           const utl::Colour& color, const double& scale, const double& power,
           const double& turnSpeed, const double& shotPower, const double& mass,
           const double& cooldown)
    : utl::VecGraphPhysEnt{ENTITY_MAP[new_type],
                           new_gameWorld,
                           pos,
                           shape,
                           color,
                           scale,
                           mass,
                           true,
                           false},
      engine{*this, power, turnSpeed}, gun{*this, shotPower, cooldown}
{}

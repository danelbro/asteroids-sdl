#include "Ship.hpp"

#include "Colors.hpp"
#include "Engine.hpp"
#include "flags.hpp"
#include "GameWorld.hpp"
#include "Gun.hpp"
#include "PhysicsEntity.hpp"
#include "Vec2d.hpp"
#include "utility.hpp"

Ship::Ship(const utl::EntityFlag& new_type, GameWorld& new_gameWorld,
           const Vec2d& pos, const std::vector<Vec2d>& shape,
           const utl::Colour& color, const double& scale,
           const double& power, const double& turnSpeed,
           const double& shotPower, const double& mass,
           const double& cooldown)
    : PhysicsEntity{ utl::entityMap[new_type], new_gameWorld, pos, shape,
                     color, scale, mass },
      engine{ *this, power, turnSpeed },
      gun{ *this, shotPower, cooldown }
{}

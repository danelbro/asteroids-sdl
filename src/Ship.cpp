#include "Ship.hpp"

#include "Colors.hpp"
#include "Engine.hpp"
#include "GameWorld.hpp"
#include "Gun.hpp"
#include "PhysicsEntity.hpp"
#include "Vec2d.hpp"
#include "utility.hpp"

Ship::Ship(utl::EntityFlag new_type, GameWorld& new_gameWorld, Vec2d pos,
           std::vector<Vec2d> shape, SdlColor color, double scale,
           double power, double turnSpeed, double shotPower, double mass,
           double cooldown)
    : PhysicsEntity{ new_type, new_gameWorld, pos, shape,
                     color, scale, mass },
      engine{ *this, power, turnSpeed },
      gun{ *this, shotPower, cooldown }
{}

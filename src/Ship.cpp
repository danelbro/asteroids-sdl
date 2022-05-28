#include "../inc/Ship.hpp"

#include "../inc/Engine.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/Gun.hpp"
#include "../inc/PhysicsComponent.hpp"

Ship::Ship(GameWorld *new_gameWorld, Vec2d pos,
           std::vector<Vec2d> shape, SdlColor color, double scale,
           double power, double turnSpeed,
           double shotPower,
           PhysicsComponent *new_physicsComponent)
    : Entity{ new_gameWorld, pos, shape, color, scale },
      engine(this, power, turnSpeed),
      gun(this, shotPower),
      physicsComponent{ new_physicsComponent }
{}

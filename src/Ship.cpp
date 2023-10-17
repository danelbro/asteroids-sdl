#include "../inc/Ship.hpp"

#include "../inc/Engine.hpp"
#include "../inc/FlagEnums.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/Gun.hpp"
#include "../inc/PhysicsComponent.hpp"
#include "../inc/Vec2d.hpp"

Ship::Ship(EntityFlag new_type, GameWorld* new_gameWorld, Vec2d pos,
    std::vector<Vec2d> shape, SdlColor color, double scale, double power, 
    double turnSpeed, double shotPower, PhysicsComponent* new_physicsComponent)
    : PhysicsEntity{ new_type, new_gameWorld, pos, shape, 
    color, scale, new_physicsComponent },
    engine(this, power, turnSpeed),
    gun(this, shotPower)
{}
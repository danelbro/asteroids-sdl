#include "../inc/Asteroid.hpp"

#include <vector>

#include <SDL.h>

#include "../inc/Colors.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/FlagEnums.hpp"
#include "../inc/PhysicsComponent.hpp"
#include "../inc/Vec2d.hpp"

Asteroid::Asteroid(GameWorld& new_gameWorld, Vec2d pos,
    std::vector<Vec2d> shape, SdlColor color, double scale,
    PhysicsComponent *new_physicsComponent, double impulse, double angle,
    double new_radius)
    : PhysicsEntity(EntityFlag::ASTEROID, new_gameWorld, pos, shape,
        color, scale, new_physicsComponent),
    radius{ new_radius }
{
    physicsComponent->setOwner(this);
    physicsComponent->setFrameImpulse(impulse / scale);
    physicsComponent->setAngle(angle);
    // fill = true;
}

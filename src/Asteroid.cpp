#include "../inc/Asteroid.hpp"

#include <cmath>
#include <ctime>
#include <random>
#include <vector>

#include <SDL.h>

#include "../inc/GameWorld.hpp"
#include "../inc/FlagEnums.hpp"
#include "../inc/PhysicsComponent.hpp"
#include "../inc/Vec2d.hpp"

Asteroid::Asteroid(GameWorld *new_gameWorld, Vec2d pos, std::vector<Vec2d> shape, SdlColor color,
    double scale, PhysicsComponent *new_physicsComponent,
    double impulse, double angle, double new_radius)
    : PhysicsEntity(ASTEROID, new_gameWorld, pos, shape, color, scale, new_physicsComponent),
    radius{ new_radius }
{
    physicsComponent->setOwner(this);
    physicsComponent->setFrameImpulse(impulse);
    physicsComponent->setAngle(angle);
    // fill = true;
}
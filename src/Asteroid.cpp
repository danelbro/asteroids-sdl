#include "../inc/Asteroid.hpp"

#include <vector>

#include <SDL.h>

#include "../inc/Colors.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/PhysicsEntity.hpp"
#include "../inc/PhysicsComponent.hpp"
#include "../inc/Vec2d.hpp"
#include "../inc/utility.hpp"

Asteroid::Asteroid(GameWorld& new_gameWorld, Vec2d pos,
    std::vector<Vec2d> shape, SdlColor color, double scale,
    double mass, double impulse, double angle, double new_radius)
    : PhysicsEntity{ utl::EntityFlag::ASTEROID, new_gameWorld, pos, shape,
        color, scale, mass }, radius{ new_radius }
{
    physicsComponent.setFrameImpulse(impulse / scale);
    physicsComponent.setAngle(angle);
    // fill = true;
}

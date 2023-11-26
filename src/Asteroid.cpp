#include "Asteroid.hpp"

#include <vector>

#include "SDL_Interface.hpp"

#include "Colors.hpp"
#include "GameWorld.hpp"
#include "PhysicsEntity.hpp"
#include "PhysicsComponent.hpp"
#include "Vec2d.hpp"
#include "utility.hpp"

Asteroid::Asteroid(GameWorld& new_gameWorld, const Vec2d& pos,
                   const std::vector<Vec2d>& shape, const utl::Colour& color,
                   const double& scale, const double& mass,
                   const double& impulse, const double& angle,
                   const double& new_radius)
    : PhysicsEntity{ utl::EntityFlag::ASTEROID, new_gameWorld, pos, shape,
        color, scale, mass }, radius{ new_radius }
{
    physicsComponent.setFrameImpulse(impulse / scale);
    physicsComponent.setAngle(angle);
    // fill = true;
}

#include "Asteroid.hpp"

#include "flags.hpp"

#include <utl_GameWorld.hpp>
#include <utl_SDLInterface.hpp>
#include <utl_Vec2d.hpp>
#include <utl_VecGraphPhysComp.hpp>
#include <utl_VecGraphPhysEnt.hpp>
#include <utl_utility.hpp>
#include <vector>

Asteroid::Asteroid(utl::GameWorld& new_gameWorld, const utl::Vec2d& pos,
                   const std::vector<utl::Vec2d>& shape,
                   const utl::Colour& color, const double& scale,
                   const double& mass, const double& impulse,
                   const double& angle, bool wrap, bool fill)
    : utl::VecGraphPhysEnt{ENTITY_MAP.at(ENTITY_FLAG::ASTEROID),
                           new_gameWorld,
                           pos,
                           shape,
                           color,
                           scale,
                           mass,
                           wrap,
                           fill}
{
    physicsComponent.setFrameImpulse(impulse / scale);
    physicsComponent.set_facing_angle(angle);
    LOG("Constructed Asteroid\n");
}

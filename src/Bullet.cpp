#include "Bullet.hpp"

#include "flags.hpp"

#include <utl_GameWorld.hpp>
#include <utl_VecGraphPhysComp.hpp>
#include <utl_VecGraphPhysEnt.hpp>
#include <utl_SDLInterface.hpp>
#include <utl_Vec2d.hpp>
#include <utl_utility.hpp>
#include <vector>

Bullet::Bullet(utl::GameWorld& new_gameWorld, const utl::Vec2d& pos,
               const std::vector<utl::Vec2d>& shape, const utl::Colour& color,
               const double& scale, const double& mass, const double& lifespan,
               const double& angle, const double& power,
               const ENTITY_FLAG& flag, bool wrap, bool fill)
    : utl::VecGraphPhysEnt{ENTITY_MAP[flag],
                           new_gameWorld,
                           pos,
                           shape,
                           color,
                           scale,
                           mass,
                           wrap,
                           fill},
      m_lifespan{lifespan}, m_wayward{true}
{
    physicsComponent.setAngle(angle);
    physicsComponent.setFrameImpulse(power);
}

void Bullet::update(double, double dt)
{
    update_shapes();

    m_alive += dt;

    if (m_alive >= m_lifespan) {
        m_killMe = true;
    }
}

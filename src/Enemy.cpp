#include "Enemy.hpp"

#include "AIComponent.hpp"
#include "PhysicsManager.hpp"
#include "Ship.hpp"
#include "flags.hpp"
#include "utl_random.hpp"

#include <utl_GameWorld.hpp>
#include <utl_SDLInterface.hpp>
#include <utl_Vec2d.hpp>
#include <utl_random.hpp>
#include <vector>

Enemy::Enemy(utl::GameWorld& new_gameworld, const utl::Vec2d& pos,
             const std::vector<utl::Vec2d>& shape, const utl::Colour& colour,
             const double& scale, const double& power, const double& turnSpeed,
             const double& minVel, const double& maxVel,
             const double& shotPower, const double& mass,
             const double& cooldown, Player* plr, PhysicsManager& physMan,
             utl::RNG& rng)
    : Ship{ENTITY_FLAG::ENEMY,
           new_gameworld,
           pos,
           shape,
           colour,
           scale,
           power,
           turnSpeed,
           shotPower,
           mass,
           cooldown},
      m_minVel{minVel}, m_maxVel{maxVel}, m_aiComponent{*this, physMan, rng},
      m_plr{plr}, m_isScreenClear{false}
{
    LOG("Constructed Enemy\n");
}

void Enemy::update(double t, double dt)
{
    gun.check_cooldown(dt);
    m_aiComponent.update(t, dt, m_plr, m_isScreenClear);
    update_shapes();
}

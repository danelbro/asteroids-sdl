#include "../inc/Gun.hpp"

#include "../inc/GameWorld.hpp"
#include "../inc/PhysicsComponent.hpp"
#include "../inc/PhysicsManager.hpp"
#include "../inc/Ship.hpp"
#include "../inc/Vec2d.hpp"

void Gun::fire(PhysicsManager& physMan)
{
    if (!m_fired)
        physMan.make_bullet(m_owner.nose(), m_shotPower,
                            m_owner.physicsComponent.angle());

    m_fired = true;
}

void Gun::check_cooldown(double dt)
{
    if (!m_fired) return;

    m_cooldownTimer += dt;
    if (m_cooldownTimer < m_cooldown) return;

    m_fired = false;
    m_cooldownTimer = 0.0;
}

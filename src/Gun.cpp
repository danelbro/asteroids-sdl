﻿#include "Gun.hpp"

#include "PhysicsComponent.hpp"
#include "PhysicsManager.hpp"
#include "Ship.hpp"

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

    reset();
}

void Gun::reset()
{
    m_fired = false;
    m_cooldownTimer = 0.0;
}

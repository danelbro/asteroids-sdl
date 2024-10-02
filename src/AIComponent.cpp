﻿#include "AIComponent.hpp"

#include <cmath>
#include <random>

#include "Enemy.hpp"
#include "PhysicsManager.hpp"
#include "Player.hpp"
#include "Vec2d.hpp"

static double genRandAngle(std::mt19937& rng);

AIComponent::AIComponent(Enemy& new_owner, PhysicsManager& physMan, std::mt19937& rng)
    : m_owner{ new_owner }, m_physMan{ physMan }, m_rng{ rng },
      m_turnTimeLower{ 1.5 }, m_turnTimeUpper{ 3.0 },
      m_turnTimeDist{ m_turnTimeLower, m_turnTimeUpper },
      m_turnTime{ m_turnTimeDist(m_rng) }, m_timeSinceTurn{ 0.0 },
      m_targetAngle{ genRandAngle(m_rng) }, m_enginePulse{ 1.0 },
      m_timeSincePulse{ 0.0 }
{}

static double genMoveTime(std::uniform_real_distribution<double> dist,
                          std::mt19937& rng)
{
    return dist(rng);
}

static double genRandAngle(std::mt19937& rng)
{
    std::uniform_real_distribution<double> angleDist{ 0.0, 360.0 };

    return angleDist(rng);
}

static double findPlayerRayAngle(const Vec2d& current_pos, const Vec2d& plr_pos)
{
    Vec2d ray{ plr_pos - current_pos };
    return ray.angleDeg();
}

void AIComponent::update(double t, double dt, Player*)
{
    const double& ourAngle{ m_owner.physicsComponent.angle() };
    m_timeSinceTurn += dt;
    m_timeSincePulse += dt;

    bool isTooFast{ m_owner.physicsComponent.velocity().magnitude()
                    > m_owner.maxVel()};
    bool isTooSlow{ m_owner.physicsComponent.velocity().magnitude()
                    < m_owner.minVel() };

    if (isTooSlow) m_owner.engine.on();

    if (m_targetAngle < ourAngle - 5.0)
        m_owner.engine.turnLeft(dt);
    else if (m_targetAngle > ourAngle + 5.0)
        m_owner.engine.turnRight(dt);

    if (m_timeSinceTurn > m_turnTime) {
        m_timeSinceTurn = 0.0;
        m_targetAngle = genRandAngle(m_rng);
        m_turnTime = genMoveTime(m_turnTimeDist, m_rng);

        // start a new engine pulse
        m_timeSincePulse = 0.0;
    }

    if (m_timeSincePulse <= m_enginePulse) {
        m_owner.engine.on();
    }
    else if (m_timeSincePulse > m_enginePulse && !(isTooSlow))
        m_owner.engine.off();

    if (isTooFast) m_owner.engine.off();

    if (std::abs(m_owner.physicsComponent.velocity().angleDeg()
                 - m_owner.physicsComponent.facing().angleDeg()) >= 90.0 )
        m_owner.engine.on();

    m_owner.gun.fire(m_physMan);
}

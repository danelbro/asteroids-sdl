#include "AIComponent.hpp"

#include "Enemy.hpp"
#include "PhysicsManager.hpp"
#include "Player.hpp"
#include "Vec2d.hpp"

AIComponent::AIComponent(Enemy& new_owner, PhysicsManager& physMan)
    : m_owner{ new_owner }, m_physMan{ physMan }
{}

static double findPlayerRayAngle(const Vec2d& current_pos, Player* plr)
{
    Vec2d ray{ plr->getPos() - current_pos };
    return ray.angleDeg();
}

void AIComponent::update(double t, double dt, Player* plr)
{
    if (!plr) {
        random_update(t, dt);
        return;
    }
    double ourAngle{ m_owner.physicsComponent.angle() };
    double angleToPlayer{ findPlayerRayAngle(m_owner.getPos(), plr) };

    if (static_cast<int>(ourAngle) == static_cast<int>(angleToPlayer)
        && m_owner.physicsComponent.velocity().magnitude() < m_owner.maxVel())
        m_owner.engine.on();
    else if (ourAngle > angleToPlayer)
        m_owner.engine.turnLeft(dt);
    else
        m_owner.engine.turnRight(dt);

    if (m_owner.physicsComponent.velocity().magnitude() >= m_owner.maxVel())
        m_owner.engine.off();

    m_owner.gun.fire(m_physMan);
}

void AIComponent::random_update(double, double dt)
{
    m_owner.engine.turnLeft(dt);
    // m_owner.gun.fire(m_physMan);
}

#include "AIComponent.hpp"

#include "Enemy.hpp"
#include "PhysicsManager.hpp"
#include "Player.hpp"
#include "Vec2d.hpp"

AIComponent::AIComponent(Enemy& new_owner, PhysicsManager& physMan)
    : m_owner{ new_owner }, m_physMan(physMan)
{}

void AIComponent::update(double t, double dt, Player* plr)
{
    if (!plr) {
        random_update(t, dt);
        return;
    }
    Vec2d vecToPlayer{plr->getPos() - m_owner.getPos()};
    vecToPlayer.normalizeInPlace();
    double angleToPlayer =
        m_owner.physicsComponent.facing().normalize().angleTo(vecToPlayer);

    if (angleToPlayer == 0)
        ;
    else if (angleToPlayer < M_PI / 2)
        m_owner.engine.turnLeft(dt);
    else
        m_owner.engine.turnRight(dt);

    if (m_owner.physicsComponent.velocity().magnitude() < m_owner.maxVel())
        m_owner.engine.on();
    else
        m_owner.engine.off();

    m_owner.gun.fire(m_physMan);
}

void AIComponent::random_update(double, double dt)
{
    m_owner.engine.turnLeft(dt);
    m_owner.gun.fire(m_physMan);
}

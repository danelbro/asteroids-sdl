#include "AIComponent.hpp"

#include "Enemy.hpp"
#include "GameWorld.hpp"
#include "PhysicsManager.hpp"
#include "Player.hpp"
#include "Vec2d.hpp"

AIComponent::AIComponent(Enemy& new_owner, PhysicsManager& physMan, std::mt19937& rng)
    : m_owner{ new_owner }, m_physMan{ physMan }, m_rng{ rng },
    turnTime{ 0.5 }, sinceTurn{ 0.0 }
{}

static double findPlayerRayAngle(const Vec2d& current_pos, const Vec2d& plr_pos)
{
    Vec2d ray{ plr_pos - current_pos };
    return ray.angleDeg();
}

static Vec2d findRandomDistantPos(std::mt19937& rng,
    Entity& distant, double distance, int w, int h)
{
    Vec2d new_pos{ };
    bool isTooClose{ true };
    do {
        new_pos = utl::randomPos(rng, w, h);

        Vec2d distanceToPlayer{ new_pos - distant.pos() };
        if (distanceToPlayer.magnitude() > distance)
            isTooClose = false;
    } while (isTooClose);
    return new_pos;
}

void AIComponent::update(double t, double dt, Player* plr)
{
    sinceTurn += dt;

    if (sinceTurn > turnTime) {
        sinceTurn = 0.0;
        Vec2d plr_pos{};
        if (!plr)
            plr_pos = utl::randomPos(m_rng, m_owner.gameWorld.screen.w,
                m_owner.gameWorld.screen.h);
        else
            plr_pos = plr->getPos();

        double ourAngle{ m_owner.physicsComponent.angle() };
        double angleToPlayer{ findPlayerRayAngle(m_owner.getPos(), plr_pos) };

        if (ourAngle > angleToPlayer)
            m_owner.engine.turnLeft(dt);
        else
            m_owner.engine.turnRight(dt);
    }

    if (m_owner.physicsComponent.velocity().magnitude()
        < (m_owner.physicsComponent.facing() * m_owner.maxVel()).magnitude())
        m_owner.engine.on();
    else
        m_owner.engine.off();

    m_owner.gun.fire(m_physMan);
}
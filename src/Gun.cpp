#include "../inc/Gun.hpp"

#include "../inc/GameWorld.hpp"
#include "../inc/PhysicsComponent.hpp"
#include "../inc/PhysicsManager.hpp"
#include "../inc/Ship.hpp"
#include "../inc/Vec2d.hpp"

void Gun::fire(PhysicsManager& physMan)
{
    Vec2d origin{ owner.nose() };
    double angle{ owner.physicsComponent.angle() };

    physMan.make_bullet(origin, m_shotPower, angle);

    fired = true;
}

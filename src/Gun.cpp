#include "../inc/Gun.hpp"

#include <iostream>

#include "../inc/EntityManager.hpp"
#include "../inc/Vec2d.hpp"

void Gun::fire(EntityManager *entMan)
{
    Vec2d origin{ owner->nose() };
    Vec2d angle{ owner->physicsComponent->angle() };

    entMan->make_bullet(origin, m_shotPower, angle);
}

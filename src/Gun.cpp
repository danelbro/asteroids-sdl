#include "../inc/Gun.hpp"

#include <iostream>

#include "../inc/EntityManager.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/Ship.hpp"
#include "../inc/Vec2d.hpp"

void Gun::fire(GameWorld *new_GameWorld, EntityManager *entMan, Ship *firingShip)
{
    Vec2d origin{ owner->nose() };
    double angle{ owner->physicsComponent->facing().angleDeg() };

    entMan->make_bullet(new_GameWorld, origin, m_shotPower, angle, firingShip);

    fired = true;
}

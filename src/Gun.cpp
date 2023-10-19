#include "../inc/Gun.hpp"

#include <iostream>

#include "../inc/GameWorld.hpp"
#include "../inc/PhysicsComponent.hpp"
#include "../inc/PhysicsManager.hpp"
#include "../inc/Ship.hpp"
#include "../inc/Vec2d.hpp"

void Gun::fire(GameWorld& new_GameWorld, PhysicsManager& physMan, 
    Ship& firingShip)
{
    Vec2d origin{ owner.nose() };
    double angle{ owner.physicsComponent->angle() };

    physMan.make_bullet(new_GameWorld, origin, 
                        m_shotPower, angle, firingShip);

    fired = true;
}

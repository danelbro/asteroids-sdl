#include "../inc/Bullet.hpp"

#include <vector>

#include <SDL.h>

#include "../inc/FlagEnums.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/PhysicsComponent.hpp"
#include "../inc/Ship.hpp"
#include "../inc/Vec2d.hpp"

Bullet::Bullet(GameWorld* new_gameWorld, Vec2d pos, std::vector<Vec2d> shape,
	SdlColor color, double scale,
	PhysicsComponent* new_physicsComponent, Ship* new_owner)
	: PhysicsEntity{BULLET, new_gameWorld, pos, shape, color, scale, new_physicsComponent},
	owner{ new_owner }
{
    physicsComponent->setOwner(this);
}
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
	PhysicsComponent* new_physicsComponent, Ship* new_owner, double lifespan)
	: PhysicsEntity{ BULLET, new_gameWorld, pos, shape, color, scale, new_physicsComponent },
	owner{ new_owner }, m_lifespan{ lifespan }
{
    physicsComponent->setOwner(this);
	fill = true;
}

void Bullet::update(double t, double dt)
{
	update_shapes();

	m_alive += dt;

	if (m_alive >= m_lifespan)
	{
		kill_me = true;
		if (physicsComponent) {
			physicsComponent->setOwner(nullptr);
			physicsComponent = nullptr;
		}
	}
}

#include "../inc/Bullet.hpp"

#include <vector>

#include <SDL.h>

#include "../inc/FlagEnums.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/PhysicsComponent.hpp"
#include "../inc/PhysicsEntity.hpp"
#include "../inc/Ship.hpp"
#include "../inc/Vec2d.hpp"

Bullet::Bullet(GameWorld& new_gameWorld, Vec2d pos, std::vector<Vec2d> shape,
               SdlColor color, double scale, double mass, double lifespan,
               double angle, double power)
	: PhysicsEntity{ EntityFlag::BULLET, new_gameWorld, pos, shape, color,
                     scale, mass }, m_lifespan{ lifespan }
{
    physicsComponent.setAngle(angle);
    physicsComponent.setFrameImpulse(power);
	fill = true;
}

void Bullet::update(double, double dt)
{
	update_shapes();

	m_alive += dt;

	if (m_alive >= m_lifespan)
		kill_me = true;
}

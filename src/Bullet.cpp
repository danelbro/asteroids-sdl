#include "Bullet.hpp"

#include <vector>

#include <SDL.h>

#include "GameWorld.hpp"
#include "PhysicsComponent.hpp"
#include "PhysicsEntity.hpp"
#include "Ship.hpp"
#include "Vec2d.hpp"
#include "utility.hpp"

Bullet::Bullet(GameWorld& new_gameWorld, Vec2d pos, std::vector<Vec2d> shape,
               SdlColor color, double scale, double mass, double lifespan,
               double angle, double power)
	: PhysicsEntity{ utl::EntityFlag::BULLET, new_gameWorld, pos, shape, color,
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

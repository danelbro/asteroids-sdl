#include "Bullet.hpp"

#include <vector>

#include "SDL_Interface.hpp"

#include "flags.hpp"
#include "GameWorld.hpp"
#include "PhysicsComponent.hpp"
#include "PhysicsEntity.hpp"
#include "Ship.hpp"
#include "Vec2d.hpp"
#include "utility.hpp"

Bullet::Bullet(GameWorld& new_gameWorld, const Vec2d& pos,
			   const std::vector<Vec2d>& shape, const utl::Colour& color,
			   const double& scale, const double& mass,
			   const double& lifespan, const double& angle,
			   const double& power, const utl::EntityFlag& flag)
	: PhysicsEntity{ utl::entityMap[flag], new_gameWorld, pos, shape, color,
                     scale, mass }, m_lifespan{ lifespan }, m_wayward{ true }
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

#include "Enemy.hpp"

#include <vector>

#include <SDL.h>

#include "AIComponent.hpp"
#include "Colors.hpp"
#include "GameWorld.hpp"
#include "PhysicsManager.hpp"
#include "Ship.hpp"
#include "Vec2d.hpp"

Enemy::Enemy(GameWorld& new_gameworld, Vec2d pos, std::vector<Vec2d> shape,
             SdlColor colour, double scale, double power, double turnSpeed,
             double maxVel, double shotPower, double mass, double cooldown,
             Player* plr, PhysicsManager& physMan)
    : Ship{ utl::EntityFlag::ENEMY, new_gameworld, pos, shape, colour, scale,
            power, turnSpeed, shotPower, mass, cooldown },
      m_maxVel{ maxVel }, m_aiComponent{ *this, physMan }, m_plr{ plr }
{}

void Enemy::update(double t, double dt)
{
    gun.check_cooldown(dt);
    m_aiComponent.update(t, dt, m_plr);
    update_shapes();
}

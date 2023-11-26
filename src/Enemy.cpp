#include "Enemy.hpp"

#include <vector>

#include "SDL_Interface.hpp"

#include "AIComponent.hpp"
#include "Colors.hpp"
#include "GameWorld.hpp"
#include "PhysicsManager.hpp"
#include "Ship.hpp"
#include "Vec2d.hpp"

Enemy::Enemy(GameWorld& new_gameworld, const Vec2d& pos,
             const std::vector<Vec2d>& shape, const utl::Colour& colour,
             const double& scale, const double& power,
             const double& turnSpeed, const double& maxVel,
             const double& shotPower, const double& mass,
             const double& cooldown, Player* plr, PhysicsManager& physMan)
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

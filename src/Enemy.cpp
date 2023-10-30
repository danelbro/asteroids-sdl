#include "../inc/Enemy.hpp"

#include <stdexcept>
#include <memory>
#include <vector>

#include <SDL.h>

#include "../inc/AIComponent.hpp"
#include "../inc/Colors.hpp"
#include "../inc/FlagEnums.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/Ship.hpp"
#include "../inc/PhysicsComponent.hpp"
#include "../inc/Vec2d.hpp"

Enemy::Enemy(GameWorld& new_gameworld, Vec2d pos, std::vector<Vec2d> shape,
             SdlColor colour, double scale, double power, double turnSpeed,
             double shotPower, double mass, double cooldown)
    : Ship{ EntityFlag::ENEMY, new_gameworld, pos, shape, colour, scale, power,
            turnSpeed, shotPower, mass, cooldown },
    aiComponent{ *this }
{}

void Enemy::update(double, double dt)
{
    gun.check_cooldown(dt);
    update_shapes();
}

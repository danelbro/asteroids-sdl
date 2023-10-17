#include "../inc/Enemy.hpp"

#include <stdexcept>
#include <memory>
#include <vector>

#include <SDL.h>

#include "../inc/AIComponent.hpp"
#include "../inc/FlagEnums.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/Ship.hpp"
#include "../inc/Vec2d.hpp"

Enemy::Enemy(GameWorld* new_gameworld, Vec2d pos, std::vector<Vec2d> shape,
    SdlColor colour, double scale, double power, double turnSpeed,
    double shotPower, PhysicsComponent* new_physicsComponent)
    : Ship{ EntityFlag::ENEMY, new_gameworld, pos, shape, colour, scale, power,
    turnSpeed, shotPower, new_physicsComponent },
    aiComponent{ nullptr }
{
    aiComponent = std::make_unique<AIComponent>();
    if (!aiComponent)
        throw std::runtime_error("failed to create AIComponent");

    aiComponent->setOwner(this);
    physicsComponent->setOwner(this);
}

void Enemy::update(double, double)
{
    update_shapes();
}
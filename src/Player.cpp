#include "../inc/Player.hpp"

#include <vector>

#include <SDL.h>

#include "../inc/Colors.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/PhysicsComponent.hpp"
#include "../inc/Ship.hpp"
#include "../inc/Vec2d.hpp"

Player::Player(GameWorld *new_gameWorld, Vec2d pos,
               std::vector<Vec2d> shape, SdlColor color, double scale,
               double power, double turnSpeed,
               double shotPower,
               PhysicsComponent* new_physicsComponent,
               double warpTimer, int new_lives)
    : Ship{ new_gameWorld, pos, shape, color, scale,
    power, turnSpeed, shotPower, new_physicsComponent},
      hyperdrive{ this, warpTimer }, isVisible{ true },
      isControllable{ true }, lives{ new_lives }
{
    physicsComponent->setOwner(this);
}
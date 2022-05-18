#include "../inc/Ship.hpp"

#include "../inc/Engine.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/Gun.hpp"
#include "../inc/PhysicsComponent.hpp"

Ship::Ship(std::string path, SDL_Renderer *renderer,
           GameWorld *new_gameWorld,
           double power, double turnSpeed,
           double shotPower,
           PhysicsComponent *new_physicsComponent)
    : Entity{ path, renderer, new_gameWorld },
      engine(this, power, turnSpeed),
      gun(this, shotPower),
      physicsComponent{ new_physicsComponent }
{}

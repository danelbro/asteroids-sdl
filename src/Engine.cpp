#include "../inc/Engine.hpp"

#include "../inc/Ship.hpp"
#include "../inc/PhysicsComponent.hpp"

Engine::Engine(Ship *newOwner, double newPower, double newTurnSpeed)
    : owner(newOwner), power(newPower), turnSpeed(newTurnSpeed)
{}

void Engine::on()
{
    owner->physicsComponent->setFrameImpulse(power);
}

void Engine::off()
{
    owner->physicsComponent->setFrameImpulse(0.0);
}

void Engine::turnLeft()
{
    owner->physicsComponent->turn(turnSpeed * -1);
}

void Engine::turnRight()
{
    owner->physicsComponent->turn(turnSpeed);
}

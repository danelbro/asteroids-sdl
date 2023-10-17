#include "../inc/Engine.hpp"

#include "../inc/Ship.hpp"
#include "../inc/PhysicsComponent.hpp"

Engine::Engine(Ship *newOwner, double newPower, double newTurnSpeed)
    : owner(newOwner), power(newPower), turnSpeed(newTurnSpeed)
{}

void Engine::on()
{
    if (owner)
        owner->physicsComponent->setFrameImpulse(power);
}

void Engine::off()
{
    if (owner)
        owner->physicsComponent->setFrameImpulse(0.0);
}

void Engine::turnLeft(double dt)
{
    if (owner)
        owner->physicsComponent->turn(turnSpeed * -1, dt);
}

void Engine::turnRight(double dt)
{
    if (owner)
        owner->physicsComponent->turn(turnSpeed, dt);
}

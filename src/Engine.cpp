#include "../inc/Engine.hpp"

#include "../inc/Ship.hpp"

Engine::Engine(Ship &newOwner, double newPower, double newTurnSpeed)
    : owner(newOwner), power(newPower), turnSpeed(newTurnSpeed)
{}

void Engine::on()
{
    owner.physicsComponent->setFrameAcceleration(power);
}

void Engine::off()
{
    owner.physicsComponent->setFrameAcceleration(0);
}

void Engine::turnLeft()
{
    owner.physicsComponent->setFrameTurn(turnSpeed * -1);
}

void Engine::turnRight()
{
    owner.physicsComponent->setFrameTurn(turnSpeed);
}

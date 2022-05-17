#include "../inc/Engine.hpp"

#include "../inc/Player.hpp"

Engine::Engine(Player &newOwner, double newPower, double newTurnSpeed)
    : owner(newOwner), power(newPower), turnSpeed(newTurnSpeed)
{}

void Engine::on()
{
    owner.set_accelerationMag(power);
}

void Engine::off()
{
    owner.set_accelerationMag(0);
}

void Engine::turnLeft()
{
    owner.set_turnAmount(turnSpeed * -1);
}

void Engine::turnRight()
{
    owner.set_turnAmount(turnSpeed);
}

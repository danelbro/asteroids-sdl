﻿#include "Engine.hpp"

#include "Ship.hpp"

#include <utl_SDLInterface.hpp>
#include <utl_VecGraphPhysComp.hpp>

Engine::Engine(Ship& newOwner, double newPower, double newTurnSpeed)
    : owner(newOwner), power(newPower), turnSpeed(newTurnSpeed)
{
    LOG("Constructed Engine\n");
}

void Engine::on()
{
    owner.physicsComponent.setFrameImpulse(power);
}

void Engine::off()
{
    owner.physicsComponent.setFrameImpulse(0.0);
}

void Engine::turnLeft(double dt)
{
    owner.physicsComponent.turn(turnSpeed * -1, dt);
}

void Engine::turnRight(double dt)
{
    owner.physicsComponent.turn(turnSpeed, dt);
}

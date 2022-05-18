#pragma once

#include <string>

#include "Engine.hpp"
#include "Entity.hpp"
#include "Gun.hpp"

struct GameWorld;
class PhysicsComponent;

class Ship : public Entity {
public:
    Engine engine;
    Gun gun;

    Ship(const Ship&) = delete;
    Ship & operator=(const Ship&) = delete;

    PhysicsComponent *physicsComponent;

    virtual void render(SDL_Renderer *renderer) = 0;

protected:
    Ship(std::string path, SDL_Renderer *renderer,
         GameWorld *new_gameWorld, double power, double turnSpeed,
         double shotPower,
         PhysicsComponent *new_physicsComponent);
};

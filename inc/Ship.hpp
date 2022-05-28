#pragma once

#include <string>
#include <vector>

#include "Colors.hpp"
#include "Engine.hpp"
#include "Entity.hpp"
#include "Gun.hpp"
#include "Vec2d.hpp"

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
    Ship(GameWorld *new_gameWorld, Vec2d pos,
         std::vector<Vec2d> shape, SdlColor color, double scale,
         double power, double turnSpeed,
         double shotPower,
         PhysicsComponent *new_physicsComponent);
};

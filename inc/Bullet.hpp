#pragma once

#include <SDL.h>

#include "Entity.hpp"
#include "PhysicsComponent.hpp"
#include "Player.hpp"

class Bullet : public Entity {
public:
    Bullet();

    PhysicsComponent *physicsComponent;

    void render(SDL_Renderer *renderer) override;

private:
    Player &owner;
};

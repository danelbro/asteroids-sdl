#pragma once

#include <SDL.h>

#include "Entity.hpp"
#include "PhysicsComponent.hpp"

class Asteroid : public Entity {
public:
    Asteroid();

    PhysicsComponent *physicsComponent;

    void render(SDL_Renderer *renderer) override;

};

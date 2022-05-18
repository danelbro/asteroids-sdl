#pragma once

#include "AIComponent.hpp"
#include "Ship.hpp"

class Enemy : public Ship {
public:
    Enemy();

    AIComponent *aiComponent;

    void render(SDL_Renderer *renderer) override;
};

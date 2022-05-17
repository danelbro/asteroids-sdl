#pragma once

#include "Entity.hpp"
#include "PhysicsComponent.hpp"

class Asteroid : public Entity {
public:
    Asteroid();

    PhysicsComponent *physicsComponent;

    void update() override;
    void render(int *renderer, double progress) override;

};

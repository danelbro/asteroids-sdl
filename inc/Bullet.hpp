#pragma once

#include "Entity.hpp"
#include "PhysicsComponent.hpp"
#include "Player.hpp"

class Bullet : public Entity {
public:
    Bullet();

    PhysicsComponent *physicsComponent;

    void update() override;
    void render(int *renderer, double progress) override;

private:
    Player &owner;

};

#pragma once

#include <vector>

#include <SDL.h>

#include "PhysicsEntity.hpp"

struct Gameworld;
struct Vec2d;

class Ship;
class PhysicsComponent;

class Bullet : public PhysicsEntity {
public:
    Bullet(GameWorld* new_gameWorld, Vec2d pos, std::vector<Vec2d> shape,
        SdlColor color, double scale, PhysicsComponent* new_physicsComponent,
        Ship* new_owner, double lifespan);
    
    void update(double t, double dt) override;

private:
    Ship *owner;
    double m_lifespan;
    double m_alive{ 0.0 };
};

#pragma once

#include <SDL.h>
#include <vector>
#include <random>

#include "Colors.hpp"
#include "PhysicsEntity.hpp"
#include "Vec2d.hpp"

struct GameWorld;

class PhysicsComponent;

class Asteroid : public PhysicsEntity {
public:
    Asteroid(GameWorld& new_gameWorld, Vec2d pos, std::vector<Vec2d> shape,
        SdlColor color, double scale, PhysicsComponent* new_physicsComponent,
        double impulse, double angle, double new_radius);

    void update(double, double) override { update_shapes(); }

    double radius;
};

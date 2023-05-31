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
    Asteroid(GameWorld *new_gameWorld, Vec2d pos,
             std::vector<Vec2d> shape, SdlColor color,
             double scale, PhysicsComponent *new_physicsComponent,
             double impulseMin, double impulseMax,
             double new_radius, std::mt19937 &rng);

    Asteroid(const Asteroid&) = delete;
    Asteroid & operator=(const Asteroid&) = delete;

    double radius;
};

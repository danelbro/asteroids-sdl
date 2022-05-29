#pragma once

#include <SDL.h>
#include <vector>
#include <random>

#include "Colors.hpp"
#include "Entity.hpp"
#include "PhysicsComponent.hpp"
#include "Vec2d.hpp"

struct GameWorld;

class Asteroid : public Entity {
public:
    Asteroid(GameWorld *new_gameWorld, Vec2d pos,
             std::vector<Vec2d> shape, SdlColor color,
             double scale, PhysicsComponent *new_physicsComponent,
             double new_radius, std::mt19937 &rng);

    Asteroid(const Asteroid&) = delete;
    Asteroid & operator=(const Asteroid&) = delete;

    void render(SDL_Renderer *renderer) override;

    PhysicsComponent *physicsComponent;
    double radius;
};

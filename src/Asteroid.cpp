#include "../inc/Asteroid.hpp"

#include <cmath>
#include <ctime>
#include <random>
#include <vector>

#include <SDL.h>

#include "../inc/GameWorld.hpp"
#include "../inc/PhysicsComponent.hpp"
#include "../inc/Vec2d.hpp"

Asteroid::Asteroid(GameWorld *new_gameWorld, Vec2d pos,
                   std::vector<Vec2d> shape, SdlColor color,
                   double scale, PhysicsComponent *new_physicsComponent,
                   double impulseMin, double impulseMax,
                   double new_radius, std::mt19937 &rng)
    : PhysicsEntity(new_gameWorld, pos, shape, color, scale, new_physicsComponent),
      radius{ new_radius }
{
    physicsComponent->setOwner(this);

    std::uniform_real_distribution<double> impulseDist(impulseMin, impulseMax);
    physicsComponent->setFrameImpulse(impulseDist(rng));

    std::uniform_real_distribution<double> angleDist(0.0, 360.0);
    physicsComponent->setAngle(angleDist(rng));

    std::uniform_real_distribution<double> cragDist(-5.0, 5.0);
    int numPoints{ 13 };
    double sliceAngle{ (2 * M_PI / numPoints) };
    for (int i{ 0 }; i < numPoints; ++i)
        m_shape.push_back(Vec2d{std::sin(sliceAngle * i) * (radius + cragDist(rng)),
                                -std::cos(sliceAngle * i) * (radius + cragDist(rng))});
}
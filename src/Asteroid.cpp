#include "../inc/Asteroid.hpp"

#include <cmath>
#include <ctime>
#include <random>
#include <vector>

#include <SDL.h>

#include "../inc/Colors.hpp"
#include "../inc/DrawWrapLine.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/Vec2d.hpp"

Asteroid::Asteroid(GameWorld *new_gameWorld, Vec2d pos,
                   std::vector<Vec2d> shape, SdlColor color,
                   double scale, PhysicsComponent *new_physicsComponent,
                   double new_radius, std::mt19937 &rng)
    : Entity(new_gameWorld, pos, shape, color, scale),
      physicsComponent{ new_physicsComponent }, radius{ new_radius }
{
    physicsComponent->setOwner(this);

    std::uniform_real_distribution<double> impulseDist(50.0, 100.0);
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

void Asteroid::render(SDL_Renderer *renderer)
{
    SdlColor oldColor{ };
    SDL_GetRenderDrawColor(renderer,
                           &oldColor.r, &oldColor.g, &oldColor.b, &oldColor.a);
    SDL_SetRenderDrawColor(renderer,
                           m_color.r, m_color.g, m_color.b, m_color.a);

    std::vector<Vec2d> transShape{ };
    for (auto p : m_shape)
        transShape.push_back(p.rotate_deg(physicsComponent->angle()) * m_scale);

    for (unsigned i{ 0 }; i < transShape.size(); ++i) {
        if (i == transShape.size() - 1) {
            DrawWrapLine(renderer,
                         gameWorld->screen,
                         m_pos.x + transShape[i].x,
                         m_pos.y + transShape[i].y,
                         m_pos.x + transShape[0].x,
                         m_pos.y + transShape[0].y);
        }
        else {
            DrawWrapLine(renderer,
                         gameWorld->screen,
                         m_pos.x + transShape[i].x,
                         m_pos.y + transShape[i].y,
                         m_pos.x + transShape[i+1].x,
                         m_pos.y + transShape[i+1].y);
        }
    }

    SDL_SetRenderDrawColor(renderer,
                           oldColor.r, oldColor.g, oldColor.b, oldColor.a);
}

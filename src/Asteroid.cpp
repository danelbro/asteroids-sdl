#include "../inc/Asteroid.hpp"

#include <cmath>
#include <vector>

#include <SDL.h>

#include "../inc/Colors.hpp"
#include "../inc/DrawWrapLine.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/Vec2d.hpp"

Asteroid::Asteroid(GameWorld *new_gameWorld, Vec2d pos,
                   std::vector<Vec2d> shape, SdlColor color,
                   double scale, PhysicsComponent *new_physicsComponent,
                   double new_radius)
    : Entity(new_gameWorld, pos, shape, color, scale),
      physicsComponent{ new_physicsComponent }, radius{ new_radius }
{
    physicsComponent->setOwner(this);
    physicsComponent->setFrameImpulse(60.0);
    physicsComponent->turn(120.0);

    int numPoints{ 12 };
    double sliceAngle{ (360.0 / numPoints) * (M_PI / 180.0) };
    for (int i{ 0 }; i < numPoints; ++i)
        m_shape.push_back(Vec2d{std::sin(sliceAngle * i) * radius,
                                -std::cos(sliceAngle * i) * radius});
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

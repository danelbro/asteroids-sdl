#include "../inc/PhysicsEntity.hpp"

#include <vector>

#include <SDL.h>

#include "../inc/Colors.hpp"
#include "../inc/Entity.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/PhysicsComponent.hpp"
#include "../inc/Vec2d.hpp"
#include "../inc/VectorDraw.hpp"
#include "../inc/utility.hpp"

PhysicsEntity::PhysicsEntity(utl::EntityFlag new_type, GameWorld& new_gameWorld,
    Vec2d pos, std::vector<Vec2d> shape, SdlColor color, double scale,
    double mass)
    : Entity{ new_type, new_gameWorld, pos, shape, color, scale },
      physicsComponent{ mass, *this }, wayward{ true },
      m_transShape{}, m_fillShape{}, m_isVisible{ true }
{}

void PhysicsEntity::update_shapes()
{
    m_transShape.clear();

    for (auto p : m_shape)
        m_transShape.push_back(
            p.rotate_deg(physicsComponent.angle()) * m_scale);

    m_fillShape = m_transShape;
    for (auto& p : m_fillShape) {
        p.x += m_pos.x;
        p.y += m_pos.y;
    }
}

void PhysicsEntity::render(SDL_Renderer* renderer)
{
    if (!m_isVisible) return;

    SdlColor oldColor{ };
    SDL_GetRenderDrawColor(renderer,
        &oldColor.r, &oldColor.g, &oldColor.b, &oldColor.a);
    SDL_SetRenderDrawColor(renderer,
        m_color.r, m_color.g, m_color.b, m_color.a);

    for (size_t i{ 0 }; i < m_fillShape.size(); ++i) {
        if (i == m_fillShape.size() - 1) {
            utl::DrawWrapLine(renderer,
                gameWorld.screen,
                m_fillShape[i].x, m_fillShape[i].y,
                m_fillShape[0].x, m_fillShape[0].y);
        }
        else {
            utl::DrawWrapLine(renderer,
                gameWorld.screen,
                m_fillShape[i].x, m_fillShape[i].y,
                m_fillShape[i + 1].x, m_fillShape[i + 1].y);
        }
    }

    if (fill)
        utl::ScanFill(gameWorld, m_fillShape, m_color, renderer);

    SDL_SetRenderDrawColor(renderer,
        oldColor.r, oldColor.g, oldColor.b, oldColor.a);
}

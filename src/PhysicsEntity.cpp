#include "PhysicsEntity.hpp"

#include <vector>

#include <SDL.h>

#include "Colors.hpp"
#include "Entity.hpp"
#include "GameWorld.hpp"
#include "PhysicsComponent.hpp"
#include "Vec2d.hpp"
#include "VectorDraw.hpp"
#include "utility.hpp"

PhysicsEntity::PhysicsEntity(utl::EntityFlag new_type, GameWorld& new_gameWorld,
    Vec2d pos, std::vector<Vec2d> shape, SdlColor color, double scale,
    double mass)
    : Entity{ new_type, new_gameWorld, pos, shape, color, scale },
      physicsComponent{ mass, *this }, wayward{ true },
      m_transShape{}, m_fillShape{}, m_collider{}, m_isVisible{ true }
{
    update_shapes();
}

void PhysicsEntity::update_shapes()
{
    m_transShape.clear();
    m_transShape.reserve(m_shape.size());
    m_fillShape.clear();
    m_fillShape.reserve(m_shape.size());
    m_collider.clear();
    m_collider.reserve(m_shape.size());

    for (auto p : m_shape) {
        p = p.rotate_deg(physicsComponent.angle());
        p = p * m_scale;
        m_transShape.emplace_back(p);
        m_fillShape.emplace_back(p);
        m_collider.emplace_back(p);
    }

    for (auto& p : m_fillShape)
        p += m_pos;

    for (auto& p : m_collider)
        p += m_pos;
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

namespace utl {
    bool areColliding(const PhysicsEntity &pe1, const PhysicsEntity &pe2)
    {
        return areColliding_SAT(pe1.collider(), pe2.collider());
    }
} // namespace utl

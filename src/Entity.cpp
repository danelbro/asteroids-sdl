#include "../inc/Entity.hpp"

#include <SDL.h>

#include "../inc/GameWorld.hpp"
#include "../inc/VectorDraw.hpp"

void Entity::render(SDL_Renderer* renderer)
{
    SdlColor oldColor{ };
    SDL_GetRenderDrawColor(renderer,
        &oldColor.r, &oldColor.g, &oldColor.b, &oldColor.a);
    SDL_SetRenderDrawColor(renderer,
        m_color.r, m_color.g, m_color.b, m_color.a);

    for (unsigned i{ 0 }; i < m_shape.size(); ++i) {
        if (i == m_shape.size() - 1) {
            SDL_RenderDrawLineF(renderer,
                static_cast<float>(m_pos.x + m_shape[i].x), static_cast<float>(m_pos.y + m_shape[i].y),
                static_cast<float>(m_pos.x + m_shape[0].x), static_cast<float>(m_pos.y + m_shape[0].y));
        }
        else {
            SDL_RenderDrawLineF(renderer,
                static_cast<float>(m_pos.x + m_shape[i].x), static_cast<float>(m_pos.y + m_shape[i].y),
                static_cast<float>(m_pos.x + m_shape[i + 1].x), static_cast<float>(m_pos.y + m_shape[i + 1].y));
        }
    }

    SDL_SetRenderDrawColor(renderer,
        oldColor.r, oldColor.g, oldColor.b, oldColor.a);
}
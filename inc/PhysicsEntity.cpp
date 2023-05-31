#include "../inc/PhysicsEntity.hpp"

#include <vector>

#include <SDL.h>

#include "../inc/Entity.hpp"
#include "../inc/FlagEnums.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/PhysicsComponent.hpp"
#include "../inc/Vec2d.hpp"
#include "../inc/VectorDraw.hpp"

PhysicsEntity::PhysicsEntity(EntityFlag new_type, GameWorld* new_gameWorld, 
    Vec2d pos, std::vector<Vec2d> shape, SdlColor color, double scale,
	PhysicsComponent* new_physicsComponent)
	: Entity{ new_type, new_gameWorld, pos, shape, color, scale },
	physicsComponent{ new_physicsComponent }
{}

void PhysicsEntity::render(SDL_Renderer* renderer)
{
    SdlColor oldColor{ };
    SDL_GetRenderDrawColor(renderer,
        &oldColor.r, &oldColor.g, &oldColor.b, &oldColor.a);
    SDL_SetRenderDrawColor(renderer,
        m_color.r, m_color.g, m_color.b, m_color.a);

    std::vector<Vec2d> transShape{ };
    for (auto p : m_shape)
        transShape.push_back(p.rotate_deg(physicsComponent->angle()) * m_scale);

    for (size_t i{ 0 }; i < transShape.size(); ++i) {
        if (i == transShape.size() - 1) {
            DrawWrapLine(renderer,
                gameWorld->screen,
                m_pos.x + transShape[i].x, m_pos.y + transShape[i].y,
                m_pos.x + transShape[0].x, m_pos.y + transShape[0].y);
        }
        else {
            DrawWrapLine(renderer,
                gameWorld->screen,
                m_pos.x + transShape[i].x, m_pos.y + transShape[i].y,
                m_pos.x + transShape[i + 1].x, m_pos.y + transShape[i + 1].y);
        }
    }

    SDL_SetRenderDrawColor(renderer,
        oldColor.r, oldColor.g, oldColor.b, oldColor.a);
}
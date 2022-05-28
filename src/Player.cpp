#include "../inc/Player.hpp"

#include <vector>

#include <SDL.h>

#include "../inc/Colors.hpp"
#include "../inc/DrawWrapLine.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/PhysicsComponent.hpp"
#include "../inc/Ship.hpp"
#include "../inc/Vec2d.hpp"

Player::Player(GameWorld *new_gameWorld, Vec2d pos,
               std::vector<Vec2d> shape, SdlColor color,
               double power, double turnSpeed,
               double shotPower,
               PhysicsComponent* new_physicsComponent,
               double warpTimer, int new_lives)
    : Ship{ new_gameWorld, pos, shape, color,
    power, turnSpeed, shotPower, new_physicsComponent},
      hyperdrive{ this, warpTimer }, isVisible{ true },
      isControllable{ true }, lives{ new_lives }
{
    physicsComponent->setOwner(this);
}

void Player::render(SDL_Renderer *renderer)
{
    SdlColor oldColor{ };
    SDL_GetRenderDrawColor(renderer,
                           &oldColor.r, &oldColor.g, &oldColor.b, &oldColor.a);
    SDL_SetRenderDrawColor(renderer,
                           m_color.r, m_color.g, m_color.b, m_color.a);

    for (unsigned i{ 0 }; i < m_shape.size(); ++i) {
        if (i == m_shape.size() - 1) {
            DrawWrapLine(renderer,
                         gameWorld->screen,
                         m_pos.x + m_shape[i].x, m_pos.y + m_shape[i].y,
                         m_pos.x + m_shape[0].x, m_pos.y + m_shape[0].y);
        }
        else {
            DrawWrapLine(renderer,
                         gameWorld->screen,
                         m_pos.x + m_shape[i].x, m_pos.y + m_shape[i].y,
                         m_pos.x + m_shape[i + 1].x, m_pos.y + m_shape[i+1].y);
        }
    }

    SDL_SetRenderDrawColor(renderer,
                           oldColor.r, oldColor.g, oldColor.b, oldColor.a);
}

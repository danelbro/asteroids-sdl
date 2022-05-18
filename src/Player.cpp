#include "../inc/Player.hpp"

#include <SDL.h>

#include "../inc/GameWorld.hpp"
#include "../inc/PhysicsComponent.hpp"
#include "../inc/Ship.hpp"

Player::Player(std::string path, SDL_Renderer *renderer,
               GameWorld *new_gameWorld, double power, double turnSpeed,
               double shotPower,
               PhysicsComponent* new_physicsComponent,
               double warpTimer, int new_lives)
    : Ship{ path, renderer, new_gameWorld, power, turnSpeed, shotPower,
        new_physicsComponent},
      hyperdrive{ this, warpTimer }, isVisible{ true },
      isControllable{ true }, lives{ new_lives }
{
    setRect((gameWorld->screen.w / 2) - (m_rect.w / 2),
           (gameWorld->screen.h / 2) - (m_rect.h / 2));
    physicsComponent->setOwner(this);
}

void Player::render(SDL_Renderer *renderer)
{
    auto directionAngleRad = std::atan2(physicsComponent->facing_direction().x,
                                        physicsComponent->facing_direction().y);
    auto directionAngle = directionAngleRad * (180 / M_PI);

    // SDL_SetRenderDrawColor(renderer, debug.r, debug.g, debug.b, debug.a);
    // SDL_RenderFillRect(renderer, &dest);
    SDL_RenderCopyEx(renderer, m_texture.get(), NULL, &m_rect,
                     -directionAngle, NULL, SDL_FLIP_NONE);
    // SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
}

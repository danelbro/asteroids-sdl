#include "../inc/Entity.hpp"

#include <cmath>
#include <iostream>
#include <memory>
#include <string>

#include <SDL.h>

#include "../inc/Colors.hpp"
#include "../inc/DirFlag.hpp"
#include "../inc/utility.hpp"
#include "../inc/Vec2d.hpp"

extern const SdlColor bg;
extern const SdlColor debug;

Entity::Entity(std::string path, SDL_Renderer *renderer,
               GameWorld &new_gameWorld)
    : texture{ nullptr }, rect{ }, old_rect{ rect }, gameWorld{ new_gameWorld }
{
    texture = std::unique_ptr<SDL_Texture, SDL_TextureDestroyer> {loadMedia(path, renderer)};
    SDL_QueryTexture(texture.get(), NULL, NULL, &rect.w, &rect.h);
}

Player::Player(std::string path, SDL_Renderer *renderer,
               GameWorld &new_gameWorld)
    : Entity{ path, renderer, new_gameWorld }, velocity{ 0, 0 },
      facing_direction{ 1, 0 }, velocity_direction{ facing_direction },
      turnSpeed{ 10.0 }, mass{ 100.0 }, thrust_power{ 45.0 },
      acceleration_mag{ 0.0 }, turnAmount{ 0.0 }, isInHyperspace{ false }
{
    setPos((gameWorld.screen.w / 2) - (rect.w / 2),
           (gameWorld.screen.h / 2) - (rect.h / 2));
}

void Player::update(std::array<bool, K_TOTAL> keyState)
{
    old_rect = rect;

    if (keyState[K_LEFT])
        turnLeft();
    else if (keyState[K_RIGHT])
        turnRight();
    if (keyState[K_UP])
        accelerate();
    if (keyState[K_SPACE])
        fire();
    if (keyState[K_LSHIFT])
        hyperspace();

    facing_direction = facing_direction.rotate_deg(turnAmount);
    facing_direction.normalizeInPlace();

    double drag { 0.5 * gameWorld.fluidDensity * velocity.magnitude_squared() };

    if (velocity.magnitude() == 0)
        velocity_direction.update(0, 0);
    else
        velocity_direction = velocity.normalize();

    auto totalForces{ ((facing_direction * acceleration_mag)
                       + (-velocity_direction * drag)) };

    auto acceleration{ totalForces / mass };

    velocity = velocity + acceleration;

    rect.x -= velocity.x;
    rect.y -= velocity.y;

    collide(rect, gameWorld.screen);

    acceleration_mag = 0;
    turnAmount = 0;
}

void Player::render(SDL_Renderer *renderer, double progress)
{

    SDL_Rect dest = old_rect;
    dest.x += velocity.x * progress;
    dest.y += velocity.y * progress;

    collide(dest, gameWorld.screen);

    auto directionAngleRad = std::atan2(facing_direction.x, facing_direction.y);
    auto directionAngle = directionAngleRad * (180 / M_PI);

    // SDL_SetRenderDrawColor(renderer, debug.r, debug.g, debug.b, debug.a);
    // SDL_RenderFillRect(renderer, &dest);
    SDL_RenderCopyEx(renderer, texture.get(), NULL, &dest,
                     -directionAngle, NULL, SDL_FLIP_NONE);
    // SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
}

void Player::accelerate()
{
    acceleration_mag = thrust_power;
}

void Player::turnLeft()
{
    turnAmount = turnSpeed * -1;
}

void Player::turnRight()
{
    turnAmount = turnSpeed;
}

void Player::fire()
{
    std::cout << "Bang!\n";
}

void Player::hyperspace()
{
    if (!isInHyperspace) {
        std::cout << "Hyperspace!\n";
        isInHyperspace = true;
    }
}

void Player::collide(SDL_Rect &dest, Box screen)
{
    // things go through walls in Asteroids
    if (dest.x < -rect.w)
        dest.x = screen.w;
    else if (dest.x > screen.w)
        dest.x = -rect.w;

    if (dest.y < -rect.h)
        dest.y = screen.h;
    else if (dest.y > screen.h)
        dest.y = -rect.h;
}

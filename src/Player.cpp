#include "../inc/Player.hpp"

Player::Player(std::string path, SDL_Renderer *renderer,
               GameWorld &new_gameWorld)
    : Entity{ path, renderer, new_gameWorld }, velocity{ 0, 0 },
      facing_direction{ 1, 0 }, velocity_direction{ facing_direction },
      turnSpeed{ 10.0 }, mass{ 100.0 }, thrust_power{ 45.0 },
      accelerationMag{ 0.0 }, turnAmount{ 0.0 }, isInHyperspace{ false }
{
    setPos((gameWorld.screen.w / 2) - (rect.w / 2),
           (gameWorld.screen.h / 2) - (rect.h / 2));
}

void Player::update()
{
    old_rect = rect;

    facing_direction = facing_direction.rotate_deg(turnAmount);
    facing_direction.normalizeInPlace();

    double drag { 0.5 * gameWorld.fluidDensity * velocity.magnitude_squared() };

    if (velocity.magnitude() == 0)
        velocity_direction.update(0, 0);
    else
        velocity_direction = velocity.normalize();

    auto totalForces{ ((facing_direction * accelerationMag)
                       + (-velocity_direction * drag)) };

    auto acceleration{ totalForces / mass };

    velocity = velocity + acceleration;

    rect.x -= velocity.x;
    rect.y -= velocity.y;

    collide(rect, gameWorld.screen);

    accelerationMag = 0;
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

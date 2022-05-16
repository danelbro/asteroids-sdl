#pragma once

// Entity class representing an on-screen object

#include <array>
#include <string>
#include <vector>

#include <SDL.h>

#include "DirFlag.hpp"
#include "Vec2d.hpp"

struct GameWorld {
    Box screen{ };
    double fluidDensity{ };
};

class Entity {
public:
    virtual void update(std::array<bool, K_TOTAL> keyState) = 0;
    virtual void render(SDL_Renderer *renderer, double progress) = 0;

    SDL_Texture * getTex() const { return texture; }
    SDL_Rect getRect() const { return rect; }

protected:
    Entity(std::string path, SDL_Renderer *renderer, GameWorld *new_gameWorld);
    SDL_Texture *texture{ nullptr };
    SDL_Rect rect{ };
    SDL_Rect old_rect{ };
    GameWorld *gameWorld{ };
};

class Player : public Entity {
public:
    Player(std::string path, SDL_Renderer* renderer, GameWorld *new_gameWorld);

    void accelerate();
    void turnLeft();
    void turnRight();
    void fire();
    void hyperspace();
    // void respawn(Vecd2d new_pos, bool reset=true) {};

    void update(std::array<bool, K_TOTAL> keyState) override;
    void render(SDL_Renderer *renderer, double progress) override;
private:
    void collide(SDL_Rect &dest, Box screen);
    void updateImage();

    void setPos(int x, int y) { rect.x = x; rect.y = y; }
    void setPos(SDL_Rect newRect) { rect = newRect; }

    Vec2d velocity;
    Vec2d facing_direction;
    Vec2d velocity_direction;
    const double turnSpeed;
    const double mass;
    const double thrust_power;
    double acceleration_mag;
    double turnAmount;
    bool isInHyperspace;
};

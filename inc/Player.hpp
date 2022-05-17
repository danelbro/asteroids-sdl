#pragma once

#include <array>
#include <string>

#include <SDL.h>

#include "Hyperdrive.hpp"
#include "Ship.hpp"
#include "Vec2d.hpp"

class Engine;

class Player : public Ship {
public:
    Player(std::string path, SDL_Renderer* renderer, GameWorld &new_gameWorld);

    Hyperdrive hyperdrive();

    void respawn(Vec2d new_pos, bool reset=true) {};

    void update() override;
    void render(SDL_Renderer *renderer, double progress) override;
private:
    bool isVisible;
    bool isControllable;
    int lives;
};

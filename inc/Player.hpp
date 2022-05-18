#pragma once

#include <array>
#include <memory>
#include <string>

#include <SDL.h>

#include "Hyperdrive.hpp"
#include "Ship.hpp"
#include "Vec2d.hpp"

class Engine;
struct GameWorld;
class PhysicsComponent;

class Player : public Ship {
public:
    Player(std::string path, SDL_Renderer* renderer,
           GameWorld *new_gameWorld, double power, double turnSpeed,
           double shotPower,
           PhysicsComponent *new_physicsComponent,
           double warpTimer, int new_lives);

    Hyperdrive hyperdrive;

    void respawn(Vec2d new_pos, bool reset=true);

    void render(SDL_Renderer *renderer) override;
private:
    bool isVisible;
    bool isControllable;
    int lives;
};
